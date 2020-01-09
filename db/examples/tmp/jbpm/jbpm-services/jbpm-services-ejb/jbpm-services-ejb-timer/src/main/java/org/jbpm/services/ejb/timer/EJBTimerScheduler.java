/*
 * Copyright 2017 Red Hat, Inc. and/or its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.jbpm.services.ejb.timer;

import java.io.Serializable;
import java.time.ZonedDateTime;
import java.time.temporal.ChronoUnit;
import java.util.Date;
import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import javax.annotation.PostConstruct;
import javax.annotation.Resource;
import javax.ejb.ConcurrencyManagement;
import javax.ejb.ConcurrencyManagementType;
import javax.ejb.Lock;
import javax.ejb.LockType;
import javax.ejb.NoSuchObjectLocalException;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import javax.ejb.Timeout;
import javax.ejb.Timer;
import javax.ejb.TimerConfig;
import javax.ejb.TransactionManagement;
import javax.ejb.TransactionManagementType;
import javax.transaction.Status;
import javax.transaction.UserTransaction;

import org.drools.core.time.JobHandle;
import org.drools.core.time.impl.TimerJobInstance;
import org.jbpm.process.core.timer.TimerServiceRegistry;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Singleton
@Startup
@ConcurrencyManagement(ConcurrencyManagementType.CONTAINER)
@TransactionManagement(TransactionManagementType.BEAN)
@Lock(LockType.READ)
public class EJBTimerScheduler {

	private static final Logger logger = LoggerFactory.getLogger(EJBTimerScheduler.class);

    private enum TimerExceptionPolicy {
        RETRY,
        PLATFORM
    };

    private static final Long TIMER_RETRY_INTERVAL = Long.parseLong(System.getProperty("org.kie.jbpm.timer.retry.interval", "5000"));

    private static final Integer TIMER_RETRY_LIMIT = Integer.parseInt(System.getProperty("org.kie.jbpm.timer.retry.limit", "3"));

    private static final TimerExceptionPolicy TIMER_RETRY_POLICY = Enum.valueOf(TimerExceptionPolicy.class, System.getProperty("org.kie.jbpm.timer.retry.policy", "PLATFORM"));

	private static final Integer OVERDUE_WAIT_TIME = Integer.parseInt(System.getProperty("org.jbpm.overdue.timer.wait", "20000"));

	private static final boolean USE_LOCAL_CACHE = Boolean.parseBoolean(System.getProperty("org.jbpm.ejb.timer.local.cache", "true"));

	private ConcurrentMap<String, TimerJobInstance> localCache = new ConcurrentHashMap<String, TimerJobInstance>();

	@Resource
	protected javax.ejb.TimerService timerService;

    @Resource
    protected UserTransaction utx;


	@PostConstruct
	public void setup() {
	    // disable auto init of timers since ejb timer service supports persistence of timers
	    System.setProperty("org.jbpm.rm.init.timer", "false");
	    logger.info("Using local cache for EJB timers: {}", USE_LOCAL_CACHE);
	}

	@Timeout
	public void executeTimerJob(Timer timer) {
        EjbTimerJob timerJob = (EjbTimerJob) timer.getInfo();
        TimerJobInstance timerJobInstance = timerJob.getTimerJobInstance();
        logger.debug("About to execute timer for job {}", timerJob);

        String timerServiceId = ((EjbGlobalJobHandle) timerJobInstance.getJobHandle()).getDeploymentId();

        // handle overdue timers as ejb timer service might start before all deployments are ready
        long time = 0;
        while (TimerServiceRegistry.getInstance().get(timerServiceId) == null) {
            logger.debug("waiting for timer service to be available, elapsed time {} ms", time);
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            time += 500;

            if (time > OVERDUE_WAIT_TIME) {
                logger.debug("No timer service found after waiting {} ms", time);
                break;
            }
        }
        try {
            transaction(this::executeTimerJobInstance, timerJobInstance);
        } catch (Exception e) {
            recoverTimerJobInstance(timerJob, e);
        }
    }

    private void executeTimerJobInstance(TimerJobInstance timerJobInstance) throws Exception {
        try {
            ((Callable<?>) timerJobInstance).call();
        } catch (Exception e) {
            logger.warn("Execution of time failed due to {}", e.getMessage(), e);
            throw e;
        }
    }

    private void recoverTimerJobInstance(EjbTimerJob ejbTimerJob, Exception e) {
        // if we have next date fired means that it would have been reescheduled already by DefaultTimerJobInstance
        if (ejbTimerJob.getTimerJobInstance().getTrigger().hasNextFireTime() != null) {
            logger.warn("Execution of time failed Interval Trigger failed {}", ejbTimerJob.getTimerJobInstance());
            return;
        }

        // if there is not next date to be fired, we need to apply policy otherwise will be lost
        switch (TIMER_RETRY_POLICY) {
            case RETRY:
                logger.warn("Execution of time failed. The timer will be retried {}", ejbTimerJob.getTimerJobInstance());
                Transaction<TimerJobInstance> operation = (instance) -> {
                    ZonedDateTime nextRetry = ZonedDateTime.now().plus(TIMER_RETRY_INTERVAL, ChronoUnit.MILLIS);
                    EjbTimerJobRetry info = null;
                    if(ejbTimerJob instanceof EjbTimerJobRetry) {
                        info = ((EjbTimerJobRetry) ejbTimerJob).next();
                    } else {
                        info =  new EjbTimerJobRetry(instance);
                    }
                    if (TIMER_RETRY_LIMIT > 0 && info.getRetry() > TIMER_RETRY_LIMIT) {
                        logger.warn("The timer {} reached retry limit {}. It won't be retried again", instance, TIMER_RETRY_LIMIT);
                        return;
                    }
                    TimerConfig config = new TimerConfig(info, true);
                    timerService.createSingleActionTimer(Date.from(nextRetry.toInstant()), config);
                };
                try {
                    transaction(operation, ejbTimerJob.getTimerJobInstance());
                } catch (Exception e1) {
                    logger.error("Failed to executed timer recovery {}", e1.getMessage(), e1);
                }
                break;
            case PLATFORM:
                logger.warn("Execution of time failed. Application server policy applied {}", ejbTimerJob.getTimerJobInstance());
                throw new RuntimeException(e);
        }
    }

    @FunctionalInterface
    private interface Transaction<I> {

        void doWork(I item) throws Exception;
    }

    private <I> void transaction(Transaction<I> operation, I item) throws Exception {
        try {
            utx.begin();
            operation.doWork(item);
            utx.commit();
        } catch(Exception e) {
            try {
                if (utx.getStatus() != Status.STATUS_NO_TRANSACTION) {
                    utx.rollback();
                }
            } catch (Exception re) {
                logger.error("transaction could not be rolled back", re);
            }
            throw e;
        }
    }

	public void internalSchedule(TimerJobInstance timerJobInstance) {
		TimerConfig config = new TimerConfig(new EjbTimerJob(timerJobInstance), true);
		Date expirationTime = timerJobInstance.getTrigger().hasNextFireTime();
		logger.debug("Timer expiration date is {}", expirationTime);
		if (expirationTime != null) {
			timerService.createSingleActionTimer(expirationTime, config);
			logger.debug("Timer scheduled {} on {} scheduler service", timerJobInstance);
			if (USE_LOCAL_CACHE) {
				localCache.putIfAbsent(((EjbGlobalJobHandle) timerJobInstance.getJobHandle()).getUuid(), timerJobInstance);
			}
		} else {
			logger.info("Timer that was to be scheduled has already expired");
		}
	}



	public boolean removeJob(JobHandle jobHandle) {
		EjbGlobalJobHandle ejbHandle = (EjbGlobalJobHandle) jobHandle;

		for (Timer timer : timerService.getTimers()) {
			try {
    		    Serializable info = timer.getInfo();
    			if (info instanceof EjbTimerJob) {
    				EjbTimerJob job = (EjbTimerJob) info;

    				EjbGlobalJobHandle handle = (EjbGlobalJobHandle) job.getTimerJobInstance().getJobHandle();
    				if (handle.getUuid().equals(ejbHandle.getUuid())) {
    					logger.debug("Job handle {} does match timer and is going to be canceled", jobHandle);
    					if (USE_LOCAL_CACHE) {
    						localCache.remove(handle.getUuid());
    					}
    					try {
    					    timer.cancel();
    					} catch (Throwable e) {
    					    logger.debug("Timer cancel error due to {}", e.getMessage());
    					    return false;
    					}
    					return true;
    				}
    			}
			} catch (NoSuchObjectLocalException e) {
			    logger.debug("Timer {} has already expired or was canceled ", timer);
			}
		}
		logger.debug("Job handle {} does not match any timer on {} scheduler service", jobHandle, this);
		return false;
	}

	public TimerJobInstance getTimerByName(String jobName) {
    	if (USE_LOCAL_CACHE) {
    		if (localCache.containsKey(jobName)) {
    			logger.debug("Found job {} in cache returning", jobName);
    			return localCache.get(jobName);
    		}
    	}
	    TimerJobInstance found = null;

		for (Timer timer : timerService.getTimers()) {
		    try {
    			Serializable info = timer.getInfo();
    			if (info instanceof EjbTimerJob) {
    				EjbTimerJob job = (EjbTimerJob) info;

    				EjbGlobalJobHandle handle = (EjbGlobalJobHandle) job.getTimerJobInstance().getJobHandle();

    				if (handle.getUuid().equals(jobName)) {
    					found = handle.getTimerJobInstance();
							if (USE_LOCAL_CACHE) {
    					    localCache.putIfAbsent(jobName, found);
						  }
    					logger.debug("Job {} does match timer and is going to be returned {}", jobName, found);

    					break;
    				}
    			}
		    } catch (NoSuchObjectLocalException e) {
                logger.debug("Timer info for {} was not found ", timer);
            }
		}

		return found;
	}

}
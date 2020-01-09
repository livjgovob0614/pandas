--- START ---
RENAME TABLE SBI_I18N_MESSAGES TO SBI_I18N_MESSAGES_OLD;

CREATE TABLE SBI_I18N_MESSAGES (ID INT) AS
SELECT (@ROW := @ROW + 1) AS ID, T.*
FROM SBI_I18N_MESSAGES_OLD T, (SELECT @ROW := 0) R;

DROP TABLE SBI_I18N_MESSAGES_OLD;

ALTER TABLE SBI_I18N_MESSAGES ADD CONSTRAINT PK_SBI_I18N_MESSAGES PRIMARY KEY (ID);
ALTER TABLE SBI_I18N_MESSAGES ADD CONSTRAINT FK_SBI_I18N_MESSAGES FOREIGN KEY (LANGUAGE_CD) REFERENCES SBI_DOMAINS (VALUE_ID);
ALTER TABLE SBI_I18N_MESSAGES ADD UNIQUE SBI_I18N_MESSAGES_UNIQUE(LANGUAGE_CD, LABEL, ORGANIZATION);

INSERT INTO hibernate_sequences VALUES ('SBI_I18N_MESSAGES',
                                                            (SELECT COALESCE(MAX(m.ID) + 1, 1) FROM SBI_I18N_MESSAGES m));
COMMIT;

ALTER TABLE SBI_DATA_SET ADD UNIQUE XAK2SBI_DATA_SET (NAME, VERSION_NUM, ORGANIZATION);

ALTER TABLE SBI_ATTRIBUTE ADD COLUMN  LOV_ID INTEGER NULL AFTER ATTRIBUTE_ID,
						  ADD COLUMN  ALLOW_USER SMALLINT(6) DEFAULT '1' AFTER LOV_ID,
						  ADD COLUMN  MULTIVALUE SMALLINT(6) DEFAULT '0' AFTER ALLOW_USER,
						  ADD COLUMN  SYNTAX SMALLINT(6) NULL AFTER MULTIVALUE,
						  ADD COLUMN  VALUE_TYPE_ID INTEGER NULL AFTER SYNTAX,
						  ADD COLUMN  VALUE_TYPE_CD VARCHAR(20) AFTER VALUE_TYPE_ID,
						  ADD COLUMN  VALUE_TYPE ENUM ('STRING','DATE','NUM') AFTER VALUE_TYPE_CD;

ALTER TABLE `SBI_ATTRIBUTE` CHANGE COLUMN `DESCRIPTION` `DESCRIPTION` VARCHAR(500) NULL;

ALTER TABLE SBI_EVENTS_LOG ADD COLUMN EVENT_TYPE VARCHAR(50) DEFAULT 'SCHEDULER' NOT NULL;

UPDATE SBI_EVENTS_LOG SET EVENT_TYPE = (
CASE HANDLER
	WHEN 'it.eng.spagobi.events.handlers.DefaultEventPresentationHandler' THEN 'SCHEDULER'
	WHEN 'it.eng.spagobi.events.handlers.CommonjEventPresentationHandler' THEN 'COMMONJ'
	WHEN 'it.eng.spagobi.events.handlers.TalendEventPresentationHandler' THEN 'ETL'
	WHEN 'it.eng.spagobi.events.handlers.WekaEventPresentationHandler' THEN 'DATA_MINING'
END
);
commit;

ALTER TABLE SBI_EVENTS_LOG DROP COLUMN HANDLER;

--- END ---

ALTER TABLE SBI_OUTPUT_PARAMETER MODIFY COLUMN FORMAT_VALUE varchar(30);



-- BEGIN---
CREATE TABLE SBI_METAMODEL_PAR (
       METAMODEL_PAR_ID           INTEGER NOT NULL ,
       PAR_ID               INTEGER NOT NULL,
       METAMODEL_ID             INTEGER NOT NULL,
       LABEL                VARCHAR(40) NOT NULL,
       REQ_FL               SMALLINT NULL,
       MOD_FL               SMALLINT NULL,
       VIEW_FL              SMALLINT NULL,
       MULT_FL              SMALLINT NULL,
       PROG                 INTEGER NOT NULL,
       PARURL_NM            VARCHAR(20) NULL,
       PRIORITY             INTEGER NULL,
       COL_SPAN             INTEGER NULL DEFAULT 1,
       THICK_PERC           INTEGER NULL DEFAULT 0,
       USER_IN              VARCHAR(100) NOT NULL,
       USER_UP              VARCHAR(100),
       USER_DE              VARCHAR(100),
       TIME_IN              TIMESTAMP NOT NULL,
       TIME_UP              TIMESTAMP NULL DEFAULT NULL,
       TIME_DE              TIMESTAMP NULL DEFAULT NULL,
       SBI_VERSION_IN       VARCHAR(10),
       SBI_VERSION_UP       VARCHAR(10),
       SBI_VERSION_DE       VARCHAR(10),
       META_VERSION         VARCHAR(100),
       ORGANIZATION         VARCHAR(20),
       PRIMARY KEY (METAMODEL_PAR_ID)
) ENGINE=InnoDB;
ALTER TABLE SBI_METAMODEL_PAR 		ADD CONSTRAINT FK_METAMODEL_PAR_1 					FOREIGN KEY (METAMODEL_ID) 				REFERENCES SBI_META_MODELS (ID);
ALTER TABLE SBI_METAMODEL_PAR 		ADD CONSTRAINT FK_METAMODEL_PAR_2 					FOREIGN KEY (PAR_ID) 				REFERENCES SBI_PARAMETERS (PAR_ID);

COMMIT;
-- END---

-- BEGIN---

CREATE TABLE SBI_METAMODEL_PARUSE (
		PARUSE_ID			INTEGER NOT NULL,
		METAMODEL_PAR_ID         INTEGER NOT NULL,
		USE_ID              INTEGER NOT NULL,
		METAMODEL_PAR_FATHER_ID   INTEGER NOT NULL,
		FILTER_OPERATION    VARCHAR(20) NOT NULL,
		PROG 				INTEGER NOT NULL,
		FILTER_COLUMN       VARCHAR(30) NOT NULL,
		PRE_CONDITION 		VARCHAR(10),
	    POST_CONDITION 		VARCHAR(10),
	    LOGIC_OPERATOR 		VARCHAR(10),
        USER_IN             VARCHAR(100) NOT NULL,
        USER_UP             VARCHAR(100),
        USER_DE             VARCHAR(100),
        TIME_IN             TIMESTAMP NOT NULL,
        TIME_UP             TIMESTAMP NULL DEFAULT NULL,
        TIME_DE             TIMESTAMP NULL DEFAULT NULL,
        SBI_VERSION_IN      VARCHAR(10),
        SBI_VERSION_UP      VARCHAR(10),
        SBI_VERSION_DE      VARCHAR(10),
        META_VERSION        VARCHAR(100),
        ORGANIZATION        VARCHAR(20),
	    PRIMARY KEY(PARUSE_ID)
) ENGINE=InnoDB;

ALTER TABLE SBI_METAMODEL_PARUSE					ADD CONSTRAINT FK_SBI_METAMODEL_PARUSE_1 					FOREIGN KEY (METAMODEL_PAR_ID) 			REFERENCES SBI_METAMODEL_PAR (METAMODEL_PAR_ID);
ALTER TABLE SBI_METAMODEL_PARUSE 					ADD CONSTRAINT FK_SBI_METAMODEL_PARUSE_2 					FOREIGN KEY (USE_ID) 				REFERENCES SBI_PARUSE (USE_ID) 	;
ALTER TABLE SBI_METAMODEL_PARUSE 					ADD CONSTRAINT FK_SBI_METAMODEL_PARUSE_3 					FOREIGN KEY (METAMODEL_PAR_FATHER_ID)		REFERENCES SBI_METAMODEL_PAR (METAMODEL_PAR_ID);

CREATE TABLE SBI_METAMODEL_PARVIEW (
	PARVIEW_ID INTEGER NOT NULL,
    METAMODEL_PAR_ID INTEGER NOT NULL,
    METAMODEL_PAR_FATHER_ID  INTEGER NOT NULL,
    OPERATION  VARCHAR(20) NOT NULL,
    COMPARE_VALUE  VARCHAR(200) NOT NULL,
    VIEW_LABEL  VARCHAR(50),
    PROG INTEGER,
       USER_IN              VARCHAR(100) NOT NULL,
       USER_UP              VARCHAR(100),
       USER_DE              VARCHAR(100),
       TIME_IN              TIMESTAMP NOT NULL,
        TIME_UP             TIMESTAMP NULL DEFAULT NULL,
        TIME_DE             TIMESTAMP NULL DEFAULT NULL,
       SBI_VERSION_IN       VARCHAR(10),
       SBI_VERSION_UP       VARCHAR(10),
       SBI_VERSION_DE       VARCHAR(10),
       META_VERSION         VARCHAR(100),
       ORGANIZATION         VARCHAR(20),
  PRIMARY KEY (PARVIEW_ID)
) ENGINE=InnoDB;

ALTER TABLE SBI_METAMODEL_PARVIEW 				ADD CONSTRAINT FK_SBI_METAMODEL_PARVIEW_1 				FOREIGN KEY (METAMODEL_PAR_ID) 			REFERENCES SBI_METAMODEL_PAR (METAMODEL_PAR_ID) ;
ALTER TABLE SBI_METAMODEL_PARVIEW 				ADD CONSTRAINT FK_SBI_METAMODEL_PARVIEW_2 				FOREIGN KEY (METAMODEL_PAR_FATHER_ID)		REFERENCES SBI_METAMODEL_PAR (METAMODEL_PAR_ID) ;

-- END---


-- BeGin ---
ALTER TABLE `SBI_METAMODEL_PAR`
CHANGE COLUMN `REQ_FL` `REQ_FL` SMALLINT(6) NULL DEFAULT '0' ,
CHANGE COLUMN `MOD_FL` `MOD_FL` SMALLINT(6) NULL DEFAULT '0' ,
CHANGE COLUMN `VIEW_FL` `VIEW_FL` SMALLINT(6) NULL DEFAULT '1' ,
CHANGE COLUMN `MULT_FL` `MULT_FL` SMALLINT(6) NULL DEFAULT '0' ;

ALTER TABLE `SBI_OBJ_PAR`
CHANGE COLUMN `REQ_FL` `REQ_FL` SMALLINT(6) NULL DEFAULT '0' ,
CHANGE COLUMN `MOD_FL` `MOD_FL` SMALLINT(6) NULL DEFAULT '0' ,
CHANGE COLUMN `VIEW_FL` `VIEW_FL` SMALLINT(6) NULL DEFAULT '1' ,
CHANGE COLUMN `MULT_FL` `MULT_FL` SMALLINT(6) NULL DEFAULT '0' ;
-- END---

-- BeGin ---
SET @dbname = DATABASE();
SET @tablename = "sbi_federation_definition";
SET @columnname = "OWNER";
SET @preparedStatement = (SELECT IF(
  (
    SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS
    WHERE
      (table_name = @tablename)
      AND (table_schema = @dbname)
      AND (column_name = @columnname)
  ) > 0,
  "SELECT 1",
  CONCAT("ALTER TABLE ", @tablename, " ADD ", @columnname, " VARCHAR(100) NULL AFTER `DEGENERATED`;")
));
PREPARE alterIfNotExists FROM @preparedStatement;
EXECUTE alterIfNotExists;
DEALLOCATE PREPARE alterIfNotExists;
-- END---


DELETE FROM SBI_ROLE_TYPE_USER_FUNC WHERE ROLE_TYPE_ID = (SELECT VALUE_ID FROM SBI_DOMAINS WHERE VALUE_CD = 'TEST_ROLE') AND USER_FUNCT_ID IN (SELECT USER_FUNCT_ID FROM SBI_USER_FUNC  WHERE  NAME IN ('TIMESPAN', 'FUNCTIONSCATALOGMANAGEMENT','MANAGECROSSNAVIGATION','EVENTSMANAGEMENT'));
COMMIT;
-- Begin----
RENAME TABLE SBI_OBJ_PARUSE TO SBI_OBJ_PARUSE_OLD;
CREATE TABLE SBI_OBJ_PARUSE (PARUSE_ID INT) AS
SELECT (@ROW := @ROW +1) AS PARUSE_ID, OLDTABLE.*
FROM SBI_OBJ_PARUSE_OLD OLDTABLE,(SELECT @ROW := 0) R;

DROP TABLE SBI_OBJ_PARUSE_OLD;

ALTER TABLE SBI_OBJ_PARUSE ADD CONSTRAINT PK_SBI_OBJ_PARUSE PRIMARY KEY(PARUSE_ID);
ALTER TABLE SBI_OBJ_PARUSE ADD CONSTRAINT FK_SBI_OBJ_PARUSE_1 FOREIGN KEY (OBJ_PAR_ID) REFERENCES SBI_OBJ_PAR (OBJ_PAR_ID);
ALTER TABLE SBI_OBJ_PARUSE ADD CONSTRAINT FK_SBI_OBJ_PARUSE_2 FOREIGN KEY (USE_ID) REFERENCES SBI_PARUSE (USE_ID);
ALTER TABLE SBI_OBJ_PARUSE ADD CONSTRAINT FK_SBI_OBJ_PARUSE_3 FOREIGN KEY (OBJ_PAR_FATHER_ID) REFERENCES SBI_OBJ_PAR (OBJ_PAR_ID);

INSERT INTO HIBERNATE_SEQUENCES VALUES ('SBI_OBJ_PARUSE',(SELECT COALESCE(MAX(NEWTABLE.PARUSE_ID) + 1,1) FROM SBI_OBJ_PARUSE NEWTABLE));
 -- End---
 -- Begin----
RENAME TABLE SBI_OBJ_PARVIEW TO SBI_OBJ_PARVIEW_OLD;
CREATE TABLE SBI_OBJ_PARVIEW (PARVIEW_ID INT) AS
SELECT (@ROW := @ROW +1) AS PARVIEW_ID, OLDTABLE.*
FROM SBI_OBJ_PARVIEW_OLD OLDTABLE,(SELECT @ROW := 0) R;

DROP TABLE SBI_OBJ_PARVIEW_OLD;

ALTER TABLE SBI_OBJ_PARVIEW ADD CONSTRAINT PK_SBI_OBJ_PARVIEW PRIMARY KEY(PARVIEW_ID);
ALTER TABLE SBI_OBJ_PARVIEW ADD CONSTRAINT FK_SBI_OBJ_PARVIEW_1 FOREIGN KEY (OBJ_PAR_ID) REFERENCES SBI_OBJ_PAR (OBJ_PAR_ID);
ALTER TABLE SBI_OBJ_PARVIEW ADD CONSTRAINT FK_SBI_OBJ_PARVIEW_2 FOREIGN KEY (OBJ_PAR_FATHER_ID) REFERENCES SBI_OBJ_PAR (OBJ_PAR_ID);

INSERT INTO HIBERNATE_SEQUENCES VALUES ('SBI_OBJ_PARVIEW',(SELECT COALESCE(MAX(NEWTABLE.PARVIEW_ID) + 1, 1) FROM SBI_OBJ_PARVIEW NEWTABLE));
 -- End---



-- begin--
CREATE TABLE SBI_METAMODEL_VIEWPOINTS (
  	VP_ID              INTEGER NOT NULL,
  	METAMODEL_ID       INTEGER NOT NULL,
  	VP_NAME            VARCHAR(40) NOT NULL,
  	VP_OWNER           VARCHAR(40) DEFAULT NULL,
  	VP_DESC            VARCHAR(160) DEFAULT NULL,
  	VP_SCOPE           VARCHAR(20) NOT NULL,
  	VP_VALUE_PARAMS    TEXT,
  	VP_CREATION_DATE   TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  	USER_IN            VARCHAR(100) NOT NULL,
  	USER_UP            VARCHAR(100) DEFAULT NULL,
  	USER_DE            VARCHAR(100) DEFAULT NULL,
  	TIME_IN            TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  	TIME_UP            TIMESTAMP NULL DEFAULT NULL,
  	TIME_DE            TIMESTAMP NULL DEFAULT NULL,
  	SBI_VERSION_IN     VARCHAR(10) DEFAULT NULL,
  	SBI_VERSION_UP     VARCHAR(10) DEFAULT NULL,
  	SBI_VERSION_DE     VARCHAR(10) DEFAULT NULL,
  	META_VERSION       VARCHAR(100) DEFAULT NULL,
  	ORGANIZATION       VARCHAR(20) DEFAULT NULL,
  PRIMARY KEY (`VP_ID`)
) ENGINE=InnoDB;

ALTER TABLE SBI_METAMODEL_VIEWPOINTS        ADD CONSTRAINT `FK_SBI_METAMODEL_VIEWPOINTS_1`            FOREIGN KEY (`METAMODEL_ID`)            REFERENCES SBI_META_MODELS (`ID`);

-- end--

-- Tags Functonality
CREATE TABLE SBI_TAG (
	TAG_ID               INTEGER NOT NULL,
	NAME                 VARCHAR(30) NOT NULL,
	USER_IN              VARCHAR(100) NOT NULL,
	USER_UP              VARCHAR(100),
	USER_DE              VARCHAR(100),
	TIME_IN              TIMESTAMP NOT NULL,
	TIME_UP              TIMESTAMP NULL DEFAULT NULL,
	TIME_DE              TIMESTAMP NULL DEFAULT NULL,
	SBI_VERSION_IN       VARCHAR(10),
	SBI_VERSION_UP       VARCHAR(10),
	SBI_VERSION_DE       VARCHAR(10),
	META_VERSION         VARCHAR(100),
	ORGANIZATION         VARCHAR(20),
	PRIMARY KEY (TAG_ID),
	CONSTRAINT XAK1SBI_TAG UNIQUE (NAME, ORGANIZATION)
) ENGINE=InnoDB;


CREATE TABLE SBI_DATA_SET_TAG (
	DS_ID                INTEGER NOT NULL,
	VERSION_NUM	     	 INTEGER NOT NULL,
	ORGANIZATION         VARCHAR(20),
	TAG_ID               INTEGER NOT NULL,
	PRIMARY KEY (DS_ID, VERSION_NUM, ORGANIZATION, TAG_ID),
	FOREIGN KEY (TAG_ID) REFERENCES SBI_TAG (TAG_ID) ON UPDATE NO ACTION ON DELETE RESTRICT,
	FOREIGN KEY (DS_ID, VERSION_NUM, ORGANIZATION) REFERENCES SBI_DATA_SET (DS_ID, VERSION_NUM, ORGANIZATION)
	ON UPDATE NO ACTION ON DELETE RESTRICT
) ENGINE=InnoDB;
-- Tags Functonality END

ALTER TABLE SBI_KPI_THRESHOLD_VALUE CHANGE `POSITION` `POSITION_NUMBER` INT(11) DEFAULT NULL;

-- Column to count failed login attempts to lock the account and prevent brute force in login page
ALTER TABLE SBI_USER
	ADD COLUMN FAILED_LOGIN_ATTEMPTS INT DEFAULT 0 NOT NULL AFTER DT_LAST_ACCESS;

-- Column to define a max value for an analytical driver
ALTER TABLE SBI_PARUSE
  	ADD COLUMN MAX_LOV_ID INT DEFAULT NULL AFTER DEFAULT_LOV_ID;
ALTER TABLE SBI_PARUSE
    ADD CONSTRAINT FK_SBI_PARUSE_4 FOREIGN KEY (MAX_LOV_ID) REFERENCES SBI_LOV (LOV_ID) ON DELETE RESTRICT;

-- Removing network engine and document type references (assuming they are not being used)
SET SQL_SAFE_UPDATES = 0;
DELETE FROM SBI_PRODUCT_TYPE_ENGINE WHERE ENGINE_ID IN (SELECT ENGINE_ID FROM SBI_ENGINES WHERE DRIVER_NM = 'it.eng.spagobi.engines.drivers.network.NetworkDriver');
DELETE FROM SBI_EXPORTERS WHERE ENGINE_ID IN (SELECT ENGINE_ID FROM SBI_ENGINES WHERE DRIVER_NM = 'it.eng.spagobi.engines.drivers.network.NetworkDriver');
DELETE FROM SBI_ENGINES WHERE DRIVER_NM = 'it.eng.spagobi.engines.drivers.network.NetworkDriver';
DELETE FROM SBI_DOMAINS WHERE VALUE_CD = 'NETWORK' AND DOMAIN_CD = 'BIOBJ_TYPE';
COMMIT;

-- Create columns TABLE_PREFIX_LIKE and TABLE_PREFIX_NOT_LIKE in SBI_META_MODELS
-- Column to define prefixes to use in like conditions
ALTER TABLE SBI_META_MODELS ADD TABLE_PREFIX_LIKE VARCHAR(4000) NULL;
-- Column to define prefixes to use in not like conditions
ALTER TABLE SBI_META_MODELS ADD TABLE_PREFIX_NOT_LIKE VARCHAR(4000) NULL;

-- Create column for default role ID in SBI_USER table
ALTER TABLE SBI_USER ADD DEFAULT_ROLE_ID INTEGER DEFAULT NULL;
-- Create foreign key between SBI_USER and SBI_EXT_ROLES
ALTER TABLE SBI_USER ADD CONSTRAINT FOREIGN KEY FK_SBI_USER_1 (DEFAULT_ROLE_ID) REFERENCES SBI_EXT_ROLES(EXT_ROLE_ID);
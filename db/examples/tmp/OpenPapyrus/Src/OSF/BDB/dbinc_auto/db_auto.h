/* Do not edit: automatically built by gen_rec.awk. */

#ifndef	__db_AUTO_H
#define	__db_AUTO_H
// @v9.5.5 #include "dbinc/log.h"
#define	DB___db_addrem	41
typedef struct ___db_addrem_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	uint32	opcode;
	int32	fileid;
	db_pgno_t	pgno;
	uint32	indx;
	uint32	nbytes;
	DBT	hdr;
	DBT	dbt;
	DB_LSN	pagelsn;
} __db_addrem_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_addrem_desc[];
static inline int
__db_addrem_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags,
    uint32 opcode, db_pgno_t pgno, uint32 indx, uint32 nbytes,
    const DBT *hdr, const DBT *dbt, DB_LSN * pagelsn)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_addrem, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(uint32) +
	    sizeof(uint32) + sizeof(uint32) + LOG_DBT_SIZE(hdr) +
	    LOG_DBT_SIZE(dbt) + sizeof(*pagelsn),
	    __db_addrem_desc,
	    opcode, pgno, indx, nbytes, hdr, dbt, pagelsn));
}

static inline int __db_addrem_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_addrem_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_addrem_desc, sizeof(__db_addrem_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_addrem_42	41
typedef struct ___db_addrem_42_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	uint32	opcode;
	int32	fileid;
	db_pgno_t	pgno;
	uint32	indx;
	uint32	nbytes;
	DBT	hdr;
	DBT	dbt;
	DB_LSN	pagelsn;
} __db_addrem_42_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_addrem_42_desc[];
static inline int __db_addrem_42_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_addrem_42_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_addrem_42_desc, sizeof(__db_addrem_42_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_big	43
typedef struct ___db_big_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	uint32	opcode;
	int32	fileid;
	db_pgno_t	pgno;
	db_pgno_t	prev_pgno;
	db_pgno_t	next_pgno;
	DBT	dbt;
	DB_LSN	pagelsn;
	DB_LSN	prevlsn;
	DB_LSN	nextlsn;
} __db_big_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_big_desc[];
static inline int
__db_big_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags,
    uint32 opcode, db_pgno_t pgno, db_pgno_t prev_pgno, db_pgno_t next_pgno,
    const DBT *dbt, DB_LSN * pagelsn, DB_LSN * prevlsn, DB_LSN * nextlsn)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_big, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(uint32) +
	    sizeof(uint32) + sizeof(uint32) + LOG_DBT_SIZE(dbt) +
	    sizeof(*pagelsn) + sizeof(*prevlsn) + sizeof(*nextlsn),
	    __db_big_desc,
	    opcode, pgno, prev_pgno, next_pgno, dbt, pagelsn, prevlsn,
	    nextlsn));
}

static inline int __db_big_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_big_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_big_desc, sizeof(__db_big_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_big_42	43
typedef struct ___db_big_42_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	uint32	opcode;
	int32	fileid;
	db_pgno_t	pgno;
	db_pgno_t	prev_pgno;
	db_pgno_t	next_pgno;
	DBT	dbt;
	DB_LSN	pagelsn;
	DB_LSN	prevlsn;
	DB_LSN	nextlsn;
} __db_big_42_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_big_42_desc[];
static inline int __db_big_42_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_big_42_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_big_42_desc, sizeof(__db_big_42_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_ovref	44
typedef struct ___db_ovref_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	int32	adjust;
	DB_LSN	lsn;
} __db_ovref_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_ovref_desc[];
static inline int
__db_ovref_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, int32 adjust, DB_LSN * lsn)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_ovref, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(uint32) +
	    sizeof(*lsn),
	    __db_ovref_desc, pgno, adjust, lsn));
}

static inline int __db_ovref_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_ovref_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_ovref_desc, sizeof(__db_ovref_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_relink_42	45
typedef struct ___db_relink_42_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	uint32	opcode;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	lsn;
	db_pgno_t	prev;
	DB_LSN	lsn_prev;
	db_pgno_t	next;
	DB_LSN	lsn_next;
} __db_relink_42_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_relink_42_desc[];
static inline int __db_relink_42_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_relink_42_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_relink_42_desc, sizeof(__db_relink_42_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_debug	47
typedef struct ___db_debug_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	DBT	op;
	int32	fileid;
	DBT	key;
	DBT	data;
	uint32	arg_flags;
} __db_debug_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_debug_desc[];
static inline int
__db_debug_log(ENV *env, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags,
    const DBT *op, int32 fileid, const DBT *key, const DBT *data, uint32 arg_flags)
{
	return (__log_put_record(env, NULL, txnp, ret_lsnp,
	    flags, DB___db_debug, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    LOG_DBT_SIZE(op) + sizeof(uint32) + LOG_DBT_SIZE(key) +
	    LOG_DBT_SIZE(data) + sizeof(uint32),
	    __db_debug_desc,
	    op, fileid, key, data, arg_flags));
}

static inline int __db_debug_read(ENV *env, 
    void *data, __db_debug_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    NULL, NULL, data, __db_debug_desc, sizeof(__db_debug_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_noop	48
typedef struct ___db_noop_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	prevlsn;
} __db_noop_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_noop_desc[];
static inline int
__db_noop_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, DB_LSN * prevlsn)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_noop, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(*prevlsn),
	    __db_noop_desc, pgno, prevlsn));
}

static inline int __db_noop_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_noop_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_noop_desc, sizeof(__db_noop_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_alloc_42	49
typedef struct ___db_pg_alloc_42_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	DB_LSN	meta_lsn;
	db_pgno_t	meta_pgno;
	DB_LSN	page_lsn;
	db_pgno_t	pgno;
	uint32	ptype;
	db_pgno_t	next;
} __db_pg_alloc_42_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_alloc_42_desc[];
static inline int __db_pg_alloc_42_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_alloc_42_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_alloc_42_desc, sizeof(__db_pg_alloc_42_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_alloc	49
typedef struct ___db_pg_alloc_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	DB_LSN	meta_lsn;
	db_pgno_t	meta_pgno;
	DB_LSN	page_lsn;
	db_pgno_t	pgno;
	uint32	ptype;
	db_pgno_t	next;
	db_pgno_t	last_pgno;
} __db_pg_alloc_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_alloc_desc[];
static inline int
__db_pg_alloc_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, DB_LSN * meta_lsn, db_pgno_t meta_pgno, DB_LSN * page_lsn, db_pgno_t pgno,
    uint32 ptype, db_pgno_t next, db_pgno_t last_pgno)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_pg_alloc, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(*meta_lsn) + sizeof(uint32) +
	    sizeof(*page_lsn) + sizeof(uint32) + sizeof(uint32) +
	    sizeof(uint32) + sizeof(uint32),
	    __db_pg_alloc_desc, meta_lsn, meta_pgno, page_lsn, pgno, ptype, next, last_pgno));
}

static inline int __db_pg_alloc_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_alloc_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_alloc_desc, sizeof(__db_pg_alloc_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_free_42	50
typedef struct ___db_pg_free_42_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	meta_lsn;
	db_pgno_t	meta_pgno;
	DBT	header;
	db_pgno_t	next;
} __db_pg_free_42_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_free_42_desc[];
static inline int __db_pg_free_42_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_free_42_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_free_42_desc, sizeof(__db_pg_free_42_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_free	50
typedef struct ___db_pg_free_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	meta_lsn;
	db_pgno_t	meta_pgno;
	DBT	header;
	db_pgno_t	next;
	db_pgno_t	last_pgno;
} __db_pg_free_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_free_desc[];
static inline int
__db_pg_free_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, DB_LSN * meta_lsn, db_pgno_t meta_pgno, const DBT *header,
    db_pgno_t next, db_pgno_t last_pgno)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_pg_free, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(*meta_lsn) +
	    sizeof(uint32) + LOG_DBT_SIZE(header) + sizeof(uint32) +
	    sizeof(uint32),
	    __db_pg_free_desc, pgno, meta_lsn, meta_pgno, header, next, last_pgno));
}

static inline int __db_pg_free_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_free_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_free_desc, sizeof(__db_pg_free_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_cksum	51
typedef struct ___db_cksum_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
} __db_cksum_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_cksum_desc[];
static inline int
__db_cksum_log(ENV *env, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags)
{
	return (__log_put_record(env, NULL, txnp, ret_lsnp,
	    flags, DB___db_cksum, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN),
	    __db_cksum_desc));
}

static inline int __db_cksum_read(ENV *env, 
    void *data, __db_cksum_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    NULL, NULL, data, __db_cksum_desc, sizeof(__db_cksum_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_freedata_42	52
typedef struct ___db_pg_freedata_42_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	meta_lsn;
	db_pgno_t	meta_pgno;
	DBT	header;
	db_pgno_t	next;
	DBT	data;
} __db_pg_freedata_42_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_freedata_42_desc[];
static inline int __db_pg_freedata_42_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_freedata_42_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_freedata_42_desc, sizeof(__db_pg_freedata_42_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_freedata	52
typedef struct ___db_pg_freedata_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	meta_lsn;
	db_pgno_t	meta_pgno;
	DBT	header;
	db_pgno_t	next;
	db_pgno_t	last_pgno;
	DBT	data;
} __db_pg_freedata_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_freedata_desc[];
static inline int
__db_pg_freedata_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, DB_LSN * meta_lsn, db_pgno_t meta_pgno, const DBT *header,
    db_pgno_t next, db_pgno_t last_pgno, const DBT *data)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_pg_freedata, 1,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(*meta_lsn) +
	    sizeof(uint32) + LOG_DBT_SIZE(header) + sizeof(uint32) +
	    sizeof(uint32) + LOG_DBT_SIZE(data),
	    __db_pg_freedata_desc, pgno, meta_lsn, meta_pgno, header, next, last_pgno, data));
}

static inline int __db_pg_freedata_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_freedata_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_freedata_desc, sizeof(__db_pg_freedata_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_init	60
typedef struct ___db_pg_init_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DBT	header;
	DBT	data;
} __db_pg_init_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_init_desc[];
static inline int
__db_pg_init_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, const DBT *header, const DBT *data)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_pg_init, 1,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + LOG_DBT_SIZE(header) +
	    LOG_DBT_SIZE(data),
	    __db_pg_init_desc, pgno, header, data));
}

static inline int __db_pg_init_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_init_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_init_desc, sizeof(__db_pg_init_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_sort_44	61
typedef struct ___db_pg_sort_44_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	meta;
	DB_LSN	meta_lsn;
	db_pgno_t	last_free;
	DB_LSN	last_lsn;
	db_pgno_t	last_pgno;
	DBT	list;
} __db_pg_sort_44_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_sort_44_desc[];
static inline int __db_pg_sort_44_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_sort_44_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_sort_44_desc, sizeof(__db_pg_sort_44_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pg_trunc	66
typedef struct ___db_pg_trunc_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	meta;
	DB_LSN	meta_lsn;
	db_pgno_t	last_free;
	DB_LSN	last_lsn;
	db_pgno_t	next_free;
	db_pgno_t	last_pgno;
	DBT	list;
} __db_pg_trunc_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pg_trunc_desc[];
static inline int
__db_pg_trunc_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t meta, DB_LSN * meta_lsn, db_pgno_t last_free, DB_LSN * last_lsn,
    db_pgno_t next_free, db_pgno_t last_pgno, const DBT *list)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_pg_trunc, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(*meta_lsn) +
	    sizeof(uint32) + sizeof(*last_lsn) + sizeof(uint32) +
	    sizeof(uint32) + LOG_DBT_SIZE(list),
	    __db_pg_trunc_desc, meta, meta_lsn, last_free, last_lsn, next_free, last_pgno, list));
}

static inline int __db_pg_trunc_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pg_trunc_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pg_trunc_desc, sizeof(__db_pg_trunc_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_realloc	36
typedef struct ___db_realloc_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	prev_pgno;
	DB_LSN	page_lsn;
	db_pgno_t	next_free;
	uint32	ptype;
	DBT	list;
} __db_realloc_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_realloc_desc[];
static inline int
__db_realloc_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t prev_pgno, DB_LSN * page_lsn, db_pgno_t next_free, uint32 ptype,
    const DBT *list)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_realloc, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(*page_lsn) +
	    sizeof(uint32) + sizeof(uint32) + LOG_DBT_SIZE(list),
	    __db_realloc_desc, prev_pgno, page_lsn, next_free, ptype, list));
}

static inline int __db_realloc_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_realloc_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_realloc_desc, sizeof(__db_realloc_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_relink	147
typedef struct ___db_relink_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	db_pgno_t	new_pgno;
	db_pgno_t	prev_pgno;
	DB_LSN	lsn_prev;
	db_pgno_t	next_pgno;
	DB_LSN	lsn_next;
} __db_relink_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_relink_desc[];
static inline int
__db_relink_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, db_pgno_t new_pgno, db_pgno_t prev_pgno, DB_LSN * lsn_prev,
    db_pgno_t next_pgno, DB_LSN * lsn_next)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_relink, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(uint32) +
	    sizeof(uint32) + sizeof(*lsn_prev) + sizeof(uint32) +
	    sizeof(*lsn_next),
	    __db_relink_desc, pgno, new_pgno, prev_pgno, lsn_prev, next_pgno, lsn_next));
}

static inline int __db_relink_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_relink_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_relink_desc, sizeof(__db_relink_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_merge	148
typedef struct ___db_merge_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	lsn;
	db_pgno_t	npgno;
	DB_LSN	nlsn;
	DBT	hdr;
	DBT	data;
	int32	pg_copy;
} __db_merge_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_merge_desc[];
static inline int
__db_merge_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, DB_LSN * lsn, db_pgno_t npgno, DB_LSN * nlsn,
    const DBT *hdr, const DBT *data, int32 pg_copy)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_merge, 1,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(*lsn) +
	    sizeof(uint32) + sizeof(*nlsn) + LOG_DBT_SIZE(hdr) +
	    LOG_DBT_SIZE(data) + sizeof(uint32),
	    __db_merge_desc, pgno, lsn, npgno, nlsn, hdr, data, pg_copy));
}

static inline int __db_merge_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_merge_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_merge_desc, sizeof(__db_merge_args), reinterpret_cast<void **>(arg)));
}
#define	DB___db_pgno	149
typedef struct ___db_pgno_args {
	uint32 type;
	DB_TXN *txnp;
	DB_LSN prev_lsn;
	int32	fileid;
	db_pgno_t	pgno;
	DB_LSN	lsn;
	uint32	indx;
	db_pgno_t	opgno;
	db_pgno_t	npgno;
} __db_pgno_args;

extern __DB_IMPORT DB_LOG_RECSPEC __db_pgno_desc[];
static inline int
__db_pgno_log(DB *dbp, DB_TXN *txnp, DB_LSN *ret_lsnp, uint32 flags, db_pgno_t pgno, DB_LSN * lsn, uint32 indx, db_pgno_t opgno,
    db_pgno_t npgno)
{
	return (__log_put_record((dbp)->env, dbp, txnp, ret_lsnp,
	    flags, DB___db_pgno, 0,
	    sizeof(uint32) + sizeof(uint32) + sizeof(DB_LSN) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(*lsn) +
	    sizeof(uint32) + sizeof(uint32) + sizeof(uint32),
	    __db_pgno_desc, pgno, lsn, indx, opgno, npgno));
}

static inline int __db_pgno_read(ENV *env, 
    DB **dbpp, void *td, void *data, __db_pgno_args **arg)
{
	*arg = NULL;
	return (__log_read_record(env, 
	    dbpp, td, data, __db_pgno_desc, sizeof(__db_pgno_args), reinterpret_cast<void **>(arg)));
}
#endif
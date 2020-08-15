#ifndef LIBSTRUCTS_HASHTABLE_H
#define LIBSTRUCTS_HASHTABLE_H

#include "retcodes.h"
#include <stdlib.h>
#include <string.h>


typedef struct s_hashtable HTable;

typedef struct s_bucket {
    struct s_bucket *next;
    size_t hash;
    void *key;
    void *val;
}   Bucket;

typedef struct s_htable_iter {
    HTable *htable;
    size_t bucket_idx;
    Bucket *curr;
    Bucket *next;
}   HTableIter;


// hashes string
size_t string_hash(const void *key);
// hashes pointer itself
size_t ptr_hash(const void *key);


// integer's comparator
int int_cmp(void *i1, void *i2);


// no-op destructor;
void noop_destructor(void *p);

t_ret hashtable_new(HTable **ht,
                    size_t (*hashfunc)(const void *),
                    int (*key_cmp)(void *, void *),
                    void (*key_dstr)(void *),
                    void (*val_dstr)(void *));

t_ret hashtable_new_def(HTable **ht);
t_ret hashtable_set(HTable *ht, void *key, void *val);
void *hashtable_get(HTable *ht, void *key);
void *hashtable_delete(HTable *ht, void *key);
void hashtable_free(HTable *ht);
size_t hashtable_size(HTable *ht);
size_t hashtable_capacity(HTable *ht);

// iterator
void hashtable_new_iter(HTable *ht, HTableIter *hti);
t_ret hashtable_iter_next(HTableIter *hti, Bucket **b);


#endif//LIBSTRUCTS_HASHTABLE_H

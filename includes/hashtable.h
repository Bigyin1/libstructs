#ifndef LIBSTRUCTS_HASHTABLE_H
#define LIBSTRUCTS_HASHTABLE_H

#include <stdlib.h>
#include <string.h>
#include "retcodes.h"

typedef struct s_hashtable HTable;

// hashes string
size_t string_hash(const void *key);
// hashes pointer itself
size_t ptr_hash(const void *key);
// integer's comparator
int int_cmp(void* i1, void* i2);
// no-op destructor;
void default_destructor(void* p);

t_ret hashtable_new(HTable **ht,
                    size_t (*hashfunc) (const void *),
                    int (*key_cmp) (void*, void*),
                    void (*key_dstr) (void*),
                    void (*val_dstr) (void*));

t_ret hashtable_new_def(HTable **ht);
t_ret hashtable_set(HTable *ht, void *key, void *val);
void *hashtable_get(HTable *ht, void *key);
void *hashtable_delete(HTable *ht, void *key);
void hashtable_free(HTable *ht);
size_t hashtable_size(HTable *ht);
size_t hashtable_capacity(HTable *ht);


#endif//LIBSTRUCTS_HASHTABLE_H

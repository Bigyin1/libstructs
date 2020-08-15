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
static void default_destructor(void* p);

t_ret hashtable_new(HTable **ht,
                    size_t (*) (const void *),
                    int (*) (void*, void*),
                    void (*) (void*),
                    void (*) (void*));




#endif//LIBSTRUCTS_HASHTABLE_H

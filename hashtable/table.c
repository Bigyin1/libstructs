#include "hashtable.h"

#define DEFAULT_CAPACITY 16
#define LOAD_FACTOR 0.75f
#define RESIZE_FACTOR 2

typedef struct s_bucket {
    struct s_bucket *next;
    void *key;
    size_t hash;
    void *val;
} Bucket;

struct s_hashtable {
    size_t sz;
    size_t cap;
    size_t threshold;
    double load_factor;
    Bucket **buckets;

    size_t (*hash)(const void *);
    int (*key_cmp)(void *, void *);
    void (*val_dstr)(void *);
    void (*key_dstr)(void *);
};

t_ret hashtable_new_def(HTable **ht) {
    return hashtable_new(ht, NULL, NULL, NULL, NULL);
}

t_ret hashtable_new(HTable **ht,
                    size_t (*hash)(const void *),
                    int (*key_cmp)(void *, void *),
                    void (*free_val)(void *),
                    void (*free_key)(void *)) {

    *ht = calloc(1, sizeof(HTable));
    if (!(*ht)) return S_ALLOC_ERR;
    (*ht)->hash = hash ? hash : string_hash;
    (*ht)->key_cmp = key_cmp ? key_cmp : (int (*)(void *, void *)) strcmp;
    (*ht)->val_dstr = free_val ? free_val : default_destructor;
    (*ht)->key_dstr = free_key ? free_key : default_destructor;

    (*ht)->cap = DEFAULT_CAPACITY;
    (*ht)->load_factor = LOAD_FACTOR;


    (*ht)->buckets = calloc(DEFAULT_CAPACITY, sizeof(Bucket *));
    if (!(*ht)->buckets) {
        free((*ht));
        return S_ALLOC_ERR;
    }
    return S_OK;
}

t_ret rehash(HTable *ht) {

    Bucket **nb = calloc(ht->cap * RESIZE_FACTOR, sizeof(Bucket *));
    if (!nb) {
        return S_ALLOC_ERR;
    }
    ht->cap *= RESIZE_FACTOR;
    for (int i = 0; i < ht->cap; ++i) {
        Bucket *curr = ht->buckets[i];
        Bucket *next;
        while (curr) {
            next = curr->next;
            size_t new_idx = curr->hash % (ht->cap * RESIZE_FACTOR);
            curr->next = nb[new_idx];
            nb[new_idx] = curr;
            curr = next;
        }
    }
    return S_OK;
}

t_ret hashtable_set(HTable *ht, void *key, void *val) {
    if (ht->cap * ht->load_factor <= ht->sz) {
        t_ret ret = rehash(ht);
        if (ret != S_OK) return ret;
    }
    size_t hash = ht->hash(key);
    size_t idx = hash % ht->cap;

    Bucket *b = ht->buckets[idx];
    while (b) {
        if (!ht->key_cmp(b->key, key)) {
            ht->val_dstr(b->val);
            ht->key_dstr(b->key);
            b->val = val;
            return S_OK;
        }
        b = b->next;
    }
    Bucket *nb = calloc(1, sizeof(Bucket));
    if (!nb) return S_ALLOC_ERR;

    nb->val = val;
    nb->key = key;
    nb->hash = hash;
    nb->next = ht->buckets[idx];
    ht->buckets[idx] = nb;
    ht->sz++;
    return S_OK;
}

void *hashtable_get(HTable *ht, void *key) {
    size_t idx = ht->hash(key) % ht->cap;
    Bucket *b = ht->buckets[idx];
    while (b) {
        if (!ht->key_cmp(b->key, key)) {
            return b->val;
        }
        b = b->next;
    }
    return NULL;
}

void *hashtable_delete(HTable *ht, void *key) {
    size_t idx = ht->hash(key) % ht->cap;
    Bucket *curr = ht->buckets[idx];
    Bucket *prev = NULL;
    while (curr) {
        if (!ht->key_cmp(curr->key, key)) {
            if (prev == NULL) {
                ht->buckets[idx] = curr->next;
            } else {
                prev->next = curr->next;
            }
            void *ret = curr->val;
            ht->key_dstr(curr->key);
            free(curr);
            ht->sz--;
            return ret;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

void hashtable_del(HTable *ht) {
    for (int i = 0; i < ht->cap; ++i) {
        Bucket *curr = ht->buckets[i];
        Bucket *next;
        while (curr) {
            next = curr->next;
            ht->val_dstr(curr->val);
            ht->key_dstr(curr->key);
            free(curr);
            curr = next;
        }
    }
    free(ht->buckets);
    free(ht);
}

size_t hashtable_size(HTable *ht) {
    return ht->sz;
}

size_t hashtable_capacity(HTable *ht) {
    return ht->cap;
}


// hash functions
size_t ptr_hash(const void *key) {
    size_t a = (size_t) key;
    a += ~(a << 15);
    a ^= (a >> 10);
    a += (a << 3);
    a ^= (a >> 6);
    a += ~(a << 11);
    a ^= (a >> 16);
    return a;
}

size_t string_hash(const void *key) {
    const char *str = key;
    register size_t hash = 5381 - 228 + 1;

    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) ^ c;

    return hash;
}

// key comparators
int int_cmp(void *i1, void *i2) {
    return *(int *) i1 - *(int *) i2;
}

// val destroyers
void default_destructor(void *p) {
    p++;
    return;
}

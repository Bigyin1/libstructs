#include "slice.h"
#include "retcodes.h"
#include <stdlib.h>
#include <string.h>


#define MULT_FACTOR 2
#define THRESHOLD 1024
#define THRESHOLD_MULT_FACTOR 1.2

struct s_slice {
    void **buffer;
    size_t len;
    size_t cap;
};

t_ret slice_new(Slice **s, size_t len, size_t cap) {
    *s = calloc(1, sizeof(Slice));
    if (!(*s)) return S_ALLOC_ERR;

    cap = cap > 0 ? cap : 1;

    t_ret st = slice_grow(*s, cap);
    if (st != S_OK) {
        free(*s);
        return st;
    }
    (*s)->len = len;
    return S_OK;
}


size_t slice_len(Slice *s) {
    return s->len;
}

size_t slice_cap(Slice *s) {
    return s->cap;
}


t_ret slice_grow(Slice *s, size_t cap) {
    if (cap <= s->cap) return S_OK;

    void **nb = calloc(cap, sizeof(void *));
    if (!nb) return S_ALLOC_ERR;
    memcpy(nb, s->buffer, s->len*sizeof(void *));
    free(s->buffer);
    s->buffer = nb;
    s->cap = cap;
    return S_OK;
}

t_ret slice_insert(Slice *s, size_t idx, void *data) {
    if (idx > s->len) return S_RANGE_ERR;
    if (s->len == s->cap) {
        size_t nc;
        nc = s->cap >= THRESHOLD ? s->cap * THRESHOLD_MULT_FACTOR : s->cap * MULT_FACTOR;
        t_ret r = slice_grow(s, nc);
        if (r != S_OK) return r;
    }
    if (idx == s->len) {
        s->buffer[s->len++] = data;
        return S_OK;
    }

    memmove(s->buffer + idx + 1, s->buffer + idx, (s->len - idx)*sizeof(void *));
    s->len++;
    s->buffer[idx] = data;
    return S_OK;
}

t_ret slice_append(Slice *s, void *data) {
    return slice_insert(s, s->len, data);
}

t_ret slice_get(Slice *s, size_t idx, void **res) {
    if (idx >= s->len) return S_RANGE_ERR;

    *res = s->buffer[idx];
    return S_OK;
}

void slice_sort(Slice *s, int (*cmp)(const void *, const void *)) {
    if (s->len <= 1) return;
    qsort(s->buffer, s->len, sizeof(void *), cmp);
    return;
}

void slice_map(Slice *s, void (*m)(void *)) {
    for (int i = 0; i < s->len; ++i) {
        m(s->buffer[i]);
    }
}

void slice_delete(Slice *s, void (*cf)(void *)) {
    if (s->len == 0) {
        return;
    }
    for (int i = 0; i < s->len; ++i) {
        if (cf != NULL)
            cf(s->buffer[i]);
    }
    free(s->buffer);
    free(s);
}

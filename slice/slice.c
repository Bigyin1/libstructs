#include "slice.h"
#include "retcodes.h"
#include <stdlib.h>
#include <string.h>


struct s_slice {
    void **buffer;
    size_t len;
    size_t cap;
};

t_ret slice_new(Slice **s, size_t len, size_t cap) {
    *s = calloc(1, sizeof(Slice));
    if (!(*s)) return S_ALLOC_ERR;

    cap = cap > 0 ? cap : 1;
    (*s)->len = len;
    (*s)->cap = cap;

    (*s)->buffer = calloc(cap, sizeof(void *));
    if (!(*s)->buffer) {
        free(*s);
        return S_ALLOC_ERR;
    }
    return S_OK;
}

t_ret slice_grow(Slice *s, size_t cap) {
    if (cap <= s->cap) return S_OK;

    void **nb = calloc(cap, sizeof(void *));
    if (!nb) return S_ALLOC_ERR;
    memcpy(nb, s->buffer, s->len);
    free(s->buffer);
    s->buffer = nb;
    return S_OK;
}

t_ret slice_append(Slice *s, void *data) {
    if (s->len == s->cap) {
        size_t nc;
        nc = s->cap >= THRESHOLD ? s->cap * THRESHOLD_MULT_FACTOR : s->cap * MULT_FACTOR;
        t_ret r = slice_grow(s, nc);
        if (r != S_OK) return r;
    }

    s->buffer[s->len++] = data;
    return S_OK;
}

t_ret slice_get(Slice *s, size_t idx, void **res) {
    if (idx >= s->len) return S_RANGE_ERR;

    *res = s->buffer[idx];
    return S_OK;
}

t_ret slice_sort(Slice *s) {
    if (s->len <= 1) return S_OK;
    qsort(s->buffer, )
}


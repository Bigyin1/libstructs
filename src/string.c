//
// Created by sergey on 24.01.2021.
//

#include "structs/str.h"
#include <string.h>

#define MULT_FACTOR 2
#define THRESHOLD 1024
#define THRESHOLD_MULT_FACTOR 1.2

struct s_string {
    char *buffer;
    size_t len;
    size_t cap;
};

t_ret string_new(String **s, size_t len, size_t cap) {
    *s = calloc(1, sizeof(String));
    if (!(*s)) return S_ALLOC_ERR;

    cap = cap > 0 ? cap : 1;

    t_ret st = string_grow(*s, cap);
    if (st != S_OK) {
        free(*s);
        return st;
    }
    (*s)->len = len;
    return S_OK;
}


size_t string_len(String *s) {
    return s->len;
}

size_t string_cap(String *s) {
    return s->cap;
}


t_ret string_grow(String *s, size_t cap) {
    if (cap <= s->cap) return S_OK;

    char *nb = calloc(cap + 1, sizeof(char));
    if (!nb) return S_ALLOC_ERR;
    memcpy(nb, s->buffer, s->len * sizeof(char));
    free(s->buffer);
    s->buffer = nb;
    s->cap = cap;
    return S_OK;
}

t_ret string_insert(String *s, size_t idx, char c) {
    if (idx > s->len) return S_RANGE_ERR;
    if (s->len == s->cap) {
        size_t nc;
        nc = s->cap >= THRESHOLD ? s->cap * THRESHOLD_MULT_FACTOR : s->cap * MULT_FACTOR;
        t_ret r = string_grow(s, nc);
        if (r != S_OK) return r;
    }
    if (idx == s->len) {
        s->buffer[s->len++] = c;
        return S_OK;
    }

    memmove(s->buffer + idx + 1, s->buffer + idx, (s->len - idx) * sizeof(char));
    s->len++;
    s->buffer[idx] = c;
    return S_OK;
}

t_ret string_append(String *s, char c) {
    return string_insert(s, s->len, c);
}

char string_get(String *s, size_t idx) {
    if (idx >= s->len) return 0;

    return s->buffer[idx];
}

String *string_slice(String *s, size_t start, size_t end) {
    if (start >= s->len || end > s->len)
        return NULL;

    String *ns = calloc(1, sizeof(String));
    if (string_new(&ns, end - start, end - start) != S_OK) return NULL;
    memcpy(ns->buffer, s->buffer + start, end - start);
    return ns;
}

t_ret string_erase_from_idx(String *s, size_t idx) {
    if (idx >= s->len) return S_RANGE_ERR;
    s->len--;
    memmove(s->buffer + idx, s->buffer + idx + 1, s->len - idx);
    s->buffer[s->len] = 0;
    return S_OK;
}

t_ret string_copy(String **dst, String *src) {

    *dst = calloc(1, sizeof(String));
    if (!*dst) return S_ALLOC_ERR;
    (*dst)->buffer = calloc(src->cap, sizeof(char));
    if (!(*dst)->buffer) return S_ALLOC_ERR;
    memcpy((*dst)->buffer, src->buffer, src->len);
    return S_OK;
}


void string_free(String *s) {
    free(s->buffer);
    free(s);
}

char *string_to_c_str(String *s) {
    return s->buffer;
}
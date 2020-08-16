#ifndef LIBSTRUCTS_SLICE_H
#define LIBSTRUCTS_SLICE_H

#include "retcodes.h"
#include <stdlib.h>


typedef struct s_slice Slice;

void slice_sort(Slice *s, int (*cmp)(const void *, const void *));
t_ret slice_new(Slice **s, size_t len, size_t cap);
void slice_delete(Slice *s, void (*cf)(void *));
t_ret slice_grow(Slice *s, size_t cap);
t_ret slice_insert(Slice *s, size_t idx, void *data);
t_ret slice_append(Slice *s, void *data);
t_ret slice_get(Slice *s, size_t idx, void **res);
void slice_map(Slice *s, void (*m)(void *));
size_t slice_len(Slice *s);
size_t slice_cap(Slice *s);

#endif//LIBSTRUCTS_SLICE_H


#ifndef LIBFT_LLIST_H
#define LIBFT_LLIST_H

#include "retcodes.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_list List;

typedef struct s_node {
    void *data;
    struct s_node *next;
    struct s_node *prev;
} Node;

t_ret new_list(List **l);
t_ret list_push_back(List *l, void *data);
t_ret list_push_front(List *l, void *data);
t_ret list_pop_front(List *l, void **data);
t_ret list_pop_back(List *l, void **data);
t_ret list_get_head(List *l, Node **n);
void list_sort(List *l, int (*cmp)(void *, void *));
t_ret list_get_tail(List *l, Node **n);
void list_reverse(List *l);
t_ret filter_list_new(List *l, List **nl, bool (*f)(void *));
t_ret filter_list_mod(List *l, bool (*f)(void *));
void delete_list(List *l, void (*cf)(void *data));
size_t list_size(List *l);


#endif//LLIST_H

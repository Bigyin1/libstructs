#include "structs/list.h"
#include "structs/retcodes.h"


struct s_list {
    Node *head;
    Node *tail;
    size_t size;
};


void unlink_node(List *l, Node *n) {
    if (!n->prev && !n->next) {
        l->head = NULL;
        l->tail = NULL;
        return;
    }

    if (!n->prev) {
        l->head = n->next;
        l->head->prev = NULL;
        return;
    }
    if (!n->next) {
        l->tail = n->prev;
        l->tail->next = NULL;
        return;
    }
    n->prev->next = n->next;
    n->next->prev = n->prev;
}

size_t list_size(List *l) {
    return l->size;
}

t_ret new_list(List **l) {
    *l = calloc(1, sizeof(List));
    if (!(*l)) return S_ALLOC_ERR;

    return S_OK;
}

t_ret list_push_back(List *l, void *data) {
    Node *n = calloc(1, sizeof(Node));
    if (!n) return S_ALLOC_ERR;

    n->data = data;
    if (l->size == 0) {
        l->head = n;
        l->tail = n;
        l->size++;
        return S_OK;
    }

    l->size++;
    l->tail->next = n;
    n->prev = l->tail;
    l->tail = n;
    return S_OK;
}

t_ret list_push_front(List *l, void *data) {
    Node *n = calloc(1, sizeof(Node));
    if (!n) return S_ALLOC_ERR;

    n->data = data;
    if (l->size == 0) {
        l->head = n;
        l->tail = n;
        l->size++;
        return S_OK;
    }

    l->size++;
    l->head->prev = n;
    n->next = l->head;
    l->head = n;
    return S_OK;
}

t_ret list_pop_front(List *l, void **data) {
    Node *tmp;
    if (l->size == 0) {
        return S_NOT_EXIST;
    }

    *data = l->head->data;
    l->size--;

    tmp = l->head;
    unlink_node(l, l->head);
    free(tmp);
    return S_OK;
}

t_ret list_pop_back(List *l, void **data) {
    Node *tmp;
    if (l->size == 0) {
        return S_NOT_EXIST;
    }

    *data = l->tail->data;
    l->size--;

    tmp = l->tail;
    unlink_node(l, l->tail);
    free(tmp);
    return S_OK;
}

t_ret list_filter_new(List *l, List **nl, bool (*f)(void *)) {
    Node *curr;

    if (l->size == 0) return S_RANGE_ERR;
    t_ret r = new_list(nl);
    if (r != S_OK) return r;

    curr = l->head;
    while (curr) {
        if (f(curr->data)) {
            r = list_push_back(*nl, curr->data);
            if (r != S_OK) {
                list_free(*nl, NULL);
                return r;
            }
        }
        curr = curr->next;
    }
    return S_OK;
}

t_ret list_filter_mod(List *l, bool (*f)(void *)) {
    Node *next, *curr;

    if (l->size == 0) return S_RANGE_ERR;
    curr = l->head;
    while (curr) {
        next = curr->next;
        if (f(curr->data)) {
            unlink_node(l, curr);
            free(curr);
            l->size--;
        }
        curr = next;
    }
    return S_OK;
}

void list_sort(List *l, int (*cmp)(void *, void *)) {
    size_t sz = l->size;
    while (--sz) {
        Node *n = l->head;
        for (int i = 0; i < sz; ++i) {
            if (cmp(n->data, n->next->data) > 0) {
                void *tmp = n->data;
                n->data = n->next->data;
                n->next->data = tmp;
            }
            n = n->next;
        }
    }
}

void list_reverse(List *l) {
    if (l->size == 0 || l->size == 1) return;

    Node *tmp;
    Node *n = l->head;
    while (n) {
        tmp = n->next;
        n->next = n->prev;
        n->prev = tmp;
        n = n->prev;
    }
    tmp = l->head;
    l->head = l->tail;
    l->tail = tmp;
}

void list_foreach(List *l, void (*f)(void *)) {
    Node *n = l->head;

    while (n) {
        f(n->data);
        n = n->next;
    }
}

t_ret list_get_head(List *l, Node **n) {
    if (l->size == 0) {
        return S_NOT_EXIST;
    }
    (*n) = l->head;
    return S_OK;
}

t_ret list_get_tail(List *l, Node **n) {
    if (l->size == 0) {
        return S_NOT_EXIST;
    }
    (*n) = l->tail;
    return S_OK;
}


void list_free(List *l, void (*cf)(void *)) {
    Node *next, *curr;
    if (l->size == 0) {
        free(l);
        return;
    }
    curr = l->head;
    while (curr != NULL) {
        next = curr->next;
        if (cf != NULL)
            cf(curr->data);
        free(curr);
        curr = next;
    }
    free(l);
}

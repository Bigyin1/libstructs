#include "CppUTest/TestHarness_c.h"
#include "list.h"
#include "retcodes.h"
#include <stdio.h>

static List *l;

TEST_GROUP_C_SETUP(ListTest) {
    CHECK_EQUAL_C_INT(S_OK, new_list(&l));
}

TEST_C(ListTest, PushPopFront) {
    char *exp1 = "test1";
    CHECK_EQUAL_C_INT(S_OK, push_front(l, exp1));
    char *exp2 = "test2";
    CHECK_EQUAL_C_INT(S_OK, push_front(l, exp2));


    char *actual;
    CHECK_EQUAL_C_INT(S_OK, pop_front(l, (void **) &actual));
    CHECK_EQUAL_C_STRING(exp2, actual);

    CHECK_EQUAL_C_INT(S_OK, pop_front(l, (void **) &actual));
    CHECK_EQUAL_C_STRING(exp1, actual);
}

TEST_C(ListTest, PushPopBack) {
    char *exp1 = "test1";
    CHECK_EQUAL_C_INT(S_OK, push_back(l, exp1));
    char *exp2 = "test2";
    CHECK_EQUAL_C_INT(S_OK, push_back(l, exp2));


    char *actual;
    CHECK_EQUAL_C_INT(S_OK, pop_back(l, (void **) &actual));
    CHECK_EQUAL_C_STRING(exp2, actual);

    CHECK_EQUAL_C_INT(S_OK, pop_back(l, (void **) &actual));
    CHECK_EQUAL_C_STRING(exp1, actual);
}


char *data[] = {"test1", "test2", "test3"};
bool cmp1(void *str) {
    char *st1 = (char *) str;
    char *st2 = data[1];
    return strcmp(st1, st2) >= 0;
}

TEST_C(ListTest, FilterListNew) {

    for (int i = 0; i < sizeof(data) / sizeof(char *); ++i) {
        CHECK_EQUAL_C_INT(S_OK, push_back(l, data[i]));
    }

    List *nl;
    CHECK_EQUAL_C_INT(S_OK, filter_list_new(l, &nl, cmp1));
    CHECK_EQUAL_C_INT(sizeof(data) / sizeof(char *), list_size(l));
    CHECK_EQUAL_C_INT(2, list_size(nl));


    Node *head;
    CHECK_EQUAL_C_INT(S_OK, list_get_head(nl, &head));
    for (int i = 1; i < sizeof(data) / sizeof(char *); ++i) {
        CHECK_EQUAL_C_STRING(data[i], head->data);
        head = head->next;
    }
    CHECK_C(!head);

    delete_list(nl, NULL);
}

bool cmp2(void *str) {
    char *st1 = (char *) str;
    char *st2 = data[1];
    return strcmp(st1, st2) == 0;
}

TEST_C(ListTest, FilterListMod) {

    for (int i = 0; i < sizeof(data) / sizeof(char *); ++i) {
        CHECK_EQUAL_C_INT(S_OK, push_back(l, data[i]));
    }

    CHECK_EQUAL_C_INT(S_OK, filter_list_mod(l, cmp2));
    CHECK_EQUAL_C_INT(2, list_size(l));


    Node *head;
    CHECK_EQUAL_C_INT(S_OK, list_get_head(l, &head));
    CHECK_EQUAL_C_STRING(data[0], head->data);
    CHECK_EQUAL_C_STRING(data[2], head->next->data);
    CHECK_C(!head->next->next);
}


TEST_C(ListTest, SortList) {
    CHECK_EQUAL_C_INT(S_OK, push_back(l, "d"));
    CHECK_EQUAL_C_INT(S_OK, push_front(l, "c"));
    CHECK_EQUAL_C_INT(S_OK, push_back(l, "a"));

    list_sort(l, (int (*)(void *, void *)) strcmp);
    Node *head;
    CHECK_EQUAL_C_INT(S_OK, list_get_head(l, &head));
    while (head->next) {
        if (strcmp(head->data, head->next->data) > 0) {
            FAIL_C();
        }
        head = head->next;
    }
}

TEST_GROUP_C_TEARDOWN(ListTest) {
    delete_list(l, NULL);
}

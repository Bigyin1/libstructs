#include "CppUTest/TestHarness_c.h"
#include "structs/retcodes.h"
#include "structs/slice.h"
#include <string.h>

static Slice *s;

TEST_GROUP_C_SETUP(SliceTest) {
    CHECK_EQUAL_C_INT(S_OK, slice_new(&s, 0, 0));
    CHECK_EQUAL_C_INT(0, slice_len(s));
    CHECK_EQUAL_C_INT(1, slice_cap(s));
}

TEST_C(SliceTest, Append) {
    char *td[] = {strdup("test1"), strdup("test2")};

    CHECK_EQUAL_C_INT(S_OK, slice_append(s, td[0]));
    CHECK_EQUAL_C_INT(S_OK, slice_append(s, td[1]));

    char *ret;
    CHECK_EQUAL_C_INT(S_OK, slice_get(s, 0, (void **) &ret));
    CHECK_EQUAL_C_STRING(td[0], ret);
    CHECK_EQUAL_C_INT(S_OK, slice_get(s, 1, (void **) &ret));
    CHECK_EQUAL_C_STRING(td[1], ret);
}

TEST_C(SliceTest, Insert) {
    char *td[] = {strdup("test1"), strdup("test2"), strdup("test3")};
    char *ins = strdup("inserted");
    CHECK_EQUAL_C_INT(S_OK, slice_append(s, td[0]));
    CHECK_EQUAL_C_INT(S_OK, slice_append(s, td[1]));
    CHECK_EQUAL_C_INT(S_OK, slice_append(s, td[2]));
    int s_len = slice_len(s);

    char *ret;
    CHECK_EQUAL_C_INT(S_OK, slice_insert(s, 1, ins));

    CHECK_EQUAL_C_INT(S_OK, slice_get(s, 1, (void **) &ret));
    CHECK_EQUAL_C_STRING(ins, ret);
    CHECK_EQUAL_C_INT(s_len+1, slice_len(s));
    CHECK_EQUAL_C_INT(S_OK, slice_get(s, 2, (void **) &ret));
    CHECK_EQUAL_C_STRING(td[1], ret);
    CHECK_EQUAL_C_INT(S_OK, slice_get(s, 3, (void **) &ret));
    CHECK_EQUAL_C_STRING(td[2], ret);
}



TEST_GROUP_C_TEARDOWN(SliceTest) {
    slice_delete(s, free);
}
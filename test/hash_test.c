#include "CppUTest/TestHarness_c.h"
#include "hashtable.h"
#include "retcodes.h"
#include "slice.h"
#include <stdio.h>
#include <string.h>

static HTable *ht;

TEST_GROUP_C_SETUP(HTableTest) {
    CHECK_EQUAL_C_INT(S_OK, hashtable_new(&ht, NULL, NULL, free, free));
}

TEST_C(HTableTest, SetGet) {
    Slice *keys;
    Slice *vals;
    CHECK_EQUAL_C_INT(S_OK, slice_new(&keys, 0, 0));
    CHECK_EQUAL_C_INT(S_OK, slice_new(&vals, 0, 0));
    size_t elems = 1050;
    for (int i = 0; i < elems; ++i) {
        char *str = calloc(10, sizeof(char));
        sprintf(str, "%d", i);
        strcat(str, "test");
        CHECK_EQUAL_C_INT(S_OK, slice_append(keys, str));
        CHECK_EQUAL_C_INT(S_OK, slice_append(vals, strdup(str)));
    }
    for (int i = 0; i < slice_len(keys); ++i) {
        void *key, *val;
        slice_get(keys, i, &key);
        slice_get(vals, i, &val);
        CHECK_EQUAL_C_INT(S_OK, hashtable_set(ht, key, val));
    }
    CHECK_EQUAL_C_INT(elems, hashtable_size(ht));

    for (int i = 0; i < slice_len(keys); ++i) {
        void *key, *val, *expval;
        slice_get(keys, i, &key);
        slice_get(vals, i, &expval);

        val = hashtable_get(ht, key);
        CHECK_EQUAL_C_STRING(expval, val);
        val = hashtable_delete(ht, key);
        CHECK_EQUAL_C_STRING(expval, val);
        free(val);
    }

    slice_delete(keys, NULL);
    slice_delete(vals, NULL);
}

TEST_GROUP_C_TEARDOWN(HTableTest) {
    hashtable_free(ht);
}

#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness_c.h"

TEST_GROUP_C_WRAPPER(SliceTest) {
    TEST_GROUP_C_SETUP_WRAPPER(SliceTest);
    TEST_GROUP_C_TEARDOWN_WRAPPER(SliceTest);
};

TEST_C_WRAPPER(SliceTest, Append)
TEST_C_WRAPPER(SliceTest, Insert)

int main(int argc, char **argv) {
    return RUN_ALL_TESTS(argc, argv);
}
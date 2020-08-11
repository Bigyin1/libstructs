#include "CppUTest/TestHarness_c.h"
#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP_C_WRAPPER(ListTest)
{
    TEST_GROUP_C_SETUP_WRAPPER(ListTest);
    TEST_GROUP_C_TEARDOWN_WRAPPER(ListTest);
};

TEST_C_WRAPPER(ListTest, PushPopFront)
TEST_C_WRAPPER(ListTest, PushPopBack)
TEST_C_WRAPPER(ListTest, FilterListNew)
TEST_C_WRAPPER(ListTest, FilterListMod)
TEST_C_WRAPPER(ListTest, SortList)
TEST_C_WRAPPER(ListTest, ReverseList)

int main(int argc, char **argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
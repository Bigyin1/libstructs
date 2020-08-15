#include "CppUTest/TestHarness_c.h"
#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP_C_WRAPPER(HTableTest)
{
    TEST_GROUP_C_SETUP_WRAPPER(HTableTest);
    TEST_GROUP_C_TEARDOWN_WRAPPER(HTableTest);
};

TEST_C_WRAPPER(HTableTest, SetGet)

int main(int argc, char **argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
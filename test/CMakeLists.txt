find_package(PkgConfig)
pkg_check_modules(CPPUTEST REQUIRED cpputest>=3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPPUTEST_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPPUTEST_C_FLAGS}")


include_directories(../includes ${CPPUTEST_INCLUDE_DIRS})

add_executable(list_test list_test.c listTest.cpp)
target_link_libraries(list_test ${PROJECT_NAME} ${CPPUTEST_LDFLAGS})
add_executable(slice_test slice_test.c sliceTest.cpp)
target_link_libraries(slice_test ${PROJECT_NAME} ${CPPUTEST_LDFLAGS})
add_executable(hashtable_test hash_test.c hashTest.cpp)
target_link_libraries(hashtable_test ${PROJECT_NAME} ${CPPUTEST_LDFLAGS})

enable_testing()
add_test(ListTest list_test -c -v)
add_test(SliceTest slice_test -c -v)
add_test(HashtableTest hashtable_test -c -v)
cmake_minimum_required(VERSION 3.17)
project(structs C)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
enable_language(C)
enable_language(CXX)

add_subdirectory(src)

if(NOT IS_SUBPROJECT)
    add_subdirectory(test)
endif()
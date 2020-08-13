file(GLOB source_files "*.c")

include_directories(../includes)
add_library(lib_slice ${source_files})
file(GLOB source_files "*.c")
file(GLOB header_files "../includes/structs/*.h")

add_library(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME} PUBLIC ../includes)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_compile_options(${PROJECT_NAME} PUBLIC "SHELL:-fno-omit-frame-pointer" "SHELL:-fsanitize=address")
    target_link_options(${PROJECT_NAME} PUBLIC "SHELL:-fsanitize=address")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${header_files}")

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
        )

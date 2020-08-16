file(GLOB source_files "*.c")
file(GLOB header_files "../includes/structs/*.h")

add_library(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME} PUBLIC ../includes)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${header_files}")

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
        )

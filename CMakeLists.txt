cmake_minimum_required(VERSION 3.9)

project(cid3)

set(PROJECT_NAME cid3)
set(EXAMPLE_NAME cid3_example)

include_directories("./inc")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SOURCE_FILES "./src/*c")

add_library(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(${EXAMPLE_NAME} "main.c")
target_link_libraries(${EXAMPLE_NAME} ${PROJECT_NAME})


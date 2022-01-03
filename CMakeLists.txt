cmake_minimum_required(VERSION 3.0.0)
project(myfs VERSION 0.1.0)

include_directories(./include)

aux_source_directory(src myfs_src) 

add_library(myfs SHARED ${myfs_src})


aux_source_directory(example/test test_src) 

add_executable(myfs_test ${test_src})


aux_source_directory(example/shell shell_src) 

add_executable(shell_test ${shell_src})

target_link_libraries(myfs_test myfs)
target_link_libraries(shell_test myfs)

add_subdirectory(example/aes)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

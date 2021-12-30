cmake_minimum_required(VERSION 3.0.0)
project(myfs VERSION 0.1.0)

include_directories(./include)

aux_source_directory(src myfs_src) 

add_library(myfs SHARED ${myfs_src})

add_executable(myfs_test example/test.c)

target_link_libraries(myfs_test myfs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

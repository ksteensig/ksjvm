cmake_minimum_required(VERSION 3.10)
project(ksjvm)

set(CMAKE_C_STANDARD 11)

IF (WIN32)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
ELSE()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -lrt")
ENDIF()

include_directories(include)
add_subdirectory(src)

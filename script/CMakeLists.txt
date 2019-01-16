cmake_minimum_required(VERSION 2.8)

project(tars_cpp)

set(CMAKE_VERBOSE_MAKEFILE off)

#set(MYSQL_DIR_INC "/usr/local/mysql/include")
#set(MYSQL_DIR_LIB "/usr/local/mysql/lib")
set(MYSQL_DIR_INC "/usr/local/mysql/include/mysql")
set(MYSQL_DIR_LIB "/usr/local/mysql/lib/mysql")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O2 -Wall -Wno-deprecated")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall -Wno-deprecated")

#set(CMAKE_BUILD_TYPE "Debug")

if(ENABLE_TARS_GCOV AND NOT WIN32 AND NOT APPLE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS}     -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
endif()


set(TARS_VERSION "1.1.0")
add_definitions(-DTARS_VERSION="${TARS_VERSION}")
set(TARS_SSL 0)
add_definitions(-DTARS_SSL=${TARS_SSL})
set(TARS_HTTP2 0)
add_definitions(-DTARS_HTTP2=${TARS_HTTP2})

set(INSTALL_PREFIX "/usr/local/tars/cpp")

set(CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX})

add_subdirectory(util)
add_subdirectory(tools)

set(TARS2CPP "${tools_BINARY_DIR}/tars2cpp/tars2cpp")

add_subdirectory(servant)


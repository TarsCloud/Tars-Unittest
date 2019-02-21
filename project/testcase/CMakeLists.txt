project(tars_testcase)
cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -lgtest")
set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} -lgtest")
message(STATUS "start build tars test project:" ${CMAKE_CURRENT_SOURCE_DIR})

set(TARS_CODE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
set(TARS_TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(TARS_TEST_INCLUDE ${TARS_TEST_ROOT}/testcode/include)

include(${TARS_TEST_ROOT}/project/cmakeConf/pre_make.cmake)

include_directories(
${TARS_TEST_PROTOCOL_PATH}
${TARS_TEST_INCLUDE}
)

aux_source_directory(${TEST_CODE_SRC}/testcase TESTCASE_SRC)
#aux_source_directory(${TEST_CODE_SRC}/testcase/util  TESTCASE_SRC)
#aux_source_directory(${TEST_CODE_SRC}/testcase/framework/testAdminRegistry  TESTCASE_SRC)
aux_source_directory(${TEST_CODE_SRC}/utils       TESTCASE_SRC)
aux_source_directory(${TEST_CODE_SRC}/stub       TESTCASE_SRC)
aux_source_directory(${TEST_CODE_SRC}/stub/MockProxy       TESTCASE_SRC)
aux_source_directory(${TEST_CODE_SRC}/stub/PushServerDemo       TESTCASE_SRC)
aux_source_directory(${TEST_CODE_SRC}/stub/RegisteryStub       TESTCASE_SRC)
aux_source_directory(${TARS_TEST_PROTOCOL_PATH}/TarsTest/TestcaseServer TESTCASE_SRC)
list(APPEND TESTCASE_SRC  ${TEST_CODE_SRC}/main.cpp)
#file(GLOB TESTCASE_SRC "${TEST_CODE_SRC}/main.cpp")

message(STATUS "TAF_LIB:" ${TAF_LIB})

set(GOOGLETEST_LIB /usr/local/lib64)

link_directories(
${TARS_UTIL_LIB}
${TARS_SERVANT_LIB}
${GOOGLETEST_LIB}
)

add_executable(testcase ${TESTCASE_SRC})

if(_USE_OPENTRACKING)
target_link_libraries(testcase tarsservant tarsutil gtest gtest_main pthread z pthread opentracing zipkin_opentracing zipkin curl)
else()
target_link_libraries(testcase tarsservant tarsutil gtest pthread z)
endif()

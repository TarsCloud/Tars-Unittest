project(unit_test_server)
cmake_minimum_required(VERSION 2.6.2)

message(STATUS "start build unit test project:" ${CMAKE_CURRENT_SOURCE_DIR})

set(TARS_CODE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
set(TARS_TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${TARS_TEST_ROOT}/project/cmakeConf/pre_make.cmake)

message(STATUS "TARS_TEST_PROTOCOL_PATH:" ${TARS_TEST_PROTOCOL_PATH})
##aux_source_directory(${TARS_TEST_PROTOCOL_PATH}/firstdemo UNIT_TEST_SRV)
aux_source_directory(${TARS_TEST_PROTOCOL_PATH}/TarsTest/UnitTest UNIT_TEST_SRV)

link_directories(
${TARS_UTIL_LIB}
${TARS_SERVANT_LIB}
)


add_executable(unitTestServer ${UNIT_TEST_SRV})

if(_USE_OPENTRACKING)
target_link_libraries(unitTestServer tarsservant tarsutil pthread opentracing zipkin_opentracing zipkin curl)
else()
target_link_libraries(unitTestServer tarsservant tarsutil pthread)
endif()

project(log_server)
cmake_minimum_required(VERSION 2.6.2)

message(STATUS "start log server test project:" ${CMAKE_CURRENT_SOURCE_DIR})

set(TARS_CODE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
set(TARS_TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${TARS_TEST_ROOT}/project/cmakeConf/pre_make.cmake)
message(STATUS "TARS_LOG_SERVER_PATH:" ${TARS_LOG_SERVER_PATH})
aux_source_directory(${TARS_LOG_SERVER_PATH}/ LOG_SRV)
link_directories(
${TARS_UTIL_LIB}
${TARS_SERVANT_LIB}
)

add_executable(logServer ${LOG_SRV})

if(_USE_OPENTRACKING)
target_link_libraries(logServer tarsservant tarsutil pthread opentracing zipkin_opentracing zipkin curl)
else()
target_link_libraries(logServer tarsservant tarsutil pthread)
endif()

project(stat_server)
cmake_minimum_required(VERSION 2.6.2)

message(STATUS "start stat server test project:" ${CMAKE_CURRENT_SOURCE_DIR})

set(TARS_CODE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
set(TARS_TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${TARS_TEST_ROOT}/project/cmakeConf/pre_make.cmake)
message(STATUS "TARS_STAT_SERVER_PATH:" ${TARS_STAT_SERVER_PATH})
aux_source_directory(${TARS_STAT_SERVER_PATH}/ STAT_SRV)
link_directories(
${TARS_UTIL_LIB}
${TARS_SERVANT_LIB}
)

add_executable(statServer ${STAT_SRV})

target_link_libraries(statServer tarsservant tarsutil pthread)

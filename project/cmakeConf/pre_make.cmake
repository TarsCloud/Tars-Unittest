set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -g -O2 -Wall -Wno-deprecated")
set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} -g -O2 -Wall -Wno-deprecated ")

OPTION(ENABLE_GCOV "Enable gcov (debug, Linux builds only)" ON)

if(ENABLE_GCOV AND NOT WIN32 AND NOT APPLE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS}     -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
endif()

set(TARS_UTIL_INC        ${TARS_CODE_ROOT}/util/include)
set(TARS_SERVANT_INC        ${TARS_CODE_ROOT}/servant)
set(TARS_PROTOCOL_INC ${TARS_CODE_ROOT}/unittest/protocol/TarsTest)

set(TARS_UTIL_LIB        ${TARS_CODE_ROOT}/util/lib)
set(TARS_SERVANT_LIB        ${TARS_CODE_ROOT}/servant/lib)

set(TARS_TEST_PROTOCOL_PATH        ${TARS_TEST_ROOT}/protocol)
set(TEST_CODE_SRC      ${TARS_TEST_ROOT}/testcode/source)
set(TARS_LOG_SERVER_PATH    ${TARS_TEST_ROOT}/framework/LogServer)
set(TARS_STAT_SERVER_PATH    ${TARS_TEST_ROOT}/framework/StatServer)
include_directories(
${TARS_UTIL_INC}
${TARS_SERVANT_INC}
${TARS_PROTOCOL_INC}
)

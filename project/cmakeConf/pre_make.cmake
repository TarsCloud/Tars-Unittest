set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -g -O2 -Wall -Wno-deprecated -pthread")
set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} -g -O2 -Wall -Wno-deprecated -pthread")

OPTION(ENABLE_GCOV "Enable gcov (debug, Linux builds only)" ON)
set(_USE_OPENTRACKING $ENV{_USE_OPENTRACKING})

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
set(GTEST_LIB_PATH /usr/local/lib64)

if(_USE_OPENTRACKING)
#set(CURL_LIB_PATH /usr/local/lib)
add_definitions(-D_USE_OPENTRACKING=1)
set(CURL_LIB_PATH /usr/lib64)
set(ZIPKIN_OPENTRACKING_LIB_PATH /usr/local/lib)
set(ZIPKIN_LIB_PATH /usr/local/lib)
set(OPENTRACKING_LIB_PATH /usr/local/lib)
set(TRACKING_LIBS_PATH "${ZIPKIN_OPENTRACKING_LIB_PATH} ${ZIPKIN_LIB_PATH} ${OPENTRACKING_LIB_PATH}")
set(TRACKING_LIBS "opentracing zipkin_opentracing zipkin curl")
link_directories(
${TARS_UTIL_LIB}
${TARS_SERVANT_LIB}
${GTEST_LIB_PATH}
${TRACKING_LIBS_PATH}
${CURL_LIB_PATH}
)
else()
link_directories(
${TARS_UTIL_LIB}
${TARS_SERVANT_LIB}
${GTEST_LIB_PATH}
)
endif()

set(TARS_TEST_PROTOCOL_PATH        ${TARS_TEST_ROOT}/protocol)
set(TEST_CODE_SRC      ${TARS_TEST_ROOT}/testcode/source)
set(TARS_LOG_SERVER_PATH    ${TARS_TEST_ROOT}/framework/LogServer)
set(TARS_STAT_SERVER_PATH    ${TARS_TEST_ROOT}/framework/StatServer)
include_directories(
${TARS_UTIL_INC}
${TARS_SERVANT_INC}
${TARS_PROTOCOL_INC}
)

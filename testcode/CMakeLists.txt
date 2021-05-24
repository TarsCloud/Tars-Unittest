
# include_directories(${util_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/src/gtest/include)
link_directories(${CMAKE_BINARY_DIR}/src/gtest/lib)
link_directories(${CMAKE_BINARY_DIR}/src/gtest/lib64)

include_directories(include)
include_directories(../protocol)

include_directories(../../servant/protocol/servant)
include_directories(../../servant/protocol/framework)
build_unitest("testcase")

target_link_libraries(testcase TestcaseServer ${LIB_GTEST} z)
add_dependencies(testcase TestcaseServer)
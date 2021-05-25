#!/bin/bash

killall -9 logServer
killall -9 statServer
killall -9 unitTestServer

bin/logServer --config=../unittest/conf/TarsTest.LogServer.config.conf&

bin/statServer --config=../unittest/conf/TarsTest.StatServer.config.conf&

bin/unitTestServer --config=../unittest/conf/TarsTest.UnitTest.config.conf&

# cd ../testcase

if [ "$debug_mode"x == "gdb"x ] ;then
    gdb --args bin/testcase --config=../unittest/conf/TarsTest.TestcaseServer.config.conf
else
    bin/testcase --config=../unittest/conf/TarsTest.TestcaseServer.config.conf
fi

killall -9 logServer
killall -9 statServer
killall -9 unitTestServer

# kill  $(pidof logServer)
# kill  $(pidof statServer)

# cd ${TARS_TEST_ROOT}
# if [ ! -d "./result" ];then
# mkdir ./result
# fi
# mv ./taf_result.xml ./result

# if [ "$run_lcov"x == "YES"x ]  ;then
# cd ${TARS_TEST_ROOT}/script
# sh ./lcov.sh ${TARS_ROOT}
# fi
 

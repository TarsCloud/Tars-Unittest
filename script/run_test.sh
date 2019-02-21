#!/bin/bash

debug_mode=
clean_build=
build_only=
run_lcov=
basepath=$(cd `dirname $0`; pwd)

echo $basepath

echo $*
while getopts ":bcdla" opt
do
    case $opt in
        b ) build_only="YES";;
        c ) clean_build="YES";;
        d ) debug_mode="gdb";;
        l ) run_lcov="YES";;
        a ) clean_all="YES";;
        ? ) echo "error"
             echo "-b build_only"
             echo "-c clean_build"
             echo "-d debug gdb"
             echo "-l  run_lcov"
             echo "-a clean_all"
            exit 1;;
    esac
done

cd ../..
TARS_ROOT=$(cd `dirname $0`; pwd)
echo ${TARS_ROOT}

TARS_TEST_ROOT=${TARS_ROOT}/unittest

cd ${TARS_TEST_ROOT}/project

if [ ! -d "./build" ];then
mkdir ./build
fi

cd ./build

if [ "$clean_build"x == "YES"x ]  ;then
rm -rf !tarscpp
cd ${TARS_ROOT}
find . -name "*.gcda" | xargs rm  -rf
cd -
fi

if [ "$clean_all"x == "YES"x ]  ;then
rm -rf *
cd ${TARS_ROOT}
find . -name "*.gcda" | xargs rm  -rf
cd -
fi

if  [ ! -d "./tarscpp" ];then
mkdir ./tarscpp
cd ./tarscpp
cmake -D ENABLE_TARS_GCOV=ON ../../../cpp/
make
rm -rf tools/
cd ..
fi

#########build  unitTestServer######
if [ ! -d "./unitTestServer" ];then
mkdir ./unitTestServer
fi

cd unitTestServer
cmake ../../unitTestServer
#make -j
make
if [  $? -ne 0 ];then
    echo "Make unitTestServer failed! Please check you code first."
    exit -1
else
    echo "Make unitTestServer successful! "
fi

ls
rm -f *.tarsdat
chmod +x unitTestServer

##########build testcase############
cd ..

if [ ! -d "./testcase" ];then
mkdir ./testcase
fi

cd testcase

cmake ../../testcase
#make -j
make

if [  $? -ne 0 ];then
    echo "Make testcase failed! Please check you code first."
    exit -1
else
    echo "Make testcase successful! "
fi

ls
rm -f *.tarsdat
chmod +x testcase

if [ "$build_only"x == "YES"x ] ;then
exit 0 
fi

##########build logserver############
cd ..

if [ ! -d "./logServer" ];then
mkdir ./logServer
fi

cd logServer

cmake ../../logServer
#make -j
make

if [  $? -ne 0 ];then
    echo "Make logServer failed! Please check you code first."
    exit -1
else
    echo "Make logServer successful! "
fi

ls
rm -f *.tarsdat
chmod +x logServer

if [ "$build_only"x == "YES"x ] ;then
exit 0 
fi
##########build statserver############
cd ..

if [ ! -d "./statServer" ];then
mkdir ./statServer
fi

cd statServer

cmake ../../statServer
#make -j
make

if [  $? -ne 0 ];then
    echo "Make statServer failed! Please check you code first."
    exit -1
else
    echo "Make statServer successful! "
fi

ls
rm -f *.tarsdat
chmod +x statServer

if [ "$build_only"x == "YES"x ] ;then
exit 0 
fi
############run test##############
cd ../logServer
./logServer --config=./../../../conf/TarsTest.LogServer.config.conf&

cd ../statServer
./statServer --config=./../../../conf/TarsTest.StatServer.config.conf&

cd ../unitTestServer
./unitTestServer --config=./../../../conf/TarsTest.UnitTest.config.conf&

cd ../testcase

if [ "$debug_mode"x == "gdb"x ] ;then
gdb --args testcase --config=./../../../conf/TarsTest.TestcaseServer.config.conf
else
./testcase --config=./../../../conf/TarsTest.TestcaseServer.config.conf
fi
kill  $(pidof logServer)
kill  $(pidof statServer)

cd ${TARS_TEST_ROOT}
if [ ! -d "./result" ];then
mkdir ./result
fi
mv ./taf_result.xml ./result

if [ "$run_lcov"x == "YES"x ]  ;then
cd ${TARS_TEST_ROOT}/script
sh ./lcov.sh ${TARS_ROOT}
fi
 

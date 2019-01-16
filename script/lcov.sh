#!/bin/bash

ENABLE_BRANCH="--rc lcov_branch_coverage=1"

cd ../..
TARS_ROOT=$(cd `dirname $0`; pwd)
echo ${TARS_ROOT}

TARS_TEST_ROOT=${TARS_ROOT}/unittest

cd ${TARS_TEST_ROOT}

if [ -d "./result" ];then
mv ./result/taf_result.xml ./
rm -rf ./result/*
fi

#compute the coverage of servant only
lcov -d ${TARS_ROOT}/ -c -o out.info 
lcov --remove out.info '/usr/include/*'  -o out.info
lcov --remove out.info '/usr/local/include/*' -o out.info
lcov --remove out.info "${TARS_TEST_ROOT}/*"  -o out.info
lcov --remove out.info "${TARS_ROOT}/servant/servant/*F.h"  -o out.info
lcov --remove out.info "${TARS_ROOT}/servant/servant/Auth.h"  -o out.info
lcov --remove out.info "${TARS_ROOT}/tools/*" -o out.info
lcov --remove out.info "${TARS_ROOT}/util/*" -o out.info
lcov --remove out.info "${TARS_ROOT}/examples" -o out.info
lcov --remove out.info "${TARS_ROOT}/test_deprecated" -o out.info
genhtml -o result out.info

rm out.info
mv ./taf_result.xml ./result
cd ./result
pwd
ls 


/**
 * Tencent is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 */

/*
 * GlobalUTTest.cpp
 *
 *  Created on: 2018年10月29日
 *      Author: abelguo
 */

#include "gtest/gtest.h"
#include "TarsTest.h"
#include "servant/BaseF.h"
#include "servant/Global.h"

USING_NS_STD
USING_NS_TARS

TEST(GlobalUTTest, UT_should_not_throw_exception_when_throwException_input_TARSSERVERSUCCESS)
{
    EXPECT_NO_THROW(TarsException::throwException(TARSSERVERSUCCESS, ""));
}

TEST(GlobalUTTest, UT_should_throw_TarsServerDecodeException_when_throwException_input_TARSSERVERDECODEERR)
{
    EXPECT_THROW(TarsException::throwException(TARSSERVERDECODEERR, ""), TarsServerDecodeException);
}

TEST(GlobalUTTest, UT_should_throw_TarsServerEncodeException_when_throwException_input_TARSSERVERENCODEERR)
{
    EXPECT_THROW(TarsException::throwException(TARSSERVERENCODEERR, ""), TarsServerEncodeException);
}

TEST(GlobalUTTest, UT_should_throw_TarsServerNoFuncException_when_throwException_input_TARSSERVERNOFUNCERR)
{
    EXPECT_THROW(TarsException::throwException(TARSSERVERNOFUNCERR, ""), TarsServerNoFuncException);
}

TEST(GlobalUTTest, UT_should_throw_TarsServerNoServantException_when_throwException_input_TARSSERVERNOSERVANTERR)
{
    EXPECT_THROW(TarsException::throwException(TARSSERVERNOSERVANTERR, ""), TarsServerNoServantException);
}

TEST(GlobalUTTest, UT_should_throw_TarsServerQueueTimeoutException_when_throwException_input_TARSSERVERQUEUETIMEOUT)
{
    EXPECT_THROW(TarsException::throwException(TARSSERVERQUEUETIMEOUT, ""), TarsServerQueueTimeoutException);
}

TEST(GlobalUTTest, UT_should_throw_TarsServerQueueTimeoutException_when_throwException_input_TARSPROXYCONNECTERR)
{
    EXPECT_THROW(TarsException::throwException(TARSPROXYCONNECTERR, ""), TarsServerQueueTimeoutException);
}

TEST(GlobalUTTest, UT_should_throw_TarsServerUnknownException_when_throwException_input_unknow_ret)
{
    int unknowRet = 30;
    EXPECT_THROW(TarsException::throwException(unknowRet, ""), TarsServerUnknownException);
}

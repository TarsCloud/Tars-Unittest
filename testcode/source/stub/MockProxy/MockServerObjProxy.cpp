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
 * MockServerObjProxy.cpp
 *
 *  Created on: 2018年8月22日
 *      Author: abelguo
 */
#include "servant/BaseF.h"
#include "stub/MockServerObjProxy.h"

using namespace tars;
using namespace std;

namespace mockProxy
{

    MockServerObjProxy* MockServerObjProxy::tars_hash(int64_t key)
    {
        return (MockServerObjProxy*)ServantProxy::tars_hash(key);
    }

    MockServerObjProxy* MockServerObjProxy::tars_consistent_hash(int64_t key)
    {
        return (MockServerObjProxy*)ServantProxy::tars_consistent_hash(key);
    }

    MockServerObjProxy* MockServerObjProxy::tars_set_timeout(int msecond)
    {
        return (MockServerObjProxy*)ServantProxy::tars_set_timeout(msecond);
    }
}




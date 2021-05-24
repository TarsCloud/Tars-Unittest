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

#include "TupProxyImp.h"
#include "servant/Application.h"
#include "util/tc_http.h"
#include "util/tc_base64.h"
#include "util/tc_parsepara.h"
#include "util/tc_config.h"
#include "util/tc_hash_fun.h"
// #include "util/tc_atomic.h"
//#include "jce/Tup.h"

using namespace std;

//////////////////////////////////////////////////////

TupCallback::~TupCallback()
{
		//LOG->debug()<<"TupCallback::~TupCallback"<<endl;
        doResponse();
		map<int32_t, RequestPacket*>::iterator it = _tupRequest.begin();
		while(it != _tupRequest.end())
		{
			if(it->second != NULL)
			{
				delete it->second;
			}
			++it;
		}
}

void TupCallback::addtup(int32_t iRequestId, RequestPacket *Tup)
{
        _tupRequest[iRequestId] = Tup;
}

void TupCallback::deltup(int32_t iRequestId)
{
	map<int32_t, RequestPacket*>::iterator it = _tupRequest.find(iRequestId);
	if(it != _tupRequest.end())
	{
		delete it->second;
		it->second = NULL;
	}
    _tupRequest.erase(iRequestId);
}

//int TupCallback::onDispatch(ReqMessagePtr msg)
//{
//	try
//    {
//        if (msg->response.iRet == JCESERVERSUCCESS)
//        {
//            _servant->doResponse(msg);
//        }
//        else if (msg->pObjectProxy == NULL)
//        {
//            _servant->doResponseNoRequest(msg);
//        }
//        else
//        {
//            _servant->doResponseException(msg);
//        }
//    }
//    catch (exception& e)
//    {
//        TLOGERROR("[TAF][TupCallback::onDispatch ex:" << e.what() << "]" << endl);
//    }
//    catch (...)
//    {
//        TLOGERROR("[TAF][TupCallback::onDispatch ex.]" << endl);
//    }
//	return 0;
//}

void TupCallback::doResponse()
{
    if (_allBuffer.size() == 0) return;

	//TLOGDEBUG("-------->TupCallback::doResponse."<<endl);
    size_t contentLen = 0;
    if (_isHttpProt)
    {
        //回复http协议
        TC_HttpResponse httpResponse;
        if(_nowServantName == "voice") 
        {
            httpResponse.setConnection("keep-alive");
			//TLOGDEBUG("-------->keep-alive."<<endl);
        }
       /* else
        {
            httpResponse.setConnection("close");
        }*/
        httpResponse.setHeader("Date", TC_Common::now2GMTstr());
        httpResponse.setHeader("Server", "QBServer");
        httpResponse.setHeader("Cache-Control", "no-cache");
        httpResponse.setHeader("Content-Type", "application/multipart-formdata");
        httpResponse.setHeader("Cache-Control", "no-cache");   //不缓存内容



        //httpResponse.setResponse(200, "OK", &_allBuffer[0], _allBuffer.size());
		httpResponse.setResponse(200, "OK", _allBuffer);


        /*string s;
        s.assign((const char*)&_allBuffer[0], _allBuffer.size());*/

        vector<char> response;
        httpResponse.encode(response);
		//string s;
		//httpResponse.encode(s);

		//getCurrent()->sendResponse(s.c_str(), s.size());
    
        getCurrent()->sendResponse((const char*)(&response[0]), response.size());

    }
    else
    {
        contentLen = _allBuffer.size();

        //getCurrent()->sendResponse((const char*)(&_allBuffer[0]), _allBuffer.size());
		getCurrent()->sendResponse(_allBuffer.c_str(), _allBuffer.size());
    }

    //超级包打一个错误日志
    if (contentLen > 1000000 ) 
	{
		LOG->error() << "all|" << _tupRequest.size() << endl;
	}

    _allBuffer.clear();
    _nowServantName="";
	_iResponse = 0;
}

void TupCallback::doResponse_tup(const vector<char> &buffer)
{
	//TLOGDEBUG("-------->TupCallback::doResponse_Tup."<<endl);
        try
        {
                
                tars::TarsInputStream<BufferReader> is;
        
                //去掉四个字节的长度
                if(buffer.size()>4) 
                {
                    is.setBuffer(&buffer[0]+4, buffer.size()-4);
                }
                else
                {
                    LOG->error() << "[TupCallback::doResponse_Tup] buffer.size = "<<buffer.size()<<endl;
                    return;
                }
        
                RequestPacket Tup;
                
                Tup.readFrom(is);

                map<int32_t, RequestPacket*>::iterator it = _tupRequest.find(Tup.iRequestId);
        
                if (it == _tupRequest.end())
                {
                        LOG->error() << "[TupCallback::doResponse_Tup] find Tup origin request error:" 
                        << Tup.sServantName << "::" 
                        << Tup.sFuncName << " requestid:" 
                        << Tup.iRequestId << ", no match origin request." << endl; 
        
                        return;
                }
        
                ////回复包设置为请求包的信息
                Tup.iRequestId      = it->second->iRequestId;
                Tup.sServantName    = it->second->sServantName;
                Tup.sFuncName       = it->second->sFuncName;
        
                //设置一下当前回包的http包是否包含voice包
                if(Tup.sServantName=="voice") 
                {
                    _nowServantName = "voice";
                }
        
                ++_iResponse;
        
                tars::TarsOutputStream<BufferWriter> os;
                Tup.writeTo(os);
                
                //doRSP的时候也要加上头部4个字节
                unsigned int bufferlength = os.getLength()+4;
                bufferlength = htonl(bufferlength);
                
                string s;
				s.reserve(os.getLength() + 4);
                s.append((char*)&bufferlength, 4);
                s.append(os.getBuffer(),os.getLength());
                

                if ( os.getLength() > 100000 ) 
				{
					LOG->error()  << "Tup|" << os.getLength() << "|" << Tup.sServantName  << "|" << Tup.sFuncName << endl;
				}

                //_allBuffer.insert(_allBuffer.end(), s.c_str(), s.c_str() + s.length());
				//usleep(10000);
				_allBuffer += s;

                //都回来了, 可以回包了
                if (_iResponse == _tupRequest.size())
				{
					//TLOGDEBUG("-------->doResponse Tup."<<endl);
					doResponse();
				}
        }
        catch (exception &ex)
        {
                LOG->error() << "[TupCallback::doResponse_Tup] error:" << ex.what() << endl;
        }
        catch (...)
        {
                LOG->error() << "[TupCallback::doResponse_Tup] unknown error." << endl;
        }
}


void TupCallback::doResponse_jce(const vector<char> &buffer)
{
	//TLOGDEBUG("-------->TupCallback::doResponse_jce."<<endl);

        try
        {
                tars::TarsInputStream<BufferReader> is;
        
                        //去掉4个字节长度
                if(buffer.size()>4) 
                {
                    is.setBuffer(&buffer[0]+4, buffer.size()-4);
                }
                else
                {
                    LOG->error() <<"[TupCallback::doResponse_jce] buffer.size = "<<buffer.size()<<endl;
                    return;
                }


                ResponsePacket Tup;             
                Tup.readFrom(is);

                map<int32_t, RequestPacket*>::iterator it = _tupRequest.find(Tup.iRequestId);
                if (it == _tupRequest.end())
                {
                        LOG->error() << "[TupCallback::doResponse_jce] find Tup origin request error: requestid:" 
                         << Tup.iRequestId << ", no match origin request." << endl; 

                        return;
                }

                //回复包设置为请求包的信息
                Tup.iRequestId      = it->second->iRequestId;

				/*delete it->second;

				_tupRequest.erase(it);*/

                ++_iResponse;

                tars::TarsOutputStream<BufferWriter> os;
                Tup.writeTo(os);
                
                //doRSP的时候也要加上头部4个字节
                unsigned int bufferlength = os.getLength()+4;
                bufferlength = htonl(bufferlength);
                
                string s;
				s.reserve(os.getLength() + 4);
                s.append((char*)&bufferlength, 4);
                s.append(os.getBuffer(),os.getLength());
        

                if ( os.getLength() > 100000 ) 
				{
					LOG->error() << "jce|" << "|" << os.getLength() << "|" << endl;
				}

                //_allBuffer.insert(_allBuffer.end(), s.c_str(), s.c_str() + s.length());
				_allBuffer += s;

                //都回来了, 可以回包了
                if (_iResponse == _tupRequest.size())
                {
					//TLOGDEBUG("-------->doResponse jce."<<endl);
					doResponse();
				}
        }
        catch (exception &ex)
        {
                LOG->error() << "[TupCallback::doResponse_jce] error:" << ex.what() << endl;
        }
        catch (...)
        {
                LOG->error() << "[TupCallback::doResponse_jce] unknown error." << endl;
        }
}


//////////////////////////////////////////////////////



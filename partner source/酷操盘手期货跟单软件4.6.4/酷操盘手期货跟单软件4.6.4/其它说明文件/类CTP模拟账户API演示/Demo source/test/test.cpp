//酷操盘手跟单软件模拟账户TD  API
//量化林  2017.7.25   QQ群：5172183

#include "stdafx.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "TraderSpi.h"
//#include "ThostTraderApi.h"

CThostFtdcTraderApi *pUserApi;
CTraderSpi  *pUserSpi;
char  FRONT_ADDR[] = "tcp://127.0.0.1:41206";		    // 前置地址

TThostFtdcBrokerIDType	BROKER_ID = "9999";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "00069";			// 投资者代码
TThostFtdcPasswordType  PASSWORD = "888888";			// 用户密码
TThostFtdcInstrumentIDType INSTRUMENT_ID = "cu1712";	// 合约代码
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// 买卖方向
TThostFtdcPriceType	LIMIT_PRICE = 38850;				// 价格

														// 请求编号
int iRequestID = 0;
int main()
{
	cerr << "--->>> " << "Initialing kucps UserApi" << endl;
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
	pUserSpi = new CTraderSpi;
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	//pUserApi->SubscribePublicTopic(TERT_RESTART);					// 注册公有流
	//pUserApi->SubscribePrivateTopic(TERT_RESTART);					// 注册私有流
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();


	cerr << "--->>> " << "kucps ThostTraderApi Initialization complete." << endl;
	//cerr << "--->>> " << "演示版本，请不要花时间测试." << endl;
	system("pause");

}


// testTraderApi.cpp : 定义控制台应用程序的入口点。
//
#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "TraderSpi.h"
#include "inifile.h"
// UserApi对象
CThostFtdcTraderApi* pUserApi;

// 配置参数
//char  FRONT_ADDR[] = "tcp://121.41.46.14:8886";		// 前置地址
char  FRONT_ADDR[60];// = "tcp://121.41.46.14:8886";		// 前置地址
TThostFtdcBrokerIDType	BROKER_ID;// = "1023";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID;// = "5501156";			// 投资者代码
TThostFtdcPasswordType  PASSWORD;// = "369258";			// 用户密码
TThostFtdcInstrumentIDType INSTRUMENT_ID;// = "cu1910";	// 合约代码
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// 买卖方向
TThostFtdcPriceType	LIMIT_PRICE = 38850;				// 价格

// 请求编号
int iRequestID = 0;
#include <windows.h>
void main(void)
{
	IniFile file;
	if (!file.Init("setting.ini"))
	{
		printf("读取配置文件setting.ini错误");
		return;
	}
	//int Instrumentnum = file.GetIntFromSection("Instrument", "num", 1);

	string brokeidstr = file.GetValueFromSection("setting", "brokeid");
	string investorstr = file.GetValueFromSection("setting", "investor");
	string passwordstr = file.GetValueFromSection("setting", "password");
	string addressstr = file.GetValueFromSection("setting", "address");

	_snprintf_s(BROKER_ID, sizeof(BROKER_ID), sizeof(BROKER_ID)-1,"%s", brokeidstr.c_str());
	_snprintf_s(INVESTOR_ID, sizeof(INVESTOR_ID), sizeof(INVESTOR_ID) - 1, "%s", investorstr.c_str());
	_snprintf_s(PASSWORD, sizeof(PASSWORD), sizeof(PASSWORD) - 1, "%s", passwordstr.c_str());
	_snprintf_s(FRONT_ADDR, sizeof(FRONT_ADDR), sizeof(FRONT_ADDR) - 1, "%s", addressstr.c_str());

	printf("读入知富测试程序的配置文件setting.ini的账户信息:\nBROKERID:%s\nINVESTOR:%s\nPASSWORD:%s\nADDRESS:%s\n",BROKER_ID, INVESTOR_ID, PASSWORD, FRONT_ADDR);

	// 初始化UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	//pUserApi->SubscribePublicTopic(TERT_RESTART);					// 注册公有流
	//pUserApi->SubscribePrivateTopic(TERT_RESTART);					// 注册私有流
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();

	while (1)
	{
		pUserSpi->ReqQryInvestorPosition();	

		Sleep(3000);
		pUserSpi->ReqQryTradingAccount();

		Sleep(3000);
	}
	//pUserApi->Join();
//	pUserApi->Release();
}
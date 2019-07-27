// AutoTrader.cpp : 单合约版本,输入经纪公司代码，实盘帐号，密码即可下单。
//自动保存订阅合约TICK数据到\Bin\TickData下，文件名合约名称_日期.txt	
 

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "TraderSpi.h"
#include "MdSpi.h"
#include "Common.h"
#include "DataSniffer.h"
#include "MyTrader.h"
#include "IniFile.h"
#pragma warning(disable : 4996)
// UserApi对象
CThostFtdcTraderApi *pUserApi;
// MdApi对象
CThostFtdcMdApi *pMdApi;

// 配置参数
char  FRONT_ADDR_TD[] = "tcp://180.168.146.187:10101";		// 前置地址1交易:实盘
 
char  FRONT_ADDR_MD[] = "tcp://180.168.146.187:10111";		// 前置地址1交易:盘后
 



TThostFtdcBrokerIDType	BROKER_ID = "9999";								// 实盘：经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "000000";						// 实盘：投资者代码
TThostFtdcPasswordType  PASSWORD = "000000";							// 实盘：用户密码
TThostFtdcAuthCodeType	AuthCode = "000000";                    //期货公司提供的认证码,SINNOW为 0000000000000000
TThostFtdcAppIDType	AppID = "000000";                        //appid
 

TThostFtdcInstrumentIDType INSTRUMENT_ID = "rb1911";					// 交易合约代码,必须和CSV数据文件中合约字段代码一致
TThostFtdcDirectionType	DIRECTION;										// 交易买卖方向
TThostFtdcOffsetFlagType MARKETState;									// 开平仓
TThostFtdcPriceType	LIMIT_PRICE;										// 交易价格

//char *ppInstrumentID[] = {"IF1910", "rb1910","ag1910", "ru1910", "cu1910", "j1910", "SR1910", "m1910", "y1910", "p1910"};			// 行情订阅列表
//int iInstrumentID = 10;													// 行情订阅数量

char *ppInstrumentID[] = { "rb1911"};			// 行情订阅列表，交易合约代码,必须和CSV数据文件中合约字段代码一致，目前只支持1个合约同时回测，不支持订阅多个合约回测
int iInstrumentID = 1;							// 行情订阅数量
bool	ReceiveTick = false;

// 请求编号
int iRequestID = 0;
// 交易时间
bool	JustRun = false;	//正在启动标志

TThostFtdcDateExprType	TradingDay;

// User行情数据

extern	char	*InstrumentID_name;	//
extern	string	Q_BarTime_s;		//时间字符串
extern	int		Q_BarTime_1;		//时间采用秒计
extern	double	Q_BarTime_2;		//时间格式0.145100
extern	double	Q_UpperLimit;	//
extern	double	Q_LowerLimit;	//

extern	double	NewPrice;		//
extern	int		FirstVolume;	//前一次成交量数据

extern	double  Mn_open[3];		// 
extern	double  Mn_high[3];		// 
extern	double  Mn_low[3];		// 
extern	double  Mn_close[3];	// 

extern	double  BuyPrice;		//开仓价
extern	double  SellPrice;		//开仓价
extern	int		BNum;			//开仓次数
extern	int		SNum;			//开仓次数

extern	bool	BuySignal;		//
extern	bool	SellSignal;		//

extern	double	BSVolume;		//开仓量

extern	int		TickABS;
extern	double  TickAPrice[4];		//
extern	int		TickBNum;
extern	double  TickBPrice[4];		//

extern	char    LogFilePaths[80];	//

// 会话参数
extern	TThostFtdcFrontIDType	FRONT_ID;	//前置编号
extern	TThostFtdcSessionIDType	SESSION_ID;	//会话编号
extern	TThostFtdcOrderRefType	ORDER_REF;	//报单引用



void main(void)
{



	CIniFile	cfgfile(_T("./settini.ini"));
	//char brokeidchar[31] = { 0 };
	//char investorchar[31] = { 0 };
	//char passwordchar[31] = { 0 };
	//char appidchar[31] = { 0 };

	//char tdserverchar[31] = { 0 };



	GetPrivateProfileStringA("setting", "Brokeid", "9999", BROKER_ID, sizeof(BROKER_ID), ("./setting.ini"));

	GetPrivateProfileStringA("setting", "Investor", "", INVESTOR_ID, sizeof(INVESTOR_ID), ("./setting.ini"));

	GetPrivateProfileStringA("setting", "Password", "", PASSWORD, sizeof(PASSWORD), ("./setting.ini"));

	GetPrivateProfileStringA("setting", "TDServer", "", FRONT_ADDR_TD, sizeof(FRONT_ADDR_TD), ("./setting.ini"));
	GetPrivateProfileStringA("setting", "MDServer", "", FRONT_ADDR_MD, sizeof(FRONT_ADDR_MD), ("./setting.ini"));

	GetPrivateProfileStringA("setting", "AuthCode", "0000000000000000", AuthCode, sizeof(AuthCode), ("./setting.ini"));
	GetPrivateProfileStringA("setting", "AppID", "20", AppID, sizeof(AppID), ("./setting.ini"));

	GetPrivateProfileStringA("setting", "InstrumentID", "rb1910", INSTRUMENT_ID, sizeof(INSTRUMENT_ID), ("./setting.ini"));


	printf("Brokeid:%s Investor:%s AuthCode:%s  AppID:%s\n", BROKER_ID, INVESTOR_ID, AuthCode, AppID);


	
	Sleep(5000);



	//非穿透式（老API）
	void Erasefiles();
	void Sniffer();
	void Trading();
	bool ReadConfiguration(char *filepaths);
	void WriteConfiguration(char *filepaths);
	
	Erasefiles();
	Sleep(2000);

	cerr << "--->>> " << "Welcom MyAutoTrader System!" << endl;
	cerr << "--->>> " << "Version 1.0.0!" << endl;

	// 初始化MdApi
	pMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CThostFtdcMdSpi* pMdSpi = new CMdSpi();
	pMdApi->RegisterSpi(pMdSpi);									// 注册事件类
	pMdApi->RegisterFront(FRONT_ADDR_MD);							// connect		优先行情地址
 	//cout << pMdApi->GetApiVersion() << endl;
	pMdApi->Init();
	cout << "--->>> " << "Initialing MdApi" << endl;


	// 初始化UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);				// 注册公有流
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);			// 注册私有流
	pUserApi->RegisterFront(FRONT_ADDR_TD);							// connect
	pUserApi->Init();
	//cout << pUserApi->GetApiVersion() << endl;
	cout << "--->>> " << "Initialing TradeApi" << endl;




	
	Sleep(6000);
	ReadConfiguration("./AutoTrader.dat");			//自定义数据，如持仓数据等均可
	cout << "--->>> " << "初始化完成!" << endl;
	

	while(1)
	{
			
		//指标计算,下面只是个简单例子
		//可自建函数，进行复杂处理  见DataSniffer.h


		Sleep(5000);


	}

}




#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
using namespace std;

#include "TraderSpi.h"
#include "MdSpi.h"
#pragma warning(disable : 4996)

// USER_API参数
extern CThostFtdcMdApi* pMdApi;

// 配置参数
extern char FRONT_ADDR[];		
extern TThostFtdcBrokerIDType	BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType	PASSWORD;
extern char* ppInstrumentID[];	
extern int iInstrumentID;
extern TThostFtdcInstrumentIDType INSTRUMENT_ID;

// 请求编号
extern int iRequestID;

// User行情数据
extern	TThostFtdcDateExprType	TradingDay;

extern	bool	ReceiveTick;

bool	CloseAll= false;										//收盘标志

char	*InstrumentID_name;	//
double	Q_Dayopen=0;		//
double	Q_UpperLimit = 0;	//
double	Q_LowerLimit = 0;	//
string	Q_BarTime_s;		//
int		Q_BarTime_1;		//
double	Q_BarTime_2;		//
int		FirstVolume;		//前一次成交量数据
int		BNum = 0;			//开仓次数
int		SNum = 0;			//开仓次数

bool	MnKlinesig=false;		//
double  Mn_open[3]	= {0,0,0};			// 
double  Mn_high[3]	= {0,0,0};			// 
double  Mn_low[3]	= {0,0,0};			// 
double  Mn_close[3] = {0,0,0};			// 
double  NewPrice = 0;		//

double  Mn_bbreak = 0;		// 
double  Mn_sbreak = 0;		// 
double  Mn_UpperBand = 100000;	// 
double  Mn_LowerBand = 0;	// 

double  M4 = 1.0;			// 
double  M5 = 1.0;			// 

double  BuyPrice = 0;		//开仓价
double  SellPrice = 0;		//开仓价

double  BuyPrice1 = 0;		//买一价
double  SellPrice1 = 0;		//卖一价
double  BuyVol1 = 0;		//买一量
double  SellVol1 = 0;		//卖一量
double  BuyVol10 = 0;		//上一次买一量
double  SellVol10 = 0;		//上一次卖一量

double	TodayVolume = 0;	//成交量
double	OpenInt = 0;		//持仓量

double  BuyStopline = 0;	//开仓止损价
double  SellStopline = 0;	//开仓止损价 
double	BSVolume = 1;		//开仓量

bool	BuySignal = false;	//
bool	SellSignal = false;	//

int		TickABS = 0;
double  TickAPrice[4];		//
int		TickBNum = 0;
double  TickBPrice[4];		//
char    TickFileWritepaths[80]="";	//
char    LogFilePaths[80]="";	//

void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast)
{
	cerr << "--->>> "<< __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

void CMdSpi::OnFrontDisconnected(int nReason)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> Reason = " << nReason << endl;
}
		
void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void CMdSpi::OnFrontConnected()
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	//cerr << "--->>> " << "CMdSpi::OnFrontConnected" << endl;
	///用户登录请求
	ReqUserLogin();

}


void CMdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);
	int iResult = pMdApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> 发送行情用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;

	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		cerr << "--->>> 获取当前交易日 = " << pMdApi->GetTradingDay() << endl;
		// 请求订阅行情
		SubscribeMarketData();	
	}
}

void CMdSpi::SubscribeMarketData()
{
	int iResult0 = pMdApi->UnSubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> 取消行情订阅请求: " << ((iResult0 == 0) ? "成功" : "失败") << endl;
	Sleep(1000);
	int iResult = pMdApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;

	//文件命名，“OrderInfo_date.txt”
	char perf[100];
	char tmp[20];
	int tmp1 = 20140424;
	strcpy(perf,"./AutoTrade/");
	strcpy(perf,"TraderInfo_");
	sprintf(tmp,"%d",tmp1);
	strcat(perf,tmp);
	strcat(perf,".txt");
	cerr << "--->>> " << perf << endl;
	
	//检查文件是否存在，是否需要新建文本文件
	ifstream inf;
	ofstream ouf;
	inf.open(perf,ios::out);

}

void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> 成功订阅合约:" <<"_"<<pSpecificInstrument->InstrumentID<< endl;

}

void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
}

extern void Sniffer();//监听Tick数据已经指标计算 实盘用

extern void Trading();	//下单以及订单管理

bool openstate = false;
bool closestate = false;
extern void SendOrder(TThostFtdcInstrumentIDType FuturesId, int BuySell, int OpenClose);
extern 	bool tdloginstate;
int dealytick = 0;
 void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{

	 printf("%s %f\n",pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);
	if (tdloginstate)
	{
	
		if (!openstate)
		{
			openstate = true;
			NewPrice = pDepthMarketData->UpperLimitPrice;

			SendOrder(INSTRUMENT_ID, 0, 0);
			NewPrice = pDepthMarketData->LowerLimitPrice;

			SendOrder(INSTRUMENT_ID, 0, 0);

		}

		if (openstate)
		{
			dealytick++;
		}


		if (!closestate && dealytick>=8)
		{
			closestate = true;
			NewPrice = pDepthMarketData->LowerLimitPrice;

			SendOrder(INSTRUMENT_ID, 1, 3);

		}
	}
	
}


bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}



#pragma once
//
#include <string>
#include <iomanip>
#include <vector>

#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "TraderSpi.h"
#include "MdSpi.h"

#pragma warning(disable : 4996)

// USER_API参数
extern CThostFtdcTraderApi* pUserApi;
// 配置参数	
extern TThostFtdcBrokerIDType	BROKER_ID;						//经纪商
extern TThostFtdcInvestorIDType INVESTOR_ID;					//
extern TThostFtdcPasswordType	PASSWORD;						//

extern	TThostFtdcInstrumentIDType	INSTRUMENT_ID;				// 交易合约代码
extern	TThostFtdcDirectionType		DIRECTION ;					// 交易买卖方向
extern	TThostFtdcOffsetFlagType	MARKETState ;				// 开平仓
extern	TThostFtdcPriceType			LIMIT_PRICE ;				// 交易价格

// 会话参数
//extern	bool		RunMode;
extern	TThostFtdcFrontIDType	FRONT_ID;						//前置编号
extern	TThostFtdcSessionIDType	SESSION_ID;						//会话编号
extern	TThostFtdcOrderRefType	ORDER_REF;						//报单引用
extern	TThostFtdcOrderActionRefType	ORDERACTION_REF[20];	//撤单引用

// 请求编号
extern	int iRequestID;
extern	TThostFtdcDateExprType	TradingDay;
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
extern  double  TickAPrice[4];		//
extern	int		TickBNum;
extern	double  TickBPrice[4];		//

extern	char    LogFilePaths[80];	//



void SendOrder(TThostFtdcInstrumentIDType FuturesId,int BuySell,int OpenClose)
{
	//INSTRUMENT_ID = FuturesId;
	DIRECTION = BuySell;
	MARKETState = OpenClose;

	if (BuySell==0 && OpenClose==0)
	{
			BuySignal = true;
			SellSignal= false;
	}
	if (BuySell==1 && OpenClose==0)
	{
			BuySignal = false;
			SellSignal = true;
	}
	if (BuySell==0 && OpenClose==3)
	{
			BuySignal = false;
			SellSignal = false;	
	}
	if (BuySell==1 && OpenClose==3)
	{
			BuySignal = false;
			SellSignal = false;
	}
	
	//Sleep(050);

	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));

 	strcpy_s(req.ExchangeID, "SHFE");


	///经纪公司代码
	strcpy_s(req.BrokerID, BROKER_ID);
	///投资者代码
	strcpy_s(req.InvestorID, INVESTOR_ID);
	///合约代码											//INSTRUMENT_ID
	strcpy_s(req.InstrumentID, INSTRUMENT_ID);
	///报单引用
	//strcpy_s(req.OrderRef, ORDER_REF);
	///用户代码
//	TThostFtdcUserIDType	UserID;
	///报单价格条件: 限价
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;

	///买卖方向:										//THOST_FTDC_D_Buy,THOST_FTDC_D_Sell
	if (BuySell==0)
	{
	req.Direction = THOST_FTDC_D_Buy;
	}
	else if (BuySell==1)
	{
	req.Direction = THOST_FTDC_D_Sell;
	}

	///组合开平标志: 开仓								//THOST_FTDC_OF_Open,THOST_FTDC_OF_Close,THOST_FTDC_OF_CloseToday
	if (OpenClose==0)
	{
	req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;			//开仓
	}
	else if(OpenClose==1)
	{
	req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;		//平仓
	}
	else if(OpenClose==3)
	{
	req.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;	//平今
	}

	///组合投机套保标志
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;	//投机

	///价格
	if (BuySell==0)
	{
	//LIMIT_PRICE = Q_UpperLimit;	//涨停价	
	LIMIT_PRICE = NewPrice;			//最新价
	}
	else if (BuySell==1)
	{
	//LIMIT_PRICE = Q_LowerLimit;	//跌停价
	LIMIT_PRICE = NewPrice;			//最新价
	}
	req.LimitPrice = LIMIT_PRICE;

	///数量: 1											//     开平仓数量
	req.VolumeTotalOriginal = 1;						
	///有效期类型: 当日有效
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD日期
//	TThostFtdcDateType	GTDDate;
	///成交量类型: 任何数量
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///最小成交量: 1
	req.MinVolume = 1;
	///触发条件: 立即
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///止损价
//	TThostFtdcPriceType	StopPrice;
	///强平原因: 非强平
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///自动挂起标志: 否
	req.IsAutoSuspend = 0;
	///业务单元
//	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
//	TThostFtdcRequestIDType	RequestID;
	///用户强评标志: 否
	req.UserForceClose = 0;

	///报单引用,必须大于上次
	int iNextOrderRef = atoi(ORDER_REF);
	iNextOrderRef++;
	sprintf(ORDER_REF,"%d",iNextOrderRef);
	strcpy_s(req.OrderRef, ORDER_REF);

	//测试，不真正下单
	//if(RunMode)				//	仿真=0；实盘=1；
	//{
	int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestID);		//实盘，会正式下单
	cerr << "--->>> 报单录入请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
	//}
}

void _record0(double system_times, char *txt, double SPrice, double BPrice)
{
	ofstream o_file(LogFilePaths,ios::app);
	o_file << TradingDay << "_" << system_times << "_" << INSTRUMENT_ID << "_" << BSVolume << txt << "_" << SPrice << "_" << BPrice << endl; //将内容写入到文本文件中
	o_file.close();						//关闭文件
}

bool ReadConfiguration(char *filepaths)
{
	ifstream config(filepaths);

	if (!config)
	{
		cerr << "--->>> " << "Configuration File is missing!" << endl;
		return false;
	}
	else
	{
		cerr << "--->>> " << "Read Configuration File!" << endl;
	}

	vector < double > data(8);
	for (int i = 0; i < 8; i++)
	{
		config >> data[i];
		//cout << "Configuration:" << data[i] << endl;
	}
	
	Sleep(100);
	//								//
	//Q_BarTime_2 = data[1];		//Q_BarTime_2
	BSVolume	= data[2];			//BSVolume
	//								//
	Mn_open[0]	= data[4];			//Mn_open
	Mn_high[0]	= data[5];			//Mn_high
	Mn_low[0]	= data[6];			//Mn_low
	Mn_close[0] = data[7];			//Mn_close
	NewPrice	= data[7];

	config.close();
	return true;
}

void WriteConfiguration(char *filepaths)
{
	ofstream o_file(filepaths,ios::trunc);
	o_file << "20140428" << "\t" <<Q_BarTime_2<< "\t" << BSVolume <<"\t"<<"1409" <<"\t"<< Mn_open << "\t" << Mn_high << "\t" << Mn_low << "\t" << Mn_close << endl; //将内容写入到文本文件中
	o_file.close();						//关闭文件

}


void Erasefiles()
{
	system("del .\\thostmduserapi.dllDialogRsp.con");
	system("del .\\thostmduserapi.dllQueryRsp.con");
	system("del .\\thostmduserapi.dllTradingDay.con");

	system("del .\\thosttraderapi.dllDialogRsp.con");
	system("del .\\thosttraderapi.dllPrivate.con");
	system("del .\\thosttraderapi.dllPublic.con");
	system("del .\\thosttraderapi.dllQueryRsp.con");
	system("del .\\thosttraderapi.dllTradingDay.con");

}

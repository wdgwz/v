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


void Trading()	//下单以及订单管理
{
	void SendOrder(TThostFtdcInstrumentIDType FuturesId,int BuySell,int OpenClose);
	void _record0(double system_times, char *txt, double SPrice, double BPrice);
	void StopLoss(double system_times);

		bool TradingTime=(Q_BarTime_2>0.0910 && Q_BarTime_2<0.2355);	//交易时间
		bool fanshou=false;	//反手使能

		//调用止损子程序	************************优先判断是否符号止损止盈条件，在进行开仓处理；
		StopLoss(Q_BarTime_2);

		if (TickABS==1 && TradingTime)
		{

			if (SellSignal == true && fanshou)	//如果有持仓，先平仓
			{
 			SendOrder(INSTRUMENT_ID, 0, 3);		//买平
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_买_平仓" << endl;
			_record0(Q_BarTime_2, "_买_平仓", NewPrice, NewPrice);
			}

 			SendOrder(INSTRUMENT_ID, 0, 0);	

			BuyPrice=NewPrice;
			SellPrice=0;
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_买_开仓" << endl;
			_record0(Q_BarTime_2, "_买_开仓", BuyPrice, BuyPrice);

		}
		if (TickABS==2 && TradingTime)
		{
			if (BuySignal == true && fanshou)	//如果有持仓，先平仓
			{
 			SendOrder(INSTRUMENT_ID, 1, 3);	
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_卖_平仓" << endl;
			_record0(Q_BarTime_2, "_卖_平仓", NewPrice, NewPrice);
			}

 			SendOrder(INSTRUMENT_ID, 1, 0);	

			BuyPrice=0;
			SellPrice=NewPrice;
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_卖_开仓" << endl;
			_record0(Q_BarTime_2, "_卖_开仓", SellPrice, SellPrice);
		}

}





void StopLoss(double system_times)
{
	void SendOrder(TThostFtdcInstrumentIDType FuturesId,int a,int b);
	void _record0(double system_times, char *txt, double SPrice, double BPrice);
	
	bool stopwin =true;	//使能止盈
	bool stoploss=true;	//使能止损
	bool stoptime=true;	//使能收盘平仓

	double surplus	=20;	//止赢幅度
	double Stopline	=30;	//止损幅度

		//止赢平仓
	if (BuySignal == true && (NewPrice-BuyPrice) >= surplus && stopwin)
		{
			SendOrder(INSTRUMENT_ID, 1, 3);
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_卖_平仓止赢_" << BuyPrice << endl;
			_record0(system_times, "_卖_平仓止赢_", BuyPrice, BuyPrice);
		}
	if (SellSignal == true && (SellPrice-NewPrice) >= surplus && stopwin)
		{
			SendOrder(INSTRUMENT_ID, 0, 3);
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_买_平仓止赢_" << SellPrice << endl;
			_record0(system_times, "_买_平仓止赢_", SellPrice, SellPrice);
		}

		//止损平仓
	if (BuySignal == true && (BuyPrice-NewPrice)>Stopline && stoploss)
		{
			SendOrder(INSTRUMENT_ID,1,3);
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_卖_平仓止损_" << BuyPrice << endl;
			_record0(system_times, "_卖_平仓止损_", BuyPrice, BuyPrice);
		}
	if (SellSignal == true && (NewPrice-SellPrice)>Stopline && stoploss)
		{
			SendOrder(INSTRUMENT_ID,0,3);
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_买_平仓止损_" << SellPrice << endl;
			_record0(system_times, "_买_平仓止损_", SellPrice, SellPrice);
		}

		//收盘平仓
	if (BuySignal == true && Q_BarTime_2>0.1455 && stoptime)
		{
			SendOrder(INSTRUMENT_ID,1,3);
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_卖_平仓收盘_" << BuyPrice << endl;
			_record0(system_times, "_卖_平仓收盘_", BuyPrice, BuyPrice);
		}
	if (SellSignal == true && Q_BarTime_2>0.1455 && stoptime)
		{
			SendOrder(INSTRUMENT_ID,0,3);
			cerr << "--->>> " << TradingDay << "_" << Q_BarTime_s << "_" << INSTRUMENT_ID << "_买_平仓收盘_" << SellPrice << endl;
			_record0(system_times, "_买_平仓收盘_", SellPrice, SellPrice);
		}

}
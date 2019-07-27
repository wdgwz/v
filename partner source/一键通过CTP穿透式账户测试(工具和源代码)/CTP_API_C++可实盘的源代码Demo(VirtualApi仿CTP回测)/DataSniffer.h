#pragma once

#include <string>
#include <iomanip>
#include <vector>
#include <math.h>
#include <windows.h>
#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "TraderSpi.h"
#include "MdSpi.h"

#pragma warning(disable : 4996)

#define EPSILON_E4 (float)(1E-2) 
#define EPSILON_E5 (float)(1E-3)


extern	int		TickABS;
extern	double  TickAPrice[4];		//
extern	int		TickBNum;
extern	double  TickBPrice[4];		//
extern	bool	CloseAll;					//收盘标志

 
void Sniffer()	//监听Tick数据已经指标计算 实盘用
{

	if (Q_BarTime_2>=0.1500 && CloseAll==false)
	{	
		cerr << "--->>> " <<TradingDay<<"准备收盘!" << endl;
		cerr << "--->>> " <<"WriteConfiguration!" << endl;
		WriteConfiguration("./AutoTrader.cfg");				//备份数据
		Sleep(3000);
		//ErasingTradeConfiguration();
		cerr << "--->>> " <<TradingDay<<"收盘!" << endl;
		CloseAll=true;
	}
 
	if (TickAPrice[0]>TickAPrice[1] && TickAPrice[1]>TickAPrice[2])
	{
			TickABS=1;	//连续2个TICK涨，buy
 	}
	else if (TickAPrice[0]<TickAPrice[1] && TickAPrice[1]<TickAPrice[2])
	{
			TickABS=2;	//连续2个TICK跌，Sell
 	}
	else
	{
			TickABS=0;
	}	
}


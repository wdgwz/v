#导入A股 API交易库
from TestMD import *
#导入多进程库
import multiprocessing
test = TestMD()   #交易接口类赋值给变量 
num=0    

#回调类型
SYSTEM_SYSTEM_NONE              = 8000 #登录成功
SYSTEM_LOGIN_SCUESS             = 8001 #登录成功
SYSTEM_LOGIN_DENIED             = 8002 #登录被拒绝
SYSTEM_LOGIN_ERRORPASSWORD      = 8003 #密码错误
SYSTEM_LOGINOUT_SCUESS          = 8004 #登出成功
SYSTEM_NETCONNECT_SCUESS        = 8005 #连接成功
SYSTEM_NETCONNECT_BREAK         = 8006 #断开连接
SYSTEM_NETCONNECT_FAILER        = 8007 #连接失败
#SYSTEM_SUBCRIBE_SCUESS          = 8008 #订阅成功
#SYSTEM_UNSUBCRIBE_SCUESS        = 8009 #取消订阅成功 
SYSTEM_NEWTICK                  = 8010 #新Tick到来 
SYSTEM_SYSTEM_ERROR             = 8011 #错误应答 

SYSTEM_MD_TICK                  =8012  #Tick数据
SYSTEM_MD_M1                    =8013  #M1数据
SYSTEM_MD_M3                    =8014  #M3数据
SYSTEM_MD_M5                    =8015  #M5数据
SYSTEM_MD_M10                   =8016  #M10数据
SYSTEM_MD_M15                   =8017  #M15数据
SYSTEM_MD_M30                   =8018  #M30数据
SYSTEM_MD_M60                   =8019  #M60数据
SYSTEM_MD_M120                  =8020  #M120数据

def OnNoneCmd():
    #回调指令缓冲区已为空（因为短时间获得多个指令，时间间隔态度，在下面的for i in range(market.GetUnGetCmdSize()):循环执行了多次已经完成了）
    print "OnNoneCmd"
    
def OnUserLogin():
    #登录成功
    print "OnUserLogin"
    
def OnUserLoginDenied():
    #登录被拒绝
    print "OnUserLoginDenied"  
    
def OnUserLoginErrPassword():
    #登录密码错误
    print "OnUserLoginErrPassword"
    
def OnUserLogout():
    #登出成功
    print "OnUserLogout"
    
def OnFrontConnected():
    #连接成功
    print "OnFrontConnected"
    #连接成功，登录账号
    if True:
        #登录方式1(自动读取配置文件信息登录)
        test.ReqUserLogin()
    else:
        #登录方式2(账户、密码、brokeid通过参数提交登录)
        test.ReqUserLogin()
        
def OnFrontDisconnected():
    #断开连接
    print "OnFrontDisconnected"
    #每隔5s断线从连    
    time.sleep(5)
    test.ReqConnect()
    
def OnFrontConnectedFailer():
    #连接失败
    print "OnFrontConnectedFailer"
    
def OnError():
    print u"OnError(错误应答)"
    
def OnTick():
    global num
    #新的一笔Tick数据驱动
    
    while(test.GetUnGetCmdSize()>0):
        num=num+1
        data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
        print "---------------TEST_OnTick[%d]---------------"%num
        print "InstrumentID %s"%((str(data[0].InstrumentID)))         #合约代码
        print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
        print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
        print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
        print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
        print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
        print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
        print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
        print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
        print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
        print "Volume %s"%(str(data[0].Volume))                               #数量
        print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
        print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
        print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
        print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
        print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
        print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
        print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
        print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
        print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
        print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
        print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
        print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价
 
        
        if num ==100000:
            result=test.UnGetTestData()       
def OnM1():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_OnM1---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价       
        
def OnM3():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_OnM3---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价      
        
def OnM5():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_OnM5---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价        
        
def OnM10():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_OnM10---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价      
        
def OnM15():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_OnM15---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价        
        
def OnM30():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_OnM30---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价       
        
        
def OnM60():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_On60---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价      
        
def OnM120():        
    global num
    #新的一笔Tick数据驱动
    print "---------------TEST_OnM120---------------"  
    num=num+1
    data = cast(test.GetMD_Tick(), POINTER(QL_MarketTickData))
    print "[%d]InstrumentID %s"%(num,(str(data[0].InstrumentID)))         #合约代码
    print "TradingDay %s"%(str(data[0].TradingDay))                       #交易日
    print "ActionDay %s"%(str(data[0].ActionDay))                         #业务日期
    print "LastPrice %s"%(str(data[0].LastPrice))                         #最新价        
    print "PreSettlementPrice %s"%(str(data[0].PreSettlementPrice))       #上次结算价
    print "PreClosePrice %s"%(str(data[0].PreClosePrice))                 #昨收盘     
    print "PreOpenInterest %s"%(str(data[0].PreOpenInterest))             #昨持仓量
    print "OpenPrice %s"%(str(data[0].OpenPrice))                         #今开盘
    print "HighestPrice %s"%(str(data[0].HighestPrice))                   #最高价
    print "LowestPrice %s"%(str(data[0].LowestPrice))                     #最低价
    print "Volume %s"%(str(data[0].Volume))                               #数量
    print "Turnover %s"%(str(data[0].Turnover))                           #成交金额       
    print "OpenInterest %s"%(str(data[0].OpenInterest))                   #持仓量
    print "ClosePrice %s"%(str(data[0].ClosePrice))                       #今收盘
    print "UpperLimitPrice %s"%(str(data[0].UpperLimitPrice))             #涨停板价       
    print "LowerLimitPrice %s"%(str(data[0].LowerLimitPrice))             #跌停板价
    print "UpdateTime %s"%(str(data[0].UpdateTime))                       #最后修改时间
    print "UpdateMillisec %s"%(str(data[0].UpdateMillisec))               #最后修改毫秒       
    print "BidPrice1 %s"%(str(data[0].BidPrice1))                         #申买价一
    print "BidVolume1 %s"%(str(data[0].BidVolume1))                       #申买量一
    print "AskPrice1 %s"%(str(data[0].AskPrice1))                         #申卖价一
    print "AskVolume1 %s"%(str(data[0].AskVolume1))                       #申卖量一       
    print "AveragePrice %s"%(str(data[0].AveragePrice))                   #当日均价           
        
cmddict={
    SYSTEM_SYSTEM_NONE:OnNoneCmd,
    SYSTEM_LOGIN_SCUESS:OnUserLogin,
    SYSTEM_LOGIN_DENIED:OnUserLoginDenied,
    SYSTEM_LOGIN_ERRORPASSWORD:OnUserLoginErrPassword,
    SYSTEM_LOGINOUT_SCUESS:OnUserLogout,
    SYSTEM_NETCONNECT_SCUESS:OnFrontConnected,
    SYSTEM_NETCONNECT_BREAK:OnFrontDisconnected,
    SYSTEM_NETCONNECT_FAILER:OnFrontConnectedFailer,
    
    SYSTEM_MD_TICK:OnTick,
    SYSTEM_MD_M1:OnM1,
    SYSTEM_MD_M3:OnM3,
    SYSTEM_MD_M5:OnM5,
    SYSTEM_MD_M10:OnM10,
    SYSTEM_MD_M15:OnM15,
    SYSTEM_MD_M30:OnM30,
    SYSTEM_MD_M60:OnM60,    
    SYSTEM_MD_M120:OnM120,    
    SYSTEM_SYSTEM_ERROR:OnError,
 
}
#-----------------------------------------------------------------------------------------
 

# main()为程序入口函数，所有的行情、交易订阅、指标调用、下单的逻辑均写在此函数内执行
def main():
    #connectref=test.ConnectServer('data.quicklib.cn')  #官方维护的数据行情服务器，当前测试状态，将来会对多个用户并发做优化
    connectref=test.ConnectServer('127.0.0.1')  #127.0.0.1是本机IP地址，在本机运行收集工具（作为服务器）时使用
    if connectref==True:
        print u'连接历史回播行情服务器成功\n'
        result = test.GetTestData('ag1706','20170201', '20170401', 0)    
        if result == True:
            print u"数据服务器指令接收成功[开始重播行情]\n"
        else:
            print u"数据服务器指令接收失败[开始重播行情]\n"
    else:
        print u'连接历史回播行情服务器失败\n'

    while(1): 
        print(u"Wait for a New Cmd\n");
        cmddict[test.OnCmd()]()
        
        #终止发送行情（这里设置条件为num>10000停止接收，实盘可以对照ctp的行情，一旦补齐CTP的断档行情即可通过UnGetTestData()方法停止回播）
        if num>10000:
            result=test.UnGetTestData()    
            if result == True:
                print u"数据服务器指令接收成功[停止重播行情]"
            else:
                print u"数据服务器指令接收失败[停止重播行情]"
        print(u"A New cmd\n")     
 
if __name__ == '__main__':
    main()
    

    
 
    
    
    
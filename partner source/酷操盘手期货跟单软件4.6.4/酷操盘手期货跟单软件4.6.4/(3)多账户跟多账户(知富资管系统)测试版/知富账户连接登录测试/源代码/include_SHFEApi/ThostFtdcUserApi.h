/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file ThostFtdcUserApi.h
///@brief 定义了客户端接口
///@history 
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCUSERAPI_H)
#define _FTDCUSERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ThostFtdcUserApiStruct.h"

#if defined(USERAPI_IS_LIB) && defined(WIN32)
#ifdef LIB_USER_API_EXPORT
#define USER_API_EXPORT __declspec(dllexport)
#else
#define USER_API_EXPORT __declspec(dllimport)
#endif
#else
#define USER_API_EXPORT 
#endif


class CThostFtdcUserSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	

	///数据输出请求
	virtual void OnRspDataDump(CThostFtdcSettlementRefField *pSettlementRef, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///装载结算信息请求响应
	virtual void OnRspLoadSettlementInfo(CThostFtdcLoadSettlementInfoField *pLoadSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///全部登出请求响应
	virtual void OnRspLogoutAll(CThostFtdcLogoutAllField *pLogoutAll, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///强制用户登出请求响应
	virtual void OnRspForceUserLogout(CThostFtdcForceUserLogoutField *pForceUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///强制用户退出请求响应
	virtual void OnRspForceUserExit(CThostFtdcForceUserLogoutField *pForceUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金账户口令更新请求响应
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///预埋单录入请求响应
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///预埋撤单录入请求响应
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作请求响应
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询最大报单数量响应
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求银行资金转期货响应
	virtual void OnRspTransferBankToFuture(CThostFtdcTransferBankToFutureRspField *pTransferBankToFutureRsp, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求期货资金转银行响应
	virtual void OnRspTransferFutureToBank(CThostFtdcTransferFutureToBankRspField *pTransferFutureToBankRsp, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询银行资金响应
	virtual void OnRspTransferQryBank(CThostFtdcTransferQryBankRspField *pTransferQryBankRsp, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询银行交易明细响应
	virtual void OnRspTransferQryDetail(CThostFtdcTransferQryDetailRspField *pTransferQryDetailRsp, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///删除预埋单响应
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///删除预埋撤单响应
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///校验投资者密码响应
	virtual void OnRspVerifyInvestorPassword(CThostFtdcVerifyInvestorPasswordField *pVerifyInvestorPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加产品响应
	virtual void OnRspInsProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改产品响应
	virtual void OnRspUpdProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加合约响应
	virtual void OnRspInsInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改合约响应
	virtual void OnRspUpdInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加经纪公司响应
	virtual void OnRspInsBroker(CThostFtdcBrokerField *pBroker, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改经纪公司响应
	virtual void OnRspUpdBroker(CThostFtdcBrokerField *pBroker, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加交易员响应
	virtual void OnRspInsTrader(CThostFtdcTraderField *pTrader, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改交易员响应
	virtual void OnRspUpdTrader(CThostFtdcTraderField *pTrader, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加会员经纪公司关系响应
	virtual void OnRspInsPartBroker(CThostFtdcPartBrokerField *pPartBroker, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改会员经纪公司关系响应
	virtual void OnRspUpdPartBroker(CThostFtdcPartBrokerField *pPartBroker, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加管理用户响应
	virtual void OnRspInsSuperUser(CThostFtdcSuperUserField *pSuperUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改管理用户响应
	virtual void OnRspUpdSuperUser(CThostFtdcSuperUserField *pSuperUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加管理用户权限响应
	virtual void OnRspInsSuperUserFunction(CThostFtdcSuperUserFunctionField *pSuperUserFunction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除管理用户权限响应
	virtual void OnRspDelSuperUserFunction(CThostFtdcSuperUserFunctionField *pSuperUserFunction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加投资者响应
	virtual void OnRspInsInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改投资者响应
	virtual void OnRspUpdInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加交易编码响应
	virtual void OnRspInsTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改交易编码响应
	virtual void OnRspUpdTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除交易编码响应
	virtual void OnRspDelTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加投资者分组响应
	virtual void OnRspInsInvestorGroup(CThostFtdcInvestorGroupField *pInvestorGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改投资者分组响应
	virtual void OnRspUpdInvestorGroup(CThostFtdcInvestorGroupField *pInvestorGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改交易账号响应
	virtual void OnRspUpdTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改投资者持仓响应
	virtual void OnRspUpdInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加合约保证金率响应
	virtual void OnRspInsInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改合约保证金率响应
	virtual void OnRspUpdInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除合约保证金率响应
	virtual void OnRspDelInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加合约手续费率响应
	virtual void OnRspInsInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改合约手续费率响应
	virtual void OnRspUpdInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除合约手续费率响应
	virtual void OnRspDelInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加合约交易权限响应
	virtual void OnRspInsInstrumentTradingRight(CThostFtdcInstrumentTradingRightField *pInstrumentTradingRight, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改合约交易权限响应
	virtual void OnRspUpdInstrumentTradingRight(CThostFtdcInstrumentTradingRightField *pInstrumentTradingRight, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除合约交易权限响应
	virtual void OnRspDelInstrumentTradingRight(CThostFtdcInstrumentTradingRightField *pInstrumentTradingRight, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加经纪公司用户响应
	virtual void OnRspInsBrokerUser(CThostFtdcBrokerUserField *pBrokerUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改经纪公司用户响应
	virtual void OnRspUpdBrokerUser(CThostFtdcBrokerUserField *pBrokerUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除经纪公司用户响应
	virtual void OnRspDelBrokerUser(CThostFtdcBrokerUserField *pBrokerUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加经纪公司用户口令响应
	virtual void OnRspInsBrokerUserPassword(CThostFtdcBrokerUserPasswordField *pBrokerUserPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改经纪公司用户口令响应
	virtual void OnRspUpdBrokerUserPassword(CThostFtdcBrokerUserPasswordField *pBrokerUserPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除经纪公司用户口令响应
	virtual void OnRspDelBrokerUserPassword(CThostFtdcBrokerUserPasswordField *pBrokerUserPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加经纪公司用户权限响应
	virtual void OnRspInsBrokerUserFunction(CThostFtdcBrokerUserFunctionField *pBrokerUserFunction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除经纪公司用户权限响应
	virtual void OnRspDelBrokerUserFunction(CThostFtdcBrokerUserFunctionField *pBrokerUserFunction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加投资者交易用户关系响应
	virtual void OnRspInsInvestorUser(CThostFtdcInvestorUserField *pInvestorUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除投资者交易用户关系响应
	virtual void OnRspDelInvestorUser(CThostFtdcInvestorUserField *pInvestorUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除投资者响应
	virtual void OnRspDelInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求同步出入金响应
	virtual void OnRspSyncDeposit(CThostFtdcSyncDepositField *pSyncDeposit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加合约保证金率调整响应
	virtual void OnRspInsInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField *pInstrumentMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改合约保证金率调整响应
	virtual void OnRspUpdInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField *pInstrumentMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除合约保证金率调整响应
	virtual void OnRspDelInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField *pInstrumentMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加交易所保证金率响应
	virtual void OnRspInsExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改交易所保证金率响应
	virtual void OnRspUpdExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除交易所保证金率响应
	virtual void OnRspDelExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加交易所保证金率调整响应
	virtual void OnRspInsExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改交易所保证金率调整响应
	virtual void OnRspUpdExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除交易所保证金率调整响应
	virtual void OnRspDelExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加投资者账户响应
	virtual void OnRspInsInvestorAccount(CThostFtdcInvestorAccountField *pInvestorAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改投资者账户响应
	virtual void OnRspUpdInvestorAccount(CThostFtdcInvestorAccountField *pInvestorAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除投资者账户响应
	virtual void OnRspDelInvestorAccount(CThostFtdcInvestorAccountField *pInvestorAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加浮动盈亏算法响应
	virtual void OnRspInsPositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField *pPositionProfitAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改浮动盈亏算法响应
	virtual void OnRspUpdPositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField *pPositionProfitAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除浮动盈亏算法响应
	virtual void OnRspDelPositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField *pPositionProfitAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加会员资金折扣响应
	virtual void OnRspInsDiscount(CThostFtdcDiscountField *pDiscount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改会员资金折扣响应
	virtual void OnRspUpdDiscount(CThostFtdcDiscountField *pDiscount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除会员资金折扣响应
	virtual void OnRspDelDiscount(CThostFtdcDiscountField *pDiscount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求同步信用额度响应
	virtual void OnRspSyncCredit(CThostFtdcSyncDepositField *pSyncDeposit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求同步质押额度响应
	virtual void OnRspSyncMortgage(CThostFtdcSyncDepositField *pSyncDeposit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加资金账户密码响应
	virtual void OnRspInsTradingAccountPassword(CThostFtdcTradingAccountPasswordField *pTradingAccountPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改资金账户密码响应
	virtual void OnRspUpdTradingAccountPassword(CThostFtdcTradingAccountPasswordField *pTradingAccountPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除资金账户密码响应
	virtual void OnRspDelTradingAccountPassword(CThostFtdcTradingAccountPasswordField *pTradingAccountPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加客户通知响应
	virtual void OnRspInsNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改客户通知响应
	virtual void OnRspUpdNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除客户通知响应
	virtual void OnRspDelNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加用户权限响应
	virtual void OnRspInsUserRight(CThostFtdcUserRightField *pUserRight, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改用户权限响应
	virtual void OnRspUpdUserRight(CThostFtdcUserRightField *pUserRight, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除用户权限响应
	virtual void OnRspDelUserRight(CThostFtdcUserRightField *pUserRight, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求同步冲销
	virtual void OnRspSyncCharge(CThostFtdcSyncDepositField *pSyncDeposit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加经纪公司可提资金算法表响应
	virtual void OnRspInsBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField *pBrokerWithdrawAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改经纪公司可提资金算法表响应
	virtual void OnRspUpdBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField *pBrokerWithdrawAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除经纪公司可提资金算法表响应
	virtual void OnRspDelBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField *pBrokerWithdrawAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加投资者可提资金算法表响应
	virtual void OnRspInsInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField *pInvestorWithdrawAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改投资者可提资金算法表响应
	virtual void OnRspUpdInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField *pInvestorWithdrawAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除投资者可提资金算法表响应
	virtual void OnRspDelInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField *pInvestorWithdrawAlgorithm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加用户IP响应
	virtual void OnRspInsUserIP(CThostFtdcUserIPField *pUserIP, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改用户IP响应
	virtual void OnRspUpdUserIP(CThostFtdcUserIPField *pUserIP, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除用户IP响应
	virtual void OnRspDelUserIP(CThostFtdcUserIPField *pUserIP, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求增加客户通知响应
	virtual void OnRspInsTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求修改客户通知响应
	virtual void OnRspUpdTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求删除客户通知响应
	virtual void OnRspDelTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易编码响应
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者分组响应
	virtual void OnRspQryInvestorGroup(CThostFtdcInvestorGroupField *pInvestorGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约保证金率响应
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约交易权限响应
	virtual void OnRspQryInstrumentTradingRight(CThostFtdcInstrumentTradingRightField *pInstrumentTradingRight, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司响应
	virtual void OnRspQryBroker(CThostFtdcBrokerField *pBroker, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易员响应
	virtual void OnRspQryTrader(CThostFtdcTraderField *pTrader, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司会员代码响应
	virtual void OnRspQryPartBroker(CThostFtdcPartBrokerField *pPartBroker, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询管理用户功能权限响应
	virtual void OnRspQrySuperUserFunction(CThostFtdcSuperUserFunctionField *pSuperUserFunction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询用户会话响应
	virtual void OnRspQryUserSession(CThostFtdcUserSessionField *pUserSession, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询前置状态响应
	virtual void OnRspQryFrontStatus(CThostFtdcFrontStatusField *pFrontStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所报单响应
	virtual void OnRspQryExchangeOrder(CThostFtdcExchangeOrderField *pExchangeOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查报单操作响应
	virtual void OnRspQryOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所报单操作响应
	virtual void OnRspQryExchangeOrderAction(CThostFtdcExchangeOrderActionField *pExchangeOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询管理用户响应
	virtual void OnRspQrySuperUser(CThostFtdcSuperUserField *pSuperUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所响应
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询产品响应
	virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司用户响应
	virtual void OnRspQryBrokerUser(CThostFtdcBrokerUserField *pBrokerUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司用户权限响应
	virtual void OnRspQryBrokerUserFunction(CThostFtdcBrokerUserFunctionField *pBrokerUserFunction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者交易用户关系响应
	virtual void OnRspQryInvestorUser(CThostFtdcInvestorUserField *pInvestorUser, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易员报盘机响应
	virtual void OnRspQryTraderOffer(CThostFtdcTraderOfferField *pTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询出入金流水响应
	virtual void OnRspQrySyncDeposit(CThostFtdcSyncDepositField *pSyncDeposit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者结算结果响应
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约状态响应
	virtual void OnRspQryInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询强平次序的投资者持仓响应
	virtual void OnRspQryForceClosePosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询转帐银行响应
	virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情报盘机响应
	virtual void OnRspQryMDTraderOffer(CThostFtdcMDTraderOfferField *pMDTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询客户通知响应
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询结算信息确认响应
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询组合合约分腿响应
	virtual void OnRspQryCombinationLeg(CThostFtdcCombinationLegField *pCombinationLeg, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询数据同步状态响应
	virtual void OnRspQrySyncStatus(CThostFtdcSyncStatusField *pSyncStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询联系人响应
	virtual void OnRspQryLinkMan(CThostFtdcLinkManField *pLinkMan, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询联系人响应
	virtual void OnRspQryBrokerUserEvent(CThostFtdcBrokerUserEventField *pBrokerUserEvent, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者组合持仓明细响应
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询错误报单响应
	virtual void OnRspQryErrOrder(CThostFtdcErrOrderField *pErrOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询错误报单操作响应
	virtual void OnRspQryErrOrderAction(CThostFtdcErrOrderActionField *pErrOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所状态响应
	virtual void OnRspQryExchangeSequence(CThostFtdcExchangeSequenceField *pExchangeSequence, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询历史报单响应
	virtual void OnRspHisQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) {};

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {};

	///预埋单录入错误回报
	virtual void OnErrRtnParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///预埋撤单录入错误回报
	virtual void OnErrRtnParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///删除预埋单录入错误回报
	virtual void OnErrRtnRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///删除预埋撤单录入错误回报
	virtual void OnErrRtnRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///交易通知
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {};

	///请求查询签约银行响应
	virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询预埋单响应
	virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询预埋撤单响应
	virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易通知响应
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class USER_API_EXPORT CThostFtdcUserApi
{
public:
	///创建UserApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CThostFtdcUserApi *CreateFtdcUserApi(const char *pszFlowPath = "");
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CThostFtdcUserSpi *pSpi) = 0;
	
	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;

	virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;
	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(TE_RESUME_TYPE nResumeType) = 0;

	///用户登录请求
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;

	///数据输出请求
	virtual int ReqDataDump(CThostFtdcSettlementRefField *pSettlementRef, int nRequestID) = 0;

	///装载结算信息请求
	virtual int ReqLoadSettlementInfo(CThostFtdcLoadSettlementInfoField *pLoadSettlementInfo, int nRequestID) = 0;

	///登出请求
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	///全部登出请求
	virtual int ReqLogoutAll(CThostFtdcLogoutAllField *pLogoutAll, int nRequestID) = 0;

	///强制用户登出请求
	virtual int ReqForceUserLogout(CThostFtdcForceUserLogoutField *pForceUserLogout, int nRequestID) = 0;

	///用户口令更新请求
	virtual int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///强制用户退出请求
	virtual int ReqForceUserExit(CThostFtdcForceUserLogoutField *pForceUserLogout, int nRequestID) = 0;

	///资金账户口令更新请求
	virtual int ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///预埋单录入请求
	virtual int ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID) = 0;

	///预埋撤单录入请求
	virtual int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) = 0;

	///查询最大报单数量请求
	virtual int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID) = 0;

	///投资者结算结果确认
	virtual int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) = 0;

	///请求银行资金转期货
	virtual int ReqTransferBankToFuture(CThostFtdcTransferHeaderField *pTransferHeader, CThostFtdcTransferBankToFutureReqField *pTransferBankToFutureReq, int nRequestID) = 0;

	///请求期货资金转银行
	virtual int ReqTransferFutureToBank(CThostFtdcTransferHeaderField *pTransferHeader, CThostFtdcTransferFutureToBankReqField *pTransferFutureToBankReq, int nRequestID) = 0;

	///请求查询银行资金
	virtual int ReqTransferQryBank(CThostFtdcTransferHeaderField *pTransferHeader, CThostFtdcTransferQryBankReqField *pTransferQryBankReq, int nRequestID) = 0;

	///请求查询银行交易明细
	virtual int ReqTransferQryDetail(CThostFtdcTransferHeaderField *pTransferHeader, CThostFtdcTransferQryDetailReqField *pTransferQryDetailReq, int nRequestID) = 0;

	///请求删除预埋单
	virtual int ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID) = 0;

	///请求删除预埋撤单
	virtual int ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID) = 0;

	///请求校验投资者密码
	virtual int ReqVerifyInvestorPassword(CThostFtdcVerifyInvestorPasswordField *pVerifyInvestorPassword, int nRequestID) = 0;

	///请求增加产品
	virtual int ReqInsProduct(CThostFtdcProductField *pProduct, int nRequestID) = 0;

	///请求修改产品
	virtual int ReqUpdProduct(CThostFtdcProductField *pProduct, int nRequestID) = 0;

	///请求增加合约
	virtual int ReqInsInstrument(CThostFtdcInstrumentField *pInstrument, int nRequestID) = 0;

	///请求修改合约
	virtual int ReqUpdInstrument(CThostFtdcInstrumentField *pInstrument, int nRequestID) = 0;

	///请求增加经纪公司
	virtual int ReqInsBroker(CThostFtdcBrokerField *pBroker, int nRequestID) = 0;

	///请求修改经纪公司
	virtual int ReqUpdBroker(CThostFtdcBrokerField *pBroker, int nRequestID) = 0;

	///请求增加交易员
	virtual int ReqInsTrader(CThostFtdcTraderField *pTrader, int nRequestID) = 0;

	///请求修改交易员
	virtual int ReqUpdTrader(CThostFtdcTraderField *pTrader, int nRequestID) = 0;

	///请求增加会员经纪公司关系
	virtual int ReqInsPartBroker(CThostFtdcPartBrokerField *pPartBroker, int nRequestID) = 0;

	///请求修改会员经纪公司关系
	virtual int ReqUpdPartBroker(CThostFtdcPartBrokerField *pPartBroker, int nRequestID) = 0;

	///请求增加管理用户
	virtual int ReqInsSuperUser(CThostFtdcSuperUserField *pSuperUser, int nRequestID) = 0;

	///请求修改管理用户
	virtual int ReqUpdSuperUser(CThostFtdcSuperUserField *pSuperUser, int nRequestID) = 0;

	///请求增加管理用户权限
	virtual int ReqInsSuperUserFunction(CThostFtdcSuperUserFunctionField *pSuperUserFunction, int nRequestID) = 0;

	///请求删除管理用户权限
	virtual int ReqDelSuperUserFunction(CThostFtdcSuperUserFunctionField *pSuperUserFunction, int nRequestID) = 0;

	///请求增加投资者
	virtual int ReqInsInvestor(CThostFtdcInvestorField *pInvestor, int nRequestID) = 0;

	///请求修改投资者
	virtual int ReqUpdInvestor(CThostFtdcInvestorField *pInvestor, int nRequestID) = 0;

	///请求增加交易编码
	virtual int ReqInsTradingCode(CThostFtdcTradingCodeField *pTradingCode, int nRequestID) = 0;

	///请求修改交易编码
	virtual int ReqUpdTradingCode(CThostFtdcTradingCodeField *pTradingCode, int nRequestID) = 0;

	///请求删除交易编码
	virtual int ReqDelTradingCode(CThostFtdcTradingCodeField *pTradingCode, int nRequestID) = 0;

	///请求增加投资者分组
	virtual int ReqInsInvestorGroup(CThostFtdcInvestorGroupField *pInvestorGroup, int nRequestID) = 0;

	///请求修改投资者分组
	virtual int ReqUpdInvestorGroup(CThostFtdcInvestorGroupField *pInvestorGroup, int nRequestID) = 0;

	///请求修改交易账号
	virtual int ReqUpdTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, int nRequestID) = 0;

	///请求修改投资者持仓
	virtual int ReqUpdInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, int nRequestID) = 0;

	///请求增加合约保证金率
	virtual int ReqInsInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, int nRequestID) = 0;

	///请求修改合约保证金率
	virtual int ReqUpdInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, int nRequestID) = 0;

	///请求删除合约保证金率
	virtual int ReqDelInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, int nRequestID) = 0;

	///请求增加合约手续费率
	virtual int ReqInsInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, int nRequestID) = 0;

	///请求修改合约手续费率
	virtual int ReqUpdInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, int nRequestID) = 0;

	///请求删除合约手续费率
	virtual int ReqDelInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, int nRequestID) = 0;

	///请求增加合约交易权限
	virtual int ReqInsInstrumentTradingRight(CThostFtdcInstrumentTradingRightField *pInstrumentTradingRight, int nRequestID) = 0;

	///请求修改合约交易权限
	virtual int ReqUpdInstrumentTradingRight(CThostFtdcInstrumentTradingRightField *pInstrumentTradingRight, int nRequestID) = 0;

	///请求删除合约交易权限
	virtual int ReqDelInstrumentTradingRight(CThostFtdcInstrumentTradingRightField *pInstrumentTradingRight, int nRequestID) = 0;

	///请求增加经纪公司用户
	virtual int ReqInsBrokerUser(CThostFtdcBrokerUserField *pBrokerUser, int nRequestID) = 0;

	///请求修改经纪公司用户
	virtual int ReqUpdBrokerUser(CThostFtdcBrokerUserField *pBrokerUser, int nRequestID) = 0;

	///请求删除经纪公司用户
	virtual int ReqDelBrokerUser(CThostFtdcBrokerUserField *pBrokerUser, int nRequestID) = 0;

	///请求增加经纪公司用户口令
	virtual int ReqInsBrokerUserPassword(CThostFtdcBrokerUserPasswordField *pBrokerUserPassword, int nRequestID) = 0;

	///请求修改经纪公司用户口令
	virtual int ReqUpdBrokerUserPassword(CThostFtdcBrokerUserPasswordField *pBrokerUserPassword, int nRequestID) = 0;

	///请求删除经纪公司用户口令
	virtual int ReqDelBrokerUserPassword(CThostFtdcBrokerUserPasswordField *pBrokerUserPassword, int nRequestID) = 0;

	///请求增加经纪公司用户权限
	virtual int ReqInsBrokerUserFunction(CThostFtdcBrokerUserFunctionField *pBrokerUserFunction, int nRequestID) = 0;

	///请求删除经纪公司用户权限
	virtual int ReqDelBrokerUserFunction(CThostFtdcBrokerUserFunctionField *pBrokerUserFunction, int nRequestID) = 0;

	///请求增加投资者交易用户关系
	virtual int ReqInsInvestorUser(CThostFtdcInvestorUserField *pInvestorUser, int nRequestID) = 0;

	///请求删除投资者交易用户关系
	virtual int ReqDelInvestorUser(CThostFtdcInvestorUserField *pInvestorUser, int nRequestID) = 0;

	///请求删除投资者
	virtual int ReqDelInvestor(CThostFtdcInvestorField *pInvestor, int nRequestID) = 0;

	///请求同步出入金
	virtual int ReqSyncDeposit(CThostFtdcSyncDepositField *pSyncDeposit, int nRequestID) = 0;

	///请求增加合约保证金率调整
	virtual int ReqInsInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField *pInstrumentMarginRateAdjust, int nRequestID) = 0;

	///请求修改合约保证金率调整
	virtual int ReqUpdInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField *pInstrumentMarginRateAdjust, int nRequestID) = 0;

	///请求删除合约保证金率调整
	virtual int ReqDelInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField *pInstrumentMarginRateAdjust, int nRequestID) = 0;

	///请求增加交易所保证金率
	virtual int ReqInsExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, int nRequestID) = 0;

	///请求修改交易所保证金率
	virtual int ReqUpdExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, int nRequestID) = 0;

	///请求删除交易所保证金率
	virtual int ReqDelExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, int nRequestID) = 0;

	///请求增加交易所保证金率调整
	virtual int ReqInsExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, int nRequestID) = 0;

	///请求修改交易所保证金率调整
	virtual int ReqUpdExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, int nRequestID) = 0;

	///请求删除交易所保证金率调整
	virtual int ReqDelExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, int nRequestID) = 0;

	///请求增加投资者账户
	virtual int ReqInsInvestorAccount(CThostFtdcInvestorAccountField *pInvestorAccount, int nRequestID) = 0;

	///请求修改投资者账户
	virtual int ReqUpdInvestorAccount(CThostFtdcInvestorAccountField *pInvestorAccount, int nRequestID) = 0;

	///请求删除投资者账户
	virtual int ReqDelInvestorAccount(CThostFtdcInvestorAccountField *pInvestorAccount, int nRequestID) = 0;

	///请求增加浮动盈亏算法
	virtual int ReqInsPositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField *pPositionProfitAlgorithm, int nRequestID) = 0;

	///请求修改浮动盈亏算法
	virtual int ReqUpdPositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField *pPositionProfitAlgorithm, int nRequestID) = 0;

	///请求删除浮动盈亏算法
	virtual int ReqDelPositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField *pPositionProfitAlgorithm, int nRequestID) = 0;

	///请求增加会员资金折扣
	virtual int ReqInsDiscount(CThostFtdcDiscountField *pDiscount, int nRequestID) = 0;

	///请求修改会员资金折扣
	virtual int ReqUpdDiscount(CThostFtdcDiscountField *pDiscount, int nRequestID) = 0;

	///请求删除会员资金折扣
	virtual int ReqDelDiscount(CThostFtdcDiscountField *pDiscount, int nRequestID) = 0;

	///请求同步信用额度
	virtual int ReqSyncCredit(CThostFtdcSyncDepositField *pSyncDeposit, int nRequestID) = 0;

	///请求同步质押额度
	virtual int ReqSyncMortgage(CThostFtdcSyncDepositField *pSyncDeposit, int nRequestID) = 0;

	///请求增加资金账户密码
	virtual int ReqInsTradingAccountPassword(CThostFtdcTradingAccountPasswordField *pTradingAccountPassword, int nRequestID) = 0;

	///请求修改资金账户密码
	virtual int ReqUpdTradingAccountPassword(CThostFtdcTradingAccountPasswordField *pTradingAccountPassword, int nRequestID) = 0;

	///请求删除资金账户密码
	virtual int ReqDelTradingAccountPassword(CThostFtdcTradingAccountPasswordField *pTradingAccountPassword, int nRequestID) = 0;

	///请求增加客户通知
	virtual int ReqInsNotice(CThostFtdcNoticeField *pNotice, int nRequestID) = 0;

	///请求修改客户通知
	virtual int ReqUpdNotice(CThostFtdcNoticeField *pNotice, int nRequestID) = 0;

	///请求删除客户通知
	virtual int ReqDelNotice(CThostFtdcNoticeField *pNotice, int nRequestID) = 0;

	///请求增加用户权限
	virtual int ReqInsUserRight(CThostFtdcUserRightField *pUserRight, int nRequestID) = 0;

	///请求修改用户权限
	virtual int ReqUpdUserRight(CThostFtdcUserRightField *pUserRight, int nRequestID) = 0;

	///请求删除用户权限
	virtual int ReqDelUserRight(CThostFtdcUserRightField *pUserRight, int nRequestID) = 0;

	///请求同步冲销
	virtual int ReqSyncCharge(CThostFtdcSyncDepositField *pSyncDeposit, int nRequestID) = 0;

	///请求增加经纪公司可提资金算法表
	virtual int ReqInsBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField *pBrokerWithdrawAlgorithm, int nRequestID) = 0;

	///请求修改经纪公司可提资金算法表
	virtual int ReqUpdBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField *pBrokerWithdrawAlgorithm, int nRequestID) = 0;

	///请求删除经纪公司可提资金算法表
	virtual int ReqDelBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField *pBrokerWithdrawAlgorithm, int nRequestID) = 0;

	///请求增加投资者可提资金算法表
	virtual int ReqInsInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField *pInvestorWithdrawAlgorithm, int nRequestID) = 0;

	///请求修改投资者可提资金算法表
	virtual int ReqUpdInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField *pInvestorWithdrawAlgorithm, int nRequestID) = 0;

	///请求删除投资者可提资金算法表
	virtual int ReqDelInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField *pInvestorWithdrawAlgorithm, int nRequestID) = 0;

	///请求增加用户IP
	virtual int ReqInsUserIP(CThostFtdcUserIPField *pUserIP, int nRequestID) = 0;

	///请求修改用户IP
	virtual int ReqUpdUserIP(CThostFtdcUserIPField *pUserIP, int nRequestID) = 0;

	///请求删除用户IP
	virtual int ReqDelUserIP(CThostFtdcUserIPField *pUserIP, int nRequestID) = 0;

	///请求增加客户通知
	virtual int ReqInsTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, int nRequestID) = 0;

	///请求修改客户通知
	virtual int ReqUpdTradingNotice(CThostFtdcNoticeField *pNotice, int nRequestID) = 0;

	///请求删除客户通知
	virtual int ReqDelTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, int nRequestID) = 0;

	///请求查询报单
	virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///请求查询成交
	virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///请求查询投资者持仓
	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///请求查询资金账户
	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	///请求查询投资者
	virtual int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID) = 0;

	///请求查询交易编码
	virtual int ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID) = 0;

	///请求查询投资者分组
	virtual int ReqQryInvestorGroup(CThostFtdcQryInvestorGroupField *pQryInvestorGroup, int nRequestID) = 0;

	///请求查询合约保证金率
	virtual int ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID) = 0;

	///请求查询合约手续费率
	virtual int ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID) = 0;

	///请求查询合约交易权限率
	virtual int ReqQryInstrumentTradingRight(CThostFtdcQryInstrumentTradingRightField *pQryInstrumentTradingRight, int nRequestID) = 0;

	///请求查询经纪公司
	virtual int ReqQryBroker(CThostFtdcQryBrokerField *pQryBroker, int nRequestID) = 0;

	///请求查询交易员
	virtual int ReqQryTrader(CThostFtdcQryTraderField *pQryTrader, int nRequestID) = 0;

	///请求查询经纪公司会员代码
	virtual int ReqQryPartBroker(CThostFtdcQryPartBrokerField *pQryPartBroker, int nRequestID) = 0;

	///请求查询管理用户功能权限
	virtual int ReqQrySuperUserFunction(CThostFtdcQrySuperUserFunctionField *pQrySuperUserFunction, int nRequestID) = 0;

	///请求查询用户会话
	virtual int ReqQryUserSession(CThostFtdcQryUserSessionField *pQryUserSession, int nRequestID) = 0;

	///请求查询前置状态
	virtual int ReqQryFrontStatus(CThostFtdcQryFrontStatusField *pQryFrontStatus, int nRequestID) = 0;

	///请求查询交易所报单
	virtual int ReqQryExchangeOrder(CThostFtdcQryExchangeOrderField *pQryExchangeOrder, int nRequestID) = 0;

	///请求查询报单操作
	virtual int ReqQryOrderAction(CThostFtdcQryOrderActionField *pQryOrderAction, int nRequestID) = 0;

	///请求查询交易所报单操作
	virtual int ReqQryExchangeOrderAction(CThostFtdcQryExchangeOrderActionField *pQryExchangeOrderAction, int nRequestID) = 0;

	///请求查询管理用户
	virtual int ReqQrySuperUser(CThostFtdcQrySuperUserField *pQrySuperUser, int nRequestID) = 0;

	///请求查询交易所
	virtual int ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID) = 0;

	///请求查询产品
	virtual int ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID) = 0;

	///请求查询合约
	virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///请求查询行情
	virtual int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) = 0;

	///请求查询经纪公司用户
	virtual int ReqQryBrokerUser(CThostFtdcQryBrokerUserField *pQryBrokerUser, int nRequestID) = 0;

	///请求查询经纪公司用户权限
	virtual int ReqQryBrokerUserFunction(CThostFtdcQryBrokerUserFunctionField *pQryBrokerUserFunction, int nRequestID) = 0;

	///请求查询投资者交易用户关系
	virtual int ReqQryInvestorUser(CThostFtdcQryInvestorUserField *pQryInvestorUser, int nRequestID) = 0;

	///请求查询交易员报盘机
	virtual int ReqQryTraderOffer(CThostFtdcQryTraderOfferField *pQryTraderOffer, int nRequestID) = 0;

	///请求查询出入金流水
	virtual int ReqQrySyncDeposit(CThostFtdcQrySyncDepositField *pQrySyncDeposit, int nRequestID) = 0;

	///请求查询投资者结算结果
	virtual int ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID) = 0;

	///请求查询合约状态
	virtual int ReqQryInstrumentStatus(CThostFtdcQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///请求查询强平次序的投资者持仓
	virtual int ReqQryForceClosePosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///请求查询转帐银行
	virtual int ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID) = 0;

	///请求查询投资者持仓明细
	virtual int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) = 0;

	///请求查询行情报盘机
	virtual int ReqQryMDTraderOffer(CThostFtdcQryMDTraderOfferField *pQryMDTraderOffer, int nRequestID) = 0;

	///请求查询客户通知
	virtual int ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID) = 0;

	///请求查询结算信息确认
	virtual int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID) = 0;

	///请求查询组合合约分腿
	virtual int ReqQryCombinationLeg(CThostFtdcQryCombinationLegField *pQryCombinationLeg, int nRequestID) = 0;

	///请求查询数据同步状态
	virtual int ReqQrySyncStatus(CThostFtdcQrySyncStatusField *pQrySyncStatus, int nRequestID) = 0;

	///请求查询联系人
	virtual int ReqQryLinkMan(CThostFtdcQryLinkManField *pQryLinkMan, int nRequestID) = 0;

	///请求查询联系人
	virtual int ReqQryBrokerUserEvent(CThostFtdcQryBrokerUserEventField *pQryBrokerUserEvent, int nRequestID) = 0;

	///请求查询投资者持仓明细
	virtual int ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID) = 0;

	///请求查询错误报单
	virtual int ReqQryErrOrder(CThostFtdcQryErrOrderField *pQryErrOrder, int nRequestID) = 0;

	///请求查询错误报单操作
	virtual int ReqQryErrOrderAction(CThostFtdcQryErrOrderActionField *pQryErrOrderAction, int nRequestID) = 0;

	///请求查询交易所状态
	virtual int ReqQryExchangeSequence(CThostFtdcQryExchangeSequenceField *pQryExchangeSequence, int nRequestID) = 0;

	///请求查询历史报单
	virtual int ReqHisQryOrder(CThostFtdcQryHisOrderField *pQryHisOrder, int nRequestID) = 0;

	///请求查询签约银行
	virtual int ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID) = 0;

	///请求查询预埋单
	virtual int ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID) = 0;

	///请求查询预埋撤单
	virtual int ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID) = 0;

	///请求查询交易通知
	virtual int ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID) = 0;
protected:
	~CThostFtdcUserApi(){};
};

#endif

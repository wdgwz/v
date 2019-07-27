# coding=utf-8
from __future__ import division
from backtest import *
import os
import pandas as pd
from math import floor


# 计算复权价格
def cal_right_price(input_stock_data, type='前复权'):
    """
    :param input_stock_data: 标准股票数据，需要'收盘价', '涨跌幅'
    :param type: 确定是前复权还是后复权，分别为'后复权'，'前复权'
    :return: 新增一列'后复权价'/'前复权价'的stock_data
    """
    # 计算收盘复权价
    stock_data = input_stock_data.copy()
    num = {'后复权': 0, '前复权': -1}
    price1 = stock_data['close'].iloc[num[type]]
    stock_data['复权价_temp'] = (stock_data['change'] + 1.0).cumprod()
    price2 = stock_data['复权价_temp'].iloc[num[type]]
    stock_data['复权价'] = stock_data['复权价_temp'] * (price1 / price2)
    stock_data.pop('复权价_temp')

    # 计算开盘复权价
    stock_data['复权价_开盘'] = stock_data['复权价'] / (stock_data['close'] / stock_data['open'])
    return stock_data[['复权价_开盘', '复权价']]


# 获取股票数据
def get_stock_data():
    # 遍历数据文件夹中所有股票文件的文件名，得到股票代码列表
    stock_code_list = []
    # 此处为股票数据文件的本地路径，请自行修改
    for root, dirs, files in os.walk('e:/data/stock data'):
        if files:
            for f in files:
                if '.csv' in f:
                    stock_code_list.append(f.split('.csv')[0])

    all_stock = pd.DataFrame()

    for code in stock_code_list:
        # 此处为股票数据文件的本地路径，请自行修改
        stock_data = pd.read_csv('e:/data/stock data/' + code + '.csv', parse_dates=['date'])
        stock_data = stock_data[['code', 'date', 'open', 'close', 'change']].sort_values(by='date')
        stock_data.reset_index(drop=True, inplace=True)
        # 计算复权价
        stock_data[['open', 'close']] = cal_right_price(stock_data, type='后复权')
        # 判断每天开盘是否涨停
        stock_data.ix[stock_data['open'] > stock_data['close'].shift(1) * 1.097, 'limit_up'] = 1
        stock_data['limit_up'].fillna(0, inplace=True)

        all_stock = all_stock.append(stock_data, ignore_index=True)

    return all_stock[['code', 'date', 'change', 'limit_up']]


def momentum_and_contrarian(all_stock, start_date, end_date, window=3):
    """
    :param all_stock: 所有股票的数据集
    :param start_date: 起始日期（包含排名期）
    :param end_date: 结束日期
    :param window: 排名期的月份数，默认为3个月
    :return: 返回动量策略和反转策略的收益率和资金曲线
    """
    # 取出指数数据作为交易天数的参考标准, 此处为指数数据文件的本地路径，请自行修改
    index_data = pd.read_csv('e:/data/index data/sh000001.csv', parse_dates=True, index_col='date')
    index_data.sort_index(inplace=True)
    index_data = index_data[start_date:end_date]
    # 转换成月度数据
    by_month = index_data[['close']].resample('M', how='last')
    by_month.reset_index(inplace=True)

    momentum_portfolio_all = pd.DataFrame()
    contrarian_portfolio_all = pd.DataFrame()

    for i in range(window, len(by_month) - 1):
        start_month = by_month['date'].iloc[i - window]  # 排名期第一个月
        end_month = by_month['date'].iloc[i]  # 排名期最后一个月

        # 取出在排名期内的数据
        stock_temp = all_stock[(all_stock['date'] > start_month) & (all_stock['date'] <= end_month)]

        # 将指数在这段时间的数据取出作为交易日天数的标准
        index_temp = index_data[start_month:end_month]

        # 统计每只股票在排名期的交易日天数
        trading_days = stock_temp['code'].value_counts()
        # 剔除在排名期内累计停牌超过（5*月数）天的股票，即如果排名期为3个月，就剔除累计停牌超过15天的股票
        keep_list = trading_days[trading_days >= (len(index_temp) - 5 * window)].index
        stock_temp = stock_temp[stock_temp['code'].isin(keep_list)]

        # 计算每只股票在排名期的累计收益率
        grouped = stock_temp.groupby('code')['change'].agg({'return': lambda x: (x + 1).prod() - 1})
        # 将累计收益率排序
        grouped.sort_values(by='return', inplace=True)
        # 取排序后前5%的股票构造反转策略的组合，后5%的股票构造动量策略的组合
        num = floor(len(grouped) * 0.05)
        momentum_code_list = grouped.index[-num:]  # 动量组合的股票代码列表
        contrarian_code_list = grouped.index[0:num]  # 反转组合的股票代码列表

        # ============================动量组合============================
        # 取出动量组合内股票当月的数据
        momentum = all_stock.ix[(all_stock['code'].isin(momentum_code_list)) &
                                (all_stock['date'] > end_month) & (all_stock['date'] <= by_month['date'].iloc[i + 1])]

        # 剔除动量组合里在当月第一个交易日涨停的股票
        temp = momentum.groupby('code')['limit_up'].first()
        hold_list = temp[temp == 0].index
        momentum = momentum[momentum['code'].isin(hold_list)].reset_index(drop=True)
        # 动量组合
        momentum_portfolio = momentum.pivot('date', 'code', 'change').fillna(0)

        # 计算动量组合的收益率
        num = momentum_portfolio.shape[1]
        weights = num * [1. / num]
        momentum_portfolio['pf_rtn'] = np.dot(np.array(momentum_portfolio), np.array(weights))
        momentum_portfolio.reset_index(inplace=True)

        # 将每个月的动量组合收益数据合并
        momentum_portfolio_all = momentum_portfolio_all.append(momentum_portfolio[['date', 'pf_rtn']],
                                                               ignore_index=True)
        # 计算动量策略的资金曲线
        momentum_portfolio_all['capital'] = (1 + momentum_portfolio_all['pf_rtn']).cumprod()

        # ============================反转组合=============================
        # 取出反转组合内股票当月的数据
        contrarian = all_stock.ix[(all_stock['code'].isin(contrarian_code_list)) &
                                  (all_stock['date'] > end_month) & (all_stock['date'] <= by_month['date'].iloc[i + 1])]

        # 剔除反转组合里在当月第一个交易日涨停的股票
        temp = contrarian.groupby('code')['limit_up'].first()
        hold_list = temp[temp == 0].index
        contrarian = contrarian[contrarian['code'].isin(hold_list)].reset_index(drop=True)
        # 反转组合
        contrarian_portfolio = contrarian.pivot('date', 'code', 'change').fillna(0)

        # 计算反转组合的收益率
        num = contrarian_portfolio.shape[1]
        weights = num * [1. / num]
        contrarian_portfolio['pf_rtn'] = np.dot(np.array(contrarian_portfolio), np.array(weights))
        contrarian_portfolio.reset_index(inplace=True)

        # 将每个月的反转组合收益合并
        contrarian_portfolio_all = contrarian_portfolio_all.append(contrarian_portfolio[['date', 'pf_rtn']],
                                                                   ignore_index=True)
        # 计算反转策略的资金曲线
        contrarian_portfolio_all['capital'] = (1 + contrarian_portfolio_all['pf_rtn']).cumprod()

    return momentum_portfolio_all, contrarian_portfolio_all


# 读取股票数据
all_stock = get_stock_data()

# 从2011年1月开始形成排名期，排名期3个月，每月初根据前3个月的排名换仓
m, c = momentum_and_contrarian(all_stock, '2010-12-31', '2015-12-31', window=3)

date_line = list(m['date'])
capital_line = list(m['capital'])
return_line = list(m['pf_rtn'])
print '\n=====================动量策略主要回测指标====================='
annual_return(date_line, capital_line)
max_drawdown(date_line, capital_line)
sharpe_ratio(date_line, capital_line, return_line)

date_line = list(c['date'])
capital_line = list(c['capital'])
return_line = list(c['pf_rtn'])
print '\n=====================反转策略主要回测指标====================='
annual_return(date_line, capital_line)
max_drawdown(date_line, capital_line)
sharpe_ratio(date_line, capital_line, return_line)

# 同期大盘的相关指标
index_data = pd.read_csv('e:/data/index data/sh000001.csv', parse_dates=['date'])
index_data.sort_values(by='date', inplace=True)
index_data = index_data[index_data['date'].isin(date_line)]
capital_line = list(index_data['close'])
return_line = list(index_data['change'])
print '\n=====================同期上证指数主要回测指标====================='
annual_return(date_line, capital_line)
max_drawdown(date_line, capital_line)
sharpe_ratio(date_line, capital_line, return_line)

plt.figure(figsize=(14, 7))
m.set_index('date', inplace=True)
c.set_index('date', inplace=True)
index_data['cum_ret'] = (index_data['change'] + 1).cumprod() - 1
index_data.set_index('date', inplace=True)

(m['capital'] - 1).plot()
(c['capital'] - 1).plot()
index_data['cum_ret'].plot()
plt.title('Cumulative Return')
plt.legend(['momentum', 'contrarian', 'index'], loc='best')
plt.show()

# coding: utf-8
from __future__ import division

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from math import sqrt


# 计算年化收益率函数
def annual_return(date_line, capital_line):
    """
    :param date_line: 日期序列
    :param capital_line: 账户价值序列
    :return: 输出在回测期间的年化收益率
    """
    # 将数据序列合并成dataframe并按日期排序
    df = pd.DataFrame({'date': date_line, 'capital': capital_line})

    # 计算年化收益率
    annual = (df['capital'].iloc[-1] / df['capital'].iloc[0]) ** (250 / len(df)) - 1
    print '年化收益率为：%f' % annual


# 计算最大回撤函数
def max_drawdown(date_line, capital_line):
    """
    :param date_line: 日期序列
    :param capital_line: 账户价值序列
    :return: 输出最大回撤及开始日期和结束日期
    """
    # 将数据序列合并为一个dataframe
    df = pd.DataFrame({'date': date_line, 'capital': capital_line})

    df['max2here'] = pd.expanding_max(df['capital'])  # 计算当日之前的账户最大价值
    df['dd2here'] = df['capital'] / df['max2here'] - 1  # 计算当日的回撤

    # 计算最大回撤和结束时间
    temp = df.sort_values(by='dd2here').iloc[0][['date', 'dd2here']]
    max_dd = temp['dd2here']
    end_date = temp['date'].strftime('%Y-%m-%d')

    # 计算开始时间
    df = df[df['date'] <= end_date]
    start_date = df.sort_values(by='capital', ascending=False).iloc[0]['date'].strftime('%Y-%m-%d')

    print '最大回撤为：%f, 开始日期：%s, 结束日期：%s' % (max_dd, start_date, end_date)


# 计算平均涨幅
def average_change(date_line, return_line):
    """
    :param date_line: 日期序列
    :param return_line: 账户日收益率序列
    :return: 输出平均涨幅
    """
    df = pd.DataFrame({'date': date_line, 'rtn': return_line})
    ave = df['rtn'].mean()
    print '平均涨幅为：%f' % ave


# 计算上涨概率
def prob_up(date_line, return_line):
    """
    :param date_line: 日期序列
    :param return_line: 账户日收益率序列
    :return: 输出上涨概率
    """
    df = pd.DataFrame({'date': date_line, 'rtn': return_line})
    p_up = len(df[df['rtn'] > 0]) / len(df)
    print '上涨概率为：%f' % p_up


# 计算最大连续上涨天数和最大连续下跌天数
def max_successive_up(date_line, return_line):
    """
    :param date_line: 日期序列
    :param return_line: 账户日收益率序列
    :return: 输出最大连续上涨天数和最大连续下跌天数
    """
    df = pd.DataFrame({'date': date_line, 'rtn': return_line})
    # 新建一个全为空值的一列
    df['up'] = [np.nan] * len(df)

    # 当收益率大于0时，up取1，小于0时，up取0，等于0时采用前向差值
    df.ix[df['rtn'] > 0, 'up'] = 1
    df.ix[df['rtn'] < 0, 'up'] = 0
    df['up'].fillna(method='ffill', inplace=True)

    # 根据up这一列计算到某天为止连续上涨下跌的天数
    rtn_list = list(df['up'])
    successive_up_list = []
    num = 1
    for i in range(len(rtn_list)):
        if i == 0:
            successive_up_list.append(num)
        else:
            if (rtn_list[i] == rtn_list[i - 1] == 1) or (rtn_list[i] == rtn_list[i - 1] == 0):
                num += 1
            else:
                num = 1
            successive_up_list.append(num)
    # 将计算结果赋给新的一列'successive_up'
    df['successive_up'] = successive_up_list
    # 分别在上涨和下跌的两个dataframe里按照'successive_up'的值排序并取最大值
    max_successive_up = df[df['up'] == 1].sort_values(by='successive_up', ascending=False)['successive_up'].iloc[0]
    max_successive_down = df[df['up'] == 0].sort_values(by='successive_up', ascending=False)['successive_up'].iloc[0]
    print '最大连续上涨天数为：%d  最大连续下跌天数为：%d' % (max_successive_up, max_successive_down)


# 计算最大单周期涨幅和最大单周期跌幅
def max_period_return(date_line, return_line):
    """
    :param date_line: 日期序列
    :param return_line: 账户日收益率序列
    :return: 输出最大单周期涨幅和最大单周期跌幅
    """
    df = pd.DataFrame({'date': date_line, 'rtn': return_line})
    # 分别计算日收益率的最大值和最小值
    max_return = df['rtn'].max()
    min_return = df['rtn'].min()
    print '最大单周期涨幅为：%f  最大单周期跌幅为：%f' % (max_return, min_return)


# 计算收益波动率的函数
def volatility(date_line, return_line):
    """
    :param date_line: 日期序列
    :param return_line: 账户日收益率序列
    :return: 输出回测期间的收益波动率
    """
    df = pd.DataFrame({'date': date_line, 'rtn': return_line})
    # 计算波动率
    vol = df['rtn'].std() * sqrt(250)
    print '收益波动率为：%f' % vol


# 计算贝塔的函数
def beta(date_line, return_line, indexreturn_line):
    """
    :param date_line: 日期序列
    :param return_line: 账户日收益率序列
    :param indexreturn_line: 指数的收益率序列
    :return: 输出beta值
    """
    df = pd.DataFrame({'date': date_line, 'rtn': return_line, 'benchmark_rtn': indexreturn_line})
    # 账户收益和基准收益的协方差除以基准收益的方差
    b = df['rtn'].cov(df['benchmark_rtn']) / df['benchmark_rtn'].var()
    print 'beta: %f' % b


# 计算alpha的函数
def alpha(date_line, capital_line, index_line, return_line, indexreturn_line):
    """
    :param date_line: 日期序列
    :param capital_line: 账户价值序列
    :param index_line: 指数序列
    :param return_line: 账户日收益率序列
    :param indexreturn_line: 指数的收益率序列
    :return: 输出alpha值
    """
    # 将数据序列合并成dataframe并按日期排序
    df = pd.DataFrame({'date': date_line, 'capital': capital_line, 'benchmark': index_line, 'rtn': return_line,
                       'benchmark_rtn': indexreturn_line})
   
    rf = 0.0284  # 无风险利率取10年期国债的到期年化收益率

    annual_stock = (df['capital'].iloc[-1] / df['capital'].iloc[0]) ** (250 / len(df)) - 1  # 账户年化收益
    annual_index = (df['benchmark'].iloc[-1] / df['benchmark'].iloc[0]) ** (250 / len(df)) - 1  # 基准年化收益

    beta = df['rtn'].cov(df['benchmark_rtn']) / df['benchmark_rtn'].var()  # 计算贝塔值
    a = (annual_stock - rf) - beta * (annual_index - rf)  # 计算alpha值
    print 'alpha：%f' % a


# 计算夏普比函数
def sharpe_ratio(date_line, capital_line, return_line):
    """
    :param date_line: 日期序列
    :param capital_line: 账户价值序列
    :param return_line: 账户日收益率序列
    :return: 输出夏普比率
    """
    # 将数据序列合并为一个dataframe并按日期排序
    df = pd.DataFrame({'date': date_line, 'capital': capital_line, 'rtn': return_line})

    rf = 0.0284  # 无风险利率取10年期国债的到期年化收益率
    # 账户年化收益
    annual_stock = (df['capital'].iloc[-1] / df['capital'].iloc[0]) ** (250 / len(df)) - 1
    # 计算收益波动率
    vol = df['rtn'].std() * sqrt(250)
    # 计算夏普比
    sharpe = (annual_stock - rf) / vol
    print 'sharpe_ratio: %f' % sharpe


# 计算信息比率函数
def info_ratio(date_line, return_line, indexreturn_line):
    """
    :param date_line: 日期序列
    :param return_line: 账户日收益率序列
    :param indexreturn_line: 指数的收益率序列
    :return: 输出信息比率
    """
    df = pd.DataFrame({'date': date_line, 'rtn': return_line, 'benchmark_rtn': indexreturn_line})
    df['diff'] = df['rtn'] - df['benchmark_rtn']
    annual_mean = df['diff'].mean() * 250
    annual_std = df['diff'].std() * sqrt(250)
    info = annual_mean / annual_std
    print 'info_ratio: %f' % info


# 计算股票和基准在回测期间的累计收益率并画图
def cumulative_return(date_line, capital_line, index_line):
    """
    :param date_line: 日期序列
    :param capital_line: 账户总资产序列
    :param index_line: 指数序列
    :return: 画出股票和基准在回测期间的累计收益率的折线图
    """
    df = pd.DataFrame({'date': date_line, 'capital': capital_line, 'index': index_line})
    df['portfolio'] = df['capital'] / df.ix[0, 'capital'] - 1
    df['benchmark'] = df['index'] / df.ix[0, 'index'] - 1
    df.set_index('date', inplace=True)
    # 画出股票和基准在回测期间的累计收益率的折线图
    df['portfolio'].plot(style='b-', figsize=(14, 7))
    df['benchmark'].plot(style='g-')
    plt.legend(loc='best')
    plt.title('Cumulative Return')
    plt.show()

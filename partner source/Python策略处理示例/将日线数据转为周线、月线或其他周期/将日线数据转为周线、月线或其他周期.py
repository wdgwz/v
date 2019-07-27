# -*- coding: utf-8 -*-
import pandas as pd


# ========== 从原始csv文件中导入日线股票数据，以浦发银行sh600000为例

# 导入数据 - 注意：这里请填写数据文件在您电脑中的路径
#stock_data = pd.read_csv('trading-data@full/stock data/sh600000.csv', parse_dates=[1])

stock_data = pd.read_csv('sh600000.csv', parse_dates=[1])


# ========== 将导入的日线数据stock_data，转换为周线数据period_stock_data

# 设定转换的周期period_type，转换为周是'W'，月'M'，季度线'Q'，五分钟是'5min'，12天是'12D'
period_type = 'W'

# 将【date】设定为index
stock_data.set_index('date', inplace=True)

# 进行转换，周线的每个变量都等于那一周中最后一个交易日的变量值
period_stock_data = stock_data.resample(period_type, how='last')

# 周线的【change】等于那一周中每日【change】的连续相乘
period_stock_data['change'] = stock_data['change'].resample(period_type, how=lambda x: (x+1.0).prod() - 1.0)
# 周线的【open】等于那一周中第一个交易日的【open】
period_stock_data['open'] = stock_data['open'].resample(period_type, how='first')
# 周线的【high】等于那一周中【high】的最大值
period_stock_data['high'] = stock_data['high'].resample(period_type, how='max')
# 周线的【low】等于那一周中【low】的最小值
period_stock_data['low'] = stock_data['low'].resample(period_type, how='min')
# 周线的【volume】和【money】等于那一周中【volume】和【money】各自的和
period_stock_data['volume'] = stock_data['volume'].resample(period_type, how='sum')
period_stock_data['money'] = stock_data['money'].resample(period_type, how='sum')

# 计算周线turnover
period_stock_data['turnover'] = period_stock_data['volume'] / \
                                (period_stock_data['traded_market_value']/period_stock_data['close'])

# 股票在有些周一天都没有交易，将这些周去除
period_stock_data = period_stock_data[period_stock_data['code'].notnull()]
period_stock_data.reset_index(inplace=True)




# ========== 将计算好的周线数据period_stock_data输出到csv文件

# 导出数据 - 注意：这里请填写数据文件在您电脑中的路径
period_stock_data.to_csv('week_stock_data.csv', index=False)

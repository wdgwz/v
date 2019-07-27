# -*- coding: utf-8 -*-
import pandas as pd


# ========== 从原始csv文件中导入股票数据，以浦发银行sh600000为例

# 导入数据 - 注意：这里请填写数据文件在您电脑中的路径
#stock_data = pd.read_csv('sh600001.csv', parse_dates=[1])



#pd.append(pd.stock_data([['2014/12/30',6,6,6,6]],columns=['data','open','high','low','close']))


stock_data = pd.DataFrame({'code': ['600001', '600001', '600001', '600001'],
                    'date': ['2014/12/1', '2014/12/2', '2014/12/3', '2014/12/4'],
                    'open': [5, 6, 7, 8],
                    'high': [6, 7, 8, 9],
                    'low': [4, 5, 6, 7],
                    'close': [5, 6, 7, 8]},
                   
                     index=[0, 1, 2, 3])   


stock_data.append({'code':'600000','data':'2014/12/30','open':6,'high':6,'low':6,'close':6},ignore_index=True)
 
#pd.append(pd.stock_data([['2014/12/30',6,6,6,6]],columns=['data','open','high','low','close']))
 
 
 

# 将数据按照交易日期从远到近排序
stock_data.sort('date', inplace=True)


# ========== 计算移动平均线

# 分别计算5日、20日、60日的移动平均线
ma_list = [5, 20, 60]

# 计算简单算术移动平均线MA - 注意：stock_data['close']为股票每天的收盘价
for ma in ma_list:
    stock_data['MA_' + str(ma)] = pd.rolling_mean(stock_data['close'], ma)

# 计算指数平滑移动平均线EMA
for ma in ma_list:
    stock_data['EMA_' + str(ma)] = pd.ewma(stock_data['close'], span=ma)

# 将数据按照交易日期从近到远排序
stock_data.sort('date', ascending=False, inplace=True)

# ========== 将算好的数据输出到csv文件 - 注意：这里请填写输出文件在您电脑中的路径
stock_data.to_csv('sh600000_ma_ema.csv', index=False)


#第1行数据
print u'数据:%s'%stock_data.iloc[0] 
#第1行开盘价
print u'数据:%s'%stock_data.iloc[0] ['open']
#第2行数据
print u'数据:%s'%stock_data.iloc[1] 
#第2行开盘价
print u'数据:%s'%stock_data.iloc[1] ['open']

if(float(stock_data.iloc[0] ['EMA_5'])>float(stock_data.iloc[0] ['EMA_20'])):
    print u'买'
else:
    print u'卖'
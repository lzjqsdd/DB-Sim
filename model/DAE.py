#node/link process and analysis

import pandas as pd
from pandas import DataFrame,Series
import matplotlib.pyplot as plt


col_single_in = ['frame','pre_num','pre_oflow','pre_v','cur_num','cur_inflow','cur_v']

data_1951 = pd.read_csv("../data/sample/1951_node_sample.txt",delim_whitespace=True,names=col_single_in)
print (data_1951.describe())


## data clean(remove max speed)
data_1951 = data_1951[data_1951.pre_v <= 40]

#plt.plot(data_1951.frame[data_1951.pre_v < 40][1:10000],data_1951.pre_v[data_1951.pre_v < 40][1:10000])
#plt.plot(data_1951.frame[1000:3000], data_1951.pre_v[1000:3000])
#plt.show()

col_1949 = ['frame','cur_num','cur_inflow','cur_v']
data_1949 = pd.read_csv("../data/sample/1949_node_sample.txt",delim_whitespace=True,names=col_1949)
data_1949 = data_1949[data_1949.cur_v < 40]
print (data_1949.describe())

data_1949 = data_1949[data_1949.cur_v < data_1949.cur_v.max()]

#plt.plot(data_1949.cur_v[5000:10000],'g.-',linewidth=1)
#plt.show()

print(data_1949.cur_inflow.mean())

plt.scatter(data_1949.frame ,data_1949.cur_inflow)
plt.show()

from dae import *
from gen_feature import *
import os

origin_data = []
node_list = [1951]
data_path = '../data/Old/one-short-nolight/one-short-500car-nolight/sample/'
load_origin_data(data_path, node_list, origin_data)
train_data = origin_data[0]

train_data = train_data.drop(['1949_poolnum','1949_inflow','1949_outflow','1951_outflow'],axis=1)
train_data['period'] = train_data['frame'] / 10
#analysis_data_heatmap(train_data,'inflow', 5)


analysis_data_boxplot(train_data,'period','inflow')


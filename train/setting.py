# 定义全局变量
# 条件输出

import os
import time

DEBUG = False

#Global config
#demands = ['300']
#demands = ['400']
#demands = ['500','300']
demands = ['750']
#demands = ['1000']
model_root='../model/'

# root path
data_root = '../data/one-long-nolight/'
data_sample_root_list = []
for dmd in demands:
    data_sample_root_list.append(data_root + 'one-long-nolight-' + dmd)

# sample root path
origin_data_path_list = []
for each_sample_root in data_sample_root_list:
    origin_data_path_list.append(os.path.join(each_sample_root,'sample/'));

#model path
cur_date = time.strftime('%Y%m%d',time.localtime(time.time()))

model_version = cur_date + '-' + demands[0]
#model_version = cur_date + '-'
#for i in range(0,len(demands)):
#    if(i == 0):
#        model_version  = model_version + demands[i]
#    else:
#        model_version  = model_version + '_' + demands[i]

xgboost_node_model_path = os.path.join(model_root,'xgboost/'+model_version+'/node/')
xgboost_link_model_path = os.path.join(model_root,'xgboost/'+model_version+'/link/')

#sim path
sim_root = data_sample_root_list[0] + '/sim'

print('model_version', model_version)
print('sim_root', sim_root)

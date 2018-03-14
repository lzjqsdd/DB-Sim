# 定义全局变量
# 条件输出

import os

DEBUG = False

# root path
data_root = '../data/one-long-nolight/'
data_sample_root = '../data/one-long-nolight/one-long-500car-nolight'
data_sample_root_list = [
#        '../data/one-long-nolight/one-long-300car-nolight',
#        '../data/one-long-nolight/one-long-400car-nolight',
         '../data/one-long-nolight/one-long-500car-nolight',
#        '../data/one-long-nolight/one-long-750car-nolight',
#        '../data/one-long-nolight/one-long-1000car-nolight',
#        '../data/one-long-nolight/one-long-1250car-nolight',
#        '../data/one-long-nolight/one-long-1500car-nolight'
        ]

model_root='../model/'
config_root = '../config'
train_root = '../train/'

# data path
origin_data_path = os.path.join(data_sample_root,'sample/')
train_data_path = os.path.join(data_sample_root,'sample/train')
test_data_path = os.path.join(data_sample_root,'sample/test')

# data path list for all condition samples
origin_data_path_list = []
for each_sample_root in data_sample_root_list:
    origin_data_path_list.append(os.path.join(each_sample_root,'sample/'));

# dump path
pkl_path = os.path.join(train_root,'pkl/')
# 是否覆盖序列化数据
override_pkl = True
data_pkl_filename = os.path.join(pkl_path,'data.pkl')

# 是否进行预处理
need_preprocess = True

# config的文件
#config_file = os.path.join(config_root,"750car-nolight.conf")
#pathxml = os.path.join(data_root,"network/path.xml")
#nodexml = os.path.join(data_root,"network/node.xml")

#model path
model_version = '20180312-500'
xgboost_node_model_path = os.path.join(model_root,'xgboost/'+model_version+'/node/')
xgboost_link_model_path = os.path.join(model_root,'xgboost/'+model_version+'/link/')

sim_root = '../data/one-long-nolight/one-long-500car-nolight/sim'
print(sim_root)

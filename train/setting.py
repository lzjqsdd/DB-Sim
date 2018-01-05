# 定义全局变量
# 条件输出

import os

DEBUG = True

# root path
data_root = '../data/one-short-nolight/'
data_sample_root = '../data/one-short-nolight/one-short-500car-nolight'
model_root='../model/'
config_root = '../config'

# data path
origin_data_path = os.path.join(data_sample_root,'sample/')
train_data_path = os.path.join(data_sample_root,'sample/train')
test_data_path = os.path.join(data_sample_root,'sample/test')

# dump path
pkl_path = os.path.join(model_root,'pkl/')
# 是否覆盖序列化数据
override_pkl = True
data_pkl_filename = os.path.join(pkl_path,'data.pkl')

# 是否进行预处理
need_preprocess = True

# config的文件
config_file = os.path.join(config_root,"500car-nolight.conf")
pathxml = os.path.join(data_root,"network/path.xml")
nodexml = os.path.join(data_root,"network/node.xml")

#model path
xgboost_model_path = os.path.join(model_root,'xgboost')
svm_model_path = os.path.join(model_root,'svm')

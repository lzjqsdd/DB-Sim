# 定义全局变量
# 条件输出

import os

DEBUG = True

# root path
data_root = '../data/'
model_root='../model/'

# data path
origin_data_path = os.path.join(data_root,'sample/')
train_data_path = os.path.join(data_root,'sample/train')
test_data_path = os.path.join(data_root,'sample/test')

# dump path
pkl_path = os.path.join(model_root,'pkl/')
# 是否覆盖序列化数据
override_pkl = False
data_pkl_filename = os.path.join(pkl_path,'data.pkl')

# 是否进行预处理
need_preprocess = True

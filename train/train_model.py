# 为不同节点训练使用的模型，参数调节等功能,区别于基本的模型训练功能
# 默认加载所有Node的数据(待优化)
import setting  as st
from xgboost_model import XGBModel
from dae import *
from gen_feature import *
import pandas as pd


def train_for_node1949():
    #step1 load data
    origin_data = []
    #try loading dump data
    df_train_1949_all = pd.DataFrame()

    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [1949,1951,2077,102076], origin_data)
        #pickle.dump(origin_data, open(st.data_pkl_filename,'wb'))

        df_train_1949 = origin_data[0]

        #step2: gen_feature
        df_train_1949 = filter_cut(df_train_1949,3000,13500)
        df_train_1949 = reindex(df_train_1949,1949)
        df_train_1949 = group_frame(df_train_1949)
        df_train_1949 = drop_feature(df_train_1949, node_id = 1949)
        df_train_1949 = gen_label(df_train_1949,node_id = 1949)

        df_train_1949_all = df_train_1949_all.append(df_train_1949)

    #step3: train
    print(df_train_1949_all.columns)
    model_1949 = XGBModel(mid=1949,train_data = df_train_1949_all, test_data=df_train_1949_all)
    param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':8}
    model_1949.train(model_path = st.xgboost_node_model_path, param = param)
    model_1949.loadModel(model_path = st.xgboost_node_model_path)
    model_1949.test()


def train_for_node1951():
    #step1 load data
    origin_data = []
    #try loading dump data
    df_train_1951_all = pd.DataFrame()

    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [1949,1951,2077,102076], origin_data)
        df_train_1951 = origin_data[1]

        #step2: gen_feature
        #df_train_1951 = filter_cut(df_train_1951,2760,13500)
        df_train_1951 = reindex(df_train_1951,1951)
        df_train_1951 = group_frame(df_train_1951)
        df_train_1951 = drop_feature(df_train_1951,node_id = 1951)
        df_train_1951 = gen_label(df_train_1951,node_id = 1951)

        df_train_1951_all = df_train_1951_all.append(df_train_1951)

    #step3: train
    model_1951 = XGBModel(mid=1951,train_data = df_train_1951_all, test_data=df_train_1951_all)
    param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':8}
    model_1951.train(model_path = st.xgboost_node_model_path, param = param)
    model_1951.loadModel(model_path = st.xgboost_node_model_path)
    model_1951.test()



def train_for_node2077():
    #step1 load data
    origin_data = []
    #try loading dump data
    df_train_2077_all = pd.DataFrame()

    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [1949,1951,2077,102076], origin_data)
        df_train_2077 = origin_data[2]

        #step2: gen_feature
        #df_train_2077= filter_cut(df_train_2077,2760,13500)
        df_train_2077 = reindex(df_train_2077,2077)
        df_train_2077 = group_frame(df_train_2077)
        df_train_2077 = drop_feature(df_train_2077, node_id = 2077)
        df_train_2077 = gen_label(df_train_2077,node_id = 2077)

        df_train_2077_all = df_train_2077_all.append(df_train_2077)

    #step3: train
    param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':8}
    model_2077 = XGBModel(mid=2077,train_data = df_train_2077_all, test_data=df_train_2077_all)
    model_2077.train(model_path = st.xgboost_node_model_path, param = param)
    model_2077.loadModel(model_path = st.xgboost_node_model_path)
    model_2077.test()



def train_for_node102076():
    #step1 load data
    origin_data = []
    #try loading dump data
    df_train_102076_all = pd.DataFrame()

    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [1949,1951,2077,102076], origin_data)
        df_train_102076= origin_data[3]

        #step2: gen_feature
        #df_train_102076 = filter_cut(df_train_102076,2760,13500)
        df_train_102076= reindex(df_train_102076, 102076)
        df_train_102076 = group_frame(df_train_102076)
        df_train_102076 = drop_feature(df_train_102076, node_id = 102076) #剔除某些特征
        df_train_102076 = gen_label(df_train_102076,node_id=102076)

        df_train_102076_all = df_train_102076_all.append(df_train_102076)

    #step3: train
    param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':6}
    model_102076 = XGBModel(mid=102076,train_data = df_train_102076_all, test_data=df_train_102076_all)
    model_102076.train(model_path = st.xgboost_node_model_path, param = param)
    model_102076.loadModel(model_path = st.xgboost_node_model_path)
    model_102076.test()



def train_for_link1949():
    #step1 load data
    origin_data = []
    #try loading dump data

    df_train_1949_all = pd.DataFrame()

    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [1949,1951,2077,102076], origin_data)
        df_train_1949 = origin_data[0]

        #step2: gen_feature
        #df_train_1949 = filter_cut(df_train_1949,2760,13500)
        df_train_1949 = reindex(df_train_1949,1949)
        df_train_1949 = group_frame(df_train_1949)
        df_train_1949 = gen_pool2buffer(df_train_1949,1949)
        df_train_1949 = drop_feature(df_train_1949, link_id = 1949)
        df_train_1949 = gen_label(df_train_1949, link_id = 1949)

        df_train_1949_all = df_train_1949_all.append(df_train_1949)

    print("max label : ",df_train_1949_all.label.max())

    #step3: train
    model_1949 = XGBModel(mid=1949,train_data = df_train_1949_all, test_data=df_train_1949_all)
    param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':7}
    model_1949.train(model_path = st.xgboost_link_model_path, param = param)
    model_1949.loadModel(model_path = st.xgboost_link_model_path)
    model_1949.test()

def train_for_link1951():
    #step1 load data
    origin_data = []
    #try loading dump data
    df_train_1951_all = pd.DataFrame()

    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [1949,1951,2077,102076], origin_data)
        df_train_1951 = origin_data[1]

        #step2: gen_feature
        #df_train_1951 = filter_cut(df_train_1951,2760,13500)
        df_train_1951 = reindex(df_train_1951,1951)
        df_train_1951 = group_frame(df_train_1951)
        df_train_1951 = gen_pool2buffer(df_train_1951, 1951)
        df_train_1951 = drop_feature(df_train_1951, link_id = 1951)
        df_train_1951 = gen_label(df_train_1951,link_id = 1951)

        df_train_1951_all = df_train_1951_all.append(df_train_1951)

    print("max label : ", df_train_1951_all.label.max())

    #step3: train
    model_1951 = XGBModel(mid=1951,train_data = df_train_1951_all, test_data=df_train_1951_all)
    param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':6}
    model_1951.train(model_path = st.xgboost_link_model_path, param = param)
    model_1951.loadModel(model_path = st.xgboost_link_model_path)
    model_1951.test()



def train_for_link2077():
    #step1 load data
    origin_data = []
    #try loading dump data
    df_train_2077_all = pd.DataFrame()

    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [1949,1951,2077,102076], origin_data)
        df_train_2077 = origin_data[2]

        #step2: gen_feature
        #df_train_2077= filter_cut(df_train_2077,2760,13500)
        df_train_2077 = reindex(df_train_2077,2077)
        df_train_2077 = group_frame(df_train_2077)
        df_train_2077 = gen_pool2buffer(df_train_2077, 2077)
        df_train_2077 = drop_feature(df_train_2077, link_id = 2077)
        df_train_2077 = gen_label(df_train_2077,link_id = 2077)

        df_train_2077_all = df_train_2077_all.append(df_train_2077)

    print("max label : ", df_train_2077.label.max())
    #step3: train
    param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':6}
    model_2077 = XGBModel(mid=2077,train_data = df_train_2077_all, test_data=df_train_2077_all)
    model_2077.train(model_path = st.xgboost_link_model_path, param = param)
    model_2077.loadModel(model_path = st.xgboost_link_model_path)
    model_2077.test()

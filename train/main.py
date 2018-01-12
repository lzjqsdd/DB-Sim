from network import *
import setting  as st
from xgboost_model import XGBModel
from dae import *
from gen_feature import *
import pandas as pd

if __name__ == '__main__':
    #step1 load data
    origin_data = []
    #try loading dump data
    if(os.path.exists(st.data_pkl_filename) and not(st.override_pkl)):
        origin_data = pickle.load(open(st.data_pkl_filename,'rb'))
    else:
        load_origin_data(st.origin_data_path, [1949,1951,2077], origin_data)
        pickle.dump(origin_data, open(st.data_pkl_filename,'wb'))
    df_train_1949 = origin_data[0]

    #step2: gen_feature
    df_train_1949 = filter_cut(df_train_1949,2760,13500)
    df_train_1949 = reindex(df_train_1949,1949)
    df_train_1949 = group_frame(df_train_1949)

    #step3: train
    model_1949 = XGBModel(node_id=1949,train_data = df_train_1949, test_data=df_train_1949)
    #param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'reg:linear'}
    model_1949.train(model_path = st.xgboost_model_path)
    #model_1949.train4period(model_path = st.xgboost_model_path, period = 6, param = param)

    #model_1949.loadModel4Period(model_path = st.xgboost_model_path, period = 6)
    model_1949.loadModel(model_path = st.xgboost_model_path)
    model_1949.test()



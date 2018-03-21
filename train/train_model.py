#                            _ooOoo_
#                           o8888888o
#                           88" . "88
#                           (| -_- |)
#                            O\ = /O
#                        ____/`---'\____
#                      .   ' \\| |// `.
#                       / \\||| : |||// \
#                     / _||||| -:- |||||- \
#                       | | \\\ - /// | |
#                     | \_| ''\---/'' | |
#                      \ .-\__ `-` ___/-. /
#                   ___`. .' /--.--\ `. . __
#                ."" '< `.___\_<|>_/___.' >'"".
#               | | : `- \`.;`\ _ /`;.`/ - ` : | |
#                 \ \ `-. \_ __\ /__ _/ .-` / /
#         ======`-.____`-.___\_____/___.-`____.-'======
#                            `=---='
#
#         .............................................
#                  佛祖镇楼                  BUG辟易
#          佛曰:
#                  写字楼里写字间，写字间里程序员；
#                  程序人员写程序，又拿程序换酒钱。
#                  酒醒只在网上坐，酒醉还来网下眠；
#                  酒醉酒醒日复日，网上网下年复年。
#                  但愿老死电脑间，不愿鞠躬老板前；
#                  奔驰宝马贵者趣，公交自行程序员。
#                  别人笑我忒疯癫，我笑自己命太贱；
#                  不见满街漂亮妹，哪个归得程序员？

# 为不同节点训练使用的模型，参数调节等功能,区别于基本的模型训练功能
# 默认加载所有Node的数据(待优化)
import setting  as st
from xgboost_model import XGBModel
from dae import *
from gen_feature import *
import pandas as pd
from sklearn.utils import shuffle


#训练初始节点,每个node的类别多少不同,所有参数从外部传入
def train_for_node(node_id , nodetype, train_size, param):
    #step1 load data
    origin_data = []
    df_train_all = pd.DataFrame()
    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [node_id], origin_data)

        df_train = origin_data[0]
        if nodetype != 2:
            print('node ' , node_id , ' maxpool is :' , df_train.cur_poolnum.max(), ' max buffernum is : ' ,df_train.cur_buffernum.max())

        #step2: gen_feature
        #df_train = filter_cut(df_train , 3000 , 13500)
        df_train = reindex(df = df_train,nodetype = nodetype)
        df_train = group_frame(df = df_train)
        df_train = drop_feature_for_node(df = df_train, nodetype = nodetype)
        df_train = gen_label_for_node(df = df_train , nodetype = nodetype)

        df_train_all = df_train_all.append(df_train)

    df_train_all = shuffle(df_train_all)
    print("max label : ",df_train_all.label.max())
    split_index = int(df_train_all.shape[0] * train_size)
    train_data = df_train_all[:split_index]
    test_data = df_train_all[split_index:]

    #step3: train
    model = XGBModel(mid = node_id ,train_data = train_data, test_data=test_data)
    model.train(model_path = st.xgboost_node_model_path, param = param)
    model.loadModel(model_path = st.xgboost_node_model_path)
    model.test()


def train_for_pool2buffer(link_id, linktype, train_size, param):
    #step1 load data
    origin_data = []
    df_train_all = pd.DataFrame()
    for data_filename in st.origin_data_path_list:
        load_origin_data(data_filename, [link_id], origin_data)
        df_train = origin_data[0]
        if linktype!= 2:
            print('link ', link_id , ' maxpool is :' , df_train.cur_poolnum.max(), ' max buffernum is : ' ,df_train.cur_buffernum.max())

        #step2: gen_feature
        df_train = reindex(df = df_train, nodetype = linktype)
        df_train = gen_pool2buffer(df = df_train)
        df_train = filter_cut(df_train, 1800, df_train.frame.max())
        df_train = group_frame(df = df_train)
        df_train = drop_feature_for_pool2buffer(df_train, linktype = linktype)
        df_train = gen_label_for_pool2buffer(df_train)

        df_train_all = df_train_all.append(df_train)

    df_train_all = shuffle(df_train_all)
    print("max label : ",df_train_all.label.max())
    split_index = int(df_train_all.shape[0] * train_size)
    train_data = df_train_all[:split_index]
    test_data = df_train_all[split_index:]

    #step3: train
    model = XGBModel(mid = link_id, train_data = train_data, test_data= test_data)
    model.train(model_path = st.xgboost_link_model_path, param = param)
    model.loadModel(model_path = st.xgboost_link_model_path)
    model.test()

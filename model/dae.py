#node/link process and analysis
# -*- coding:utf-8 -*-

import os

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pickle
from scipy.stats import norm
from sklearn.preprocessing import StandardScaler
from scipy import stats
import warnings
warnings.filterwarnings('ignore')

import setting as st


#根据node列表加载原始数据
def load_origin_data(data_path, node_list, origin_data):
    if len(node_list) == 0:
        return

    for node_id in node_list:
        node_sample_path = os.path.join(data_path,str(node_id)+"_node_sample.txt")
        if st.DEBUG:
            print("load node:",node_id,"in path",node_sample_path)
        data = pd.read_csv(node_sample_path,delim_whitespace=True)
        origin_data.append(data)
        if st.DEBUG:
            print(data.describe())

#数据清洗
def clean_data(origin_data):
    #remove NA
    for data in origin_data:
        if st.DEBUG:
            print("clean node...");
        data.dropna()

    #remove outlier

    #shuffule


# 分析目标变量的分布
def analysis_y(df_train, y_name):
    sns.distplot(df_train[y_name])
    print("Skewness: %f" % df_train.SalePrice.skew())
    print("Kurtosis: %f" % df_train.SalePrice.kurt())
    plot.show()

#分析离散变量采用箱形图
def analysis_data_boxplot(df_train, feature_name, y_name):
    # boxplot
    data = pd.concat([df_train[y_name],df_train[feature_name]],axis=1)
    f, ax = plt.subplots(figsize=(16,8))
    fig = sns.boxplot(x=feature_name,y=y_name,data = data)
    fig.axis(ymin=0, ymax=df_train[y_name].max() + 10)
    plt.show()

# 分析连续变量的分布采用散点图
def analysis_data_scatter(df_train, feature_name, y_name, jitter_factor):
    data = pd.concat([jitter(df_train[y_name],jitter_factor),jitter(df_train[feature_name],jitter_factor)],axis=1)
    data.plot.scatter(x = feature_name,y=y_name, ylim=(0,df_train[y_name].max()), marker='x')
    plt.show()

#输出各个量之间的相关性
def analysis_data_heatmap(df_train, feature_name, y_name, klargest):
    corrmat = df_train.corr()
    f,ax = plt.subplots(figsize=(12,9))
    sns.heatmap(corrmat, vmax=.8, square=True)

    cols = corrmat.nlargest(klargest, y_name)[y_name].index
    cm = np.corrcoef(df_train[cols].values.T) #计算的是行与行之间的相关性系数
    sns.set(font_scale=1.25)
    hm = sns.heatmap(cm, cbar=True, annot=True, square=True, fmt='.2f',annot_kws={'size':10}, yticklabels=cols.values, xticklabels=cols.values)

    plt.show()

def jitter(series, factor):
    z = float(series.max()) - float(series.min())
    a = float(factor) * z /50.0
    return series.apply(lambda x: x+np.random.uniform(-a,a))

#训练
def train(train_data):
    # random forest
    # or GBDT
    pass

#calc score
def score(classfier, train_data, test_data):
    pass
from dae import *
from gen_feature import *
import os
import pandas as pd
import numpy as np

#本文件主要用来做一些数据分析

#1949,1951,2073,2017,2062,2075,2066,2068,2562,2571,2581,2584,2621,2637

#print(df_dbsim['300'].loc[1949])
#print(df_npess.loc[1949])

def compare_len():
    df_npess = pd.read_csv('npess.csv', header=0, index_col=0)
    df_dbsim = pd.read_csv('dbsim.csv', header=0, index_col=0)
    carnum = ['300','400','500','750','1000']
    links = [1949,1951,2073,2075,2066,2068,2062,2017,2562,2621,2584,2581,2571,2637]
    links_len = [1450,1360,974,34,31,12,3129,1630,836,707,1528,4402,3232,844]
    zh = []
    sum_zh = 0
    for length in links_len:
        sum_zh = sum_zh + length
        zh.append(sum_zh)
    for cn in carnum:
        npess_y = []
        dbsim_y = []
        for xi in links:
            npess_y.append(df_npess[cn].loc[xi])
            dbsim_y.append(df_dbsim[cn].loc[xi])
        err = abs(np.array(npess_y) - np.array(dbsim_y))
        plt.plot(npess_y,marker='o',label='npess_'+cn)
        plt.plot(dbsim_y,marker='^',label='dbsim_'+cn)
        plt.plot(err,marker='*',label='abs_err_'+cn)

        plt.xlabel('Link Order')
        plt.ylabel('Finished frame')
        plt.ylim(0,30000)
        plt.legend(loc = 'upper left')
        plt.savefig(fname = os.path.join('carnum', str(cn) + '.png'), format = 'png',dpi = 600)
        plt.clf();

def compare_carnum():
    df_npess = pd.read_csv('npess.csv', header=0, index_col=0)
    df_dbsim = pd.read_csv('dbsim.csv', header=0, index_col=0)
    carnum = ['300','400','500','750','1000']
    xxx = [300,400,500,750,1000]
    #links = [1949,1951,2073,2075,2066,2068,2062]
    links = [2017,2562,2621,2584,2581,2571,2637]
    links_len = [1450,1360,974,34,31,12,3129,1630,836,707,1528,4402,3232,844]
    zh = []
    sum_zh = 0
    for length in links_len:
        sum_zh = sum_zh + length
        zh.append(sum_zh)
    print(sum_zh)

    for xi in links:
        npess_y = []
        dbsim_y = []
        for cn in carnum:
            npess_y.append(df_npess[cn].loc[xi])
            dbsim_y.append(df_dbsim[cn].loc[xi])

        err = abs(np.array(npess_y) - np.array(dbsim_y))
        plt.plot(xxx,npess_y,marker='o',ls = '-.',  label='npess_'+str(xi))
        plt.plot(xxx,dbsim_y,marker='^',label='dbsim_'+str(xi))

    plt.xlabel('Carnum')
    plt.ylabel('Finished Frame')
    plt.ylim(18000,30000)
    plt.legend(loc = 'upper left',fontsize='xx-small')
    plt.savefig(fname = os.path.join('links', str('l2') + '.png'), format = 'png',dpi = 600)
    plt.clf();

compare_len()
#compare_carnum()

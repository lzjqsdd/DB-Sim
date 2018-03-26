from dae import *
from gen_feature import *
import os

#本文件主要用来做一些数据分析

#1949,1951,2073,2017,2062,2075,2066,2068,2562,2571,2581,2584,2621,2637

def compare_totalnum(link_id):
    #原始数据
    origin_data = [] #data through pipeline,contains all node data
    load_origin_data(st.origin_data_path_list[0], [link_id], origin_data)
    df_train = origin_data[0]
    df_train['totalnum'] = df_train['cur_poolnum'] + df_train['cur_buffernum']
    #dbsim数据
    df_sim = pd.read_csv(os.path.join(st.sim_root,str(link_id)))
    #残差
    len1 = df_train.shape[0]
    len2 = df_sim.shape[0]
    length = min(len1,len2)
    abs_err = abs(df_train['totalnum'][:length] - df_sim['totalnum'][:length])
    #abs_err = df_train['totalnum'][:length] - df_sim['totalnum'][:length]

    ###########################################

    plt.plot(df_train['frame'], df_train['totalnum'],lw = 0.8, label=str(link_id) + '_origin')
    plt.plot(df_sim['frame'],df_sim['totalnum'],lw = 0.8, label=str(link_id) + '_dbsim')
    plt.plot(df_sim['frame'][:length], abs_err, lw = 0.5, label=str(link_id)+ '_abs_error')
    plt.legend(loc = 'upper right')
    plt.legend(loc = 'best')
    plt.xlabel('frame')
    plt.ylabel('totalnum')
    #plt.show()
    '''
    savefig(fname, dpi=None, facecolor='w', edgecolor='w',
        orientation='portrait', papertype=None, format=None,
        transparent=False, bbox_inches=None, pad_inches=0.1,
        frameon=None)
    '''
    plt.savefig(fname = os.path.join(st.demands[0], str(link_id) + '.eps'), format = 'eps',dpi = 500)
    plt.clf()


    #plt.scatter(df_train['frame'], df_train['cur_poolnum'] + df_train['cur_buffernum'])
    #plt.scatter(df_sim['frame'],df_sim['totalnum'] - 3)
    #plt.scatter(df_sim['frame'][:length], abs_err)

def compare_inflow(link_id):
    #原始数据
    origin_data = [] #data through pipeline,contains all node data
    load_origin_data(st.origin_data_path_list[0], [link_id], origin_data)
    df_train = origin_data[0]
    df_sim = pd.read_csv(os.path.join(st.sim_root,str(link_id)))

    #plt.plot(df_train['frame'], df_train['cur_inflow'],lw = 0.8, label='origin')
    #plt.plot(df_sim['frame'],df_sim['inflow'],lw = 0.8, label='dbsim')

    len1 = df_train.shape[0]
    len2 = df_sim.shape[0]
    length = min(len1,len2)
    abs_err = df_train['cur_inflow'][:length] - df_sim['inflow'][:length]
    plt.plot(df_sim['frame'][:length],abs_err,lw = 0.8, label = str(link_id) + '_error')
    plt.ylim(-2,20)
    plt.xlabel('frame')
    plt.ylabel('inflow')
    plt.legend(loc = 'upper right')
    plt.savefig(fname = os.path.join(st.demands[0], str(link_id)), format = 'svg')
    plt.clf()

def compare_poolnum(link_id):
    #原始数据
    origin_data = [] #data through pipeline,contains all node data
    load_origin_data(st.origin_data_path_list[0], [link_id], origin_data)
    df_train = origin_data[0]
    #dbsim数据
    df_sim = pd.read_csv(os.path.join(st.sim_root,str(link_id)))
    #残差
    len1 = df_train.shape[0]
    len2 = df_sim.shape[0]
    length = min(len1,len2)
    abs_err = abs(df_train['cur_poolnum'][:length] - df_sim['poolnum'][:length])


    plt.plot(df_train['frame'], df_train['cur_poolnum'],lw = 0.8, label=str(link_id)+'_origin_poolnum')
    plt.plot(df_sim['frame'],df_sim['poolnum'],lw = 0.8, label=str(link_id)+'_dbsim_poolnum')
    plt.legend(loc = 'upper right')
    plt.xlabel('frame')
    plt.ylabel('poolnum')
    plt.savefig(fname = os.path.join(st.demands[0], str(link_id)), format = 'svg')
    plt.clf()


def compare_buffernum(link_id):
    #原始数据
    origin_data = [] #data through pipeline,contains all node data
    load_origin_data(st.origin_data_path_list[0], [link_id], origin_data)
    df_train = origin_data[0]
    #dbsim数据
    df_sim = pd.read_csv(os.path.join(st.sim_root,str(link_id)))
    #残差
    len1 = df_train.shape[0]
    len2 = df_sim.shape[0]
    length = min(len1,len2)
    abs_err = abs(df_train['cur_buffernum'][:length] - df_sim['buffernum'][:length])


    plt.plot(df_train['frame'], df_train['cur_buffernum'],lw = 0.8, label=str(link_id) + 'origin_buffernum')
    plt.plot(df_sim['frame'],df_sim['buffernum'],lw = 0.8, label=str(link_id) + 'dbsim_buffernum')
    plt.legend(loc = 'upper right')
    plt.xlabel('frame')
    plt.ylabel('buffernum')
    plt.savefig(fname = os.path.join(st.demands[0], str(link_id)), format = 'svg')
    plt.clf()

link_list = [1949,1951,2073,2017,2062,2075,2066,2068,2562,2571,2581,2584,2621,2637]

for link_id in link_list:
    compare_totalnum(link_id)
    #compare_poolnum(link_id)
    #compare_buffernum(link_id)
    #compare_inflow(link_id)

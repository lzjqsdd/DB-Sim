from dae import *
from gen_feature import *

#本文件主要用来做一些数据分析

origin_data = [] #data through pipeline,contains all node data

# try loading dump data
if(os.path.exists(st.data_pkl_filename) and not(st.override_pkl)):
    origin_data = pickle.load(open(st.data_pkl_filename,'rb'))

else:
    load_origin_data(st.origin_data_path, [1949,1951,2077,102076], origin_data)
    pickle.dump(origin_data, open(st.data_pkl_filename,'wb'))


#df_train_1949 = origin_data[0]
##df_train_1949 = filter_cut(df_train_1949,2760,13500)
#df_train_1949 = reindex(df_train_1949, 1949)
#df_train_1949 = group_frame(df_train_1949)
#df_train_1949 = gen_pool2buffer(df_train_1949, 1949)
#analysis_data_boxplot(df_train_1949, '1949_poolnum','pool2buffer')
#analysis_data_heatmap(df_train_1949,'pool2buffer',10)


#df_train_1951 = origin_data[1]
#plt.plot(df_train_1951['frame'], df_train_1951['1951_poolnum'] + df_train_1951['1951_buffernum'])

#df_sim = pd.read_csv(st.sim_root+'/db1000/1951')
#plt.plot(df_sim['frame'],df_sim['totalnum'])
#plt.show()

df_train_1949 = origin_data[0]
plt.plot(df_train_1949['frame'], df_train_1949['1949_poolnum'] + df_train_1949['1949_buffernum'])

df_sim = pd.read_csv(st.sim_root+'/db1000/1949')
plt.plot(df_sim['frame'],df_sim['totalnum'])
plt.show()


#df_train_1951 = filter_cut(df_train_1951,2760,13500)
#df_train_1951 = reindex(df_train_1951, 1951)
#df_train_1951 = group_frame(df_train_1951)
#df_train_1951 = gen_pool2buffer(df_train_1951, 1951)
#analysis_data_boxplot(df_train_1951, '1951_poolnum','pool2buffer')
#analysis_data_heatmap(df_train_1951,'pool2buffer',10)

#df_train_102076 = origin_data[3]
#df_train_102076 = filter_cut(df_train_102076,2760,13500)
#df_train_102076 = reindex(df_train_102076, 102076)
#df_train_102076 = group_frame(df_train_102076)
#df_train_102076 = gen_label(df_train_102076,node_id=102076)
#analysis_data_boxplot(df_train_102076, '2077_inflow','label') #只要Period和buffer_num的特征作为输入



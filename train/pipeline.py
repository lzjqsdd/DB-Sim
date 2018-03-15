from dae import *
from gen_feature import *

#本文件主要用来做一些数据分析

#1949,1951,2017,2062,2066,2068,2073,2075,2562,2571,2581,2584,2621,2637
link_id = 2068

origin_data = [] #data through pipeline,contains all node data
load_origin_data(st.origin_data_path, [link_id], origin_data)
pickle.dump(origin_data, open(st.data_pkl_filename,'wb'))
df_train = origin_data[0]
#plt.plot(df_train['frame'], df_train['cur_poolnum'] + df_train['cur_buffernum'])
plt.scatter(df_train['frame'], df_train['cur_poolnum'] + df_train['cur_buffernum'])

df_sim = pd.read_csv(os.path.join(st.sim_root,'link'+str(link_id)))
#plt.plot(df_sim['frame'],df_sim['totalnum'])
plt.scatter(df_sim['frame'],df_sim['totalnum'] - 3)
plt.show()


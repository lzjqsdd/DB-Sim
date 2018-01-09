from dae import *




####################################################################

## pipeline
#col = ['frame','pre_poolnum','pre_oflow','pre_v','cur_num','cur_inflow','cur_v']
origin_data = [] #data through pipeline,contains all node data

# try loading dump data
if(os.path.exists(st.data_pkl_filename) and not(st.override_pkl)):
    origin_data = pickle.load(open(st.data_pkl_filename,'rb'))

else:

    # step1 load data
    load_origin_data(st.origin_data_path, [1949,1951,2077], origin_data)

    # step2 clean data
    # clean_data(origin_data)

    # dump data
    pickle.dump(origin_data, open(st.data_pkl_filename,'wb'))


df_train = origin_data[0]

# 错位分析
#frame = df_train['frame'].values[:-1]
#num = df_train['1949_poolnum'].values[:-1] + df_train['1949_buffernum'].values[:-1]
#inflow = df_train['1949_inflow'].values[1:]
#di = {'frame':frame, 'num':num, 'inflow':inflow}

# 构造frame%60特征

df_train = df_train[(df_train.frame >= 2760) & (df_train.frame <= 13500)]

#analysis_data_heatmap(df_train_frame_8, '1949_outflow',10)

#x = np.arange(10)
#y = []
#for i in x:
#    y.append(df_train[df_train.frame2 == i]['1949_outflow'].mean())
#plt.plot(x,y)
#plt.show()

analysis_data_boxplot(df_train, 'frame2', '1949_outflow')

# step3 train data

# step4 test data

##################################################################
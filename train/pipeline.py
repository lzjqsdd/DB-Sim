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

print('----------------------')
#print(df_train['1949_inflow'].sum())

frame = df_train['frame'].values[:-1]
num = df_train['1949_poolnum'].values[:-1] + df_train['1949_buffernum'].values[:-1]
inflow = df_train['1949_inflow'].values[1:]

di = {'frame':frame, 'num':num, 'inflow':inflow}

df_train2 = pd.DataFrame(data = di);
df_train2.describe();

#df_train = origin_data[1]
#df_train['1951_poolandbuffer'] = df_train['1951_poolnum'] + df_train['1951_buffernum']
#df_train = df_train.drop(['1949_inflow','1949_outflow','1949_speed','1951_speed'],axis=1)
#analysis_data_heatmap(df_train, "1951_inflow", 5)

#analysis_data_boxplot(df_train, "1949_buffernum", "1951_inflow")


#df_train2 = pd.DataFrame()
#df_train2['1949_buffernum'] = df_train['1949_buffernum'][:-1]
#df_train2['1951_inflow'] = df_train['1951_inflow'][1:]
#analysis_data_scatter(df_train2,'1949_buffernum','1951_inflow',0)




# step3 train data

# step4 test data

##################################################################

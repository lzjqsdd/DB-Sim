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
    #load_origin_data(st.origin_data_path, [1949,1951,2073,2075,2066,2068,2062], origin_data)
    load_origin_data(st.origin_data_path, [1949], origin_data)
    # step2 clean data
    # clean_data(origin_data)
    # dump data
    pickle.dump(origin_data, open(st.data_pkl_filename,'wb'))

df_train = origin_data[0]
#df_train['1949_poolnum'].plot()
#plt.show()
df_train['frame'] = df_train['frame'] % 600
#analysis_data_scatter(df_train, "frame", "1949_outflow",0)
#analysis_data_boxplot(df_train, "frame", "2075_outflow")
df_train.dropna()
analysis_data_heatmap(df_train, "frame", "1949_outflow",10)
    # step3 train data

    # step4 test data

##################################################################

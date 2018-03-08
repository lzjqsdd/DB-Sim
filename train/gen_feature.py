## 处理feature的过程

import pandas as pd
import numpy as np
import setting as st


#截取一定范围内的数据
def filter_cut(df, start, end):
    df = df[(df.frame >= start) & (df.frame <= end)]
    return df

#错位构造,这里根据不同的nodeid进行处理,暂时不考虑泛化的处理方式
#type : 0(origin), 1(mid), 2(end)
def reindex(df, nodetype = 1):
    if(nodetype == 0):
        frame = df['frame'].values[:-1]
        cur_poolnum = df['cur_poolnum'].values[:-1]
        cur_buffernum = df['cur_buffernum'].values[:-1]
        cur_inflow = df['cur_inflow'].values[1:]
        cur_outflow = df['cur_outflow'].values[1:]

        data = {
                'frame':frame,
                'cur_poolnum':cur_poolnum,
                'cur_buffernum':cur_buffernum,
                'cur_inflow':cur_inflow,
                'cur_outflow':cur_outflow
        }

        new_df = pd.DataFrame(data=data)
        return new_df
    elif(nodetype == 1):
        frame = df['frame'].values[:-1]

        pre_poolnum = df['pre_poolnum'].values[:-1]
        pre_buffernum = df['pre_buffernum'].values[:-1]
        pre_inflow = df['pre_inflow'].values[1:]

        cur_poolnum = df['cur_poolnum'].values[:-1]
        cur_buffernum = df['cur_buffernum'].values[:-1]
        cur_inflow =  df['cur_inflow'].values[1:]
        cur_outflow = df['cur_outflow'].values[1:]

        data = {
            'frame':frame,
            'pre_poolnum': pre_poolnum,
            'pre_buffernum':pre_buffernum,
            'pre_inflow': pre_inflow,
            'cur_poolnum': cur_poolnum,
            'cur_buffernum': cur_buffernum,
            'cur_inflow': cur_inflow,
            'cur_outflow': cur_outflow
        }

        new_df = pd.DataFrame(data = data)
        return new_df
    elif(nodetype == 2):
        frame = df['frame'].values[:-1]

        pre_poolnum = df['pre_poolnum'].values[:-1]
        pre_buffernum = df['pre_buffernum'].values[:-1]
        pre_inflow =  df['pre_inflow'].values[1:]
        pre_outflow = df['pre_outflow'].values[1:]

        data = {
            'frame': frame,
            'pre_poolnum': pre_poolnum,
            'pre_buffernum': pre_buffernum,
            'pre_inflow': pre_inflow,
            'pre_outflow': pre_outflow
        }
        new_df = pd.DataFrame(data = data)
        return new_df


#根据frame分组
def group_frame(df, period_dur = 600 , timestep = 60):

    df['period'] = (df['frame'] % period_dur / timestep).astype('int32')
    df = df.drop(['frame'],axis=1)
    #df.groupby(['period'])
    #df.get_group(1)
    return df

#增加pool->buffer的流量特征
def gen_pool2buffer(df):
    pool_before = df['cur_poolnum'].values + df['cur_inflow'].values
    pool_after = df['cur_poolnum'][1:].append( pd.Series([0]) ).values #追加一行0，不然没法求最后一个的数据
    df['pool2buffer'] = pool_before - pool_after
    return df

def gen_label_for_node(df, nodetype = 1):
    if nodetype == 0 or nodetype == 1:
        df = df.rename(columns={"cur_inflow":"label"})
    elif nodetype == 2:
        df = df.rename(columns={"pre_outflow":"label"})
    return df

def gen_label_for_pool2buffer(df):
    df = df.rename(columns={"pool2buffer":"label"})
    return df


#丢弃一些无关特征
def drop_feature_for_node(df, nodetype):
    if nodetype == 0:
        df = df.drop(['cur_buffernum','cur_outflow'], axis = 1)
    elif nodetype == 1:
        df = df.drop(['pre_inflow','pre_poolnum','cur_outflow','cur_buffernum'], axis = 1)
    elif nodetype == 2:
        df = df.drop(['pre_inflow','pre_poolnum'], axis = 1)
    return df



def drop_feature_for_pool2buffer(df, linktype):
    if linktype == 0:
        df = df.drop(['cur_inflow','cur_outflow'], axis = 1)
    elif linktype == 1:
        df = df.drop(['pre_inflow','pre_buffernum','pre_poolnum','cur_inflow','cur_outflow'], axis = 1)
    return df

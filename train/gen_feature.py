## 处理feature的过程

import pandas as pd
import numpy as np
import setting as st


#截取一定范围内的数据
def filter_cut(df, start, end):

    df = df[(df.frame >= start) & (df.frame <= end)]
    return df

#错位构造,这里根据不同的nodeid进行处理,暂时不考虑泛化的处理方式
def reindex(df,node_id):
    if(node_id == 1949):

        frame = df['frame'].values[:-1]
        poolnum_1949 = df['1949_poolnum'].values[:-1]
        buffernum_1949 = df['1949_buffernum'].values[:-1]
        inflow_1949 = df['1949_inflow'].values[1:]
        outflow_1949 = df['1949_outflow'].values[1:]

        data = {
                'frame':frame,
                '1949_poolnum':poolnum_1949,
                '1949_buffernum':buffernum_1949,
                '1949_inflow':inflow_1949,
                '1949_outflow':outflow_1949
        }

        new_df = pd.DataFrame(data=data)
        return new_df


    elif(node_id == 1951):

        frame = df['frame'].values[:-1]

        poolnum_1949 = df['1949_poolnum'].values[:-1]
        buffernum_1949 = df['1949_buffernum'].values[:-1]
        inflow_1949 = df['1949_inflow'].values[1:]

        poolnum_1951 = df['1951_poolnum'].values[:-1]
        buffernum_1951 = df['1951_buffernum'].values[:-1]
        inflow_1951 =  df['1951_inflow'].values[1:]
        outflow_1951 = df['1951_outflow'].values[1:]

        data = {
            'frame':frame,
            '1949_poolnum': poolnum_1949,
            '1949_buffernum':buffernum_1949,
            '1949_inflow': inflow_1949,
            '1951_poolnum': poolnum_1951,
            '1951_buffernum': buffernum_1951,
            '1951_inflow': inflow_1951,
            '1951_outflow': outflow_1951
        }

        new_df = pd.DataFrame(data = data)
        return new_df


    elif(node_id == 2077):

        frame = df['frame'].values[:-1]

        poolnum_1951 = df['1951_poolnum'].values[:-1]
        buffernum_1951 = df['1951_buffernum'].values[:-1]
        inflow_1951 = df['1951_inflow'].values[1:]

        poolnum_2077 = df['2077_poolnum'].values[:-1]
        buffernum_2077 = df['2077_buffernum'].values[:-1]
        inflow_2077 =  df['2077_inflow'].values[1:]
        outflow_2077 = df['2077_outflow'].values[1:]

        data = {
            'frame':frame,
            '1951_poolnum': poolnum_1951,
            '1951_buffernum': buffernum_1951,
            '1951_inflow': inflow_1951,
            '2077_poolnum': poolnum_2077,
            '2077_buffernum':buffernum_2077,
            '2077_inflow': inflow_2077,
            '2077_outflow': outflow_2077
        }

        new_df = pd.DataFrame(data = data)
        return new_df

    else:
        frame = df['frame'].values[:-1]

        poolnum_2077 = df['2077_poolnum'].values[:-1]
        buffernum_2077 = df['2077_buffernum'].values[:-1]
        inflow_2077 =  df['2077_inflow'].values[1:]
        outflow_2077 = df['2077_outflow'].values[1:]

        data = {
            'frame': frame,
            '2077_poolnum': poolnum_2077,
            '2077_buffernum': buffernum_2077,
            '2077_inflow': inflow_2077,
            '2077_outflow': outflow_2077
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
def gen_pool2buffer(df, node_id):
    if node_id == 1949:
        pool_before = df['1949_poolnum'].values + df['1949_inflow'].values
        pool_after = df['1949_poolnum'][1:].append( pd.Series([0]) ).values #追加一行0，不然没法求最后一个的数据
        df['pool2buffer'] = pool_before - pool_after
        return df
    elif node_id == 1951:
        pool_before = df['1951_poolnum'].values + df['1951_inflow'].values
        pool_after = df['1951_poolnum'][1:].append( pd.Series([0]) ).values
        df['pool2buffer'] = pool_before - pool_after
        return df
    elif node_id == 2077:
        pool_before = df['2077_poolnum'].values + df['2077_inflow'].values
        pool_after = df['2077_poolnum'][1:].append( pd.Series([0]) ).values
        df['pool2buffer'] = pool_before - pool_after
        return df
    else:
        return df


def gen_label(df, node_id = None, link_id = None):

    if node_id is not None:
        if node_id == 1949:
            df = df.rename(columns={"1949_inflow":"label"}) #1949作为发车点，不使用model
        elif node_id == 1951:
            df = df.rename(columns={"1951_inflow":"label"})
        elif node_id == 2077:
            df = df.rename(columns={"2077_inflow":"label"})
        elif node_id == 102076:
            df = df.rename(columns={"2077_outflow":"label"}) #最后一个节点连接的是link2077的出量


    if link_id is not None:
        df = df.rename(columns={"pool2buffer":"label"}) #1949作为发车点，不使用model

    return df


#丢弃一些无关特征
def drop_feature(df, node_id = None, link_id = None):
    if node_id is not None:
        if node_id == 1949:
            df = df.drop(['1949_buffernum','1949_outflow'], axis = 1)
        elif node_id == 1951:
            df = df.drop(['1949_inflow','1949_poolnum','1951_outflow','1951_buffernum'], axis = 1)
        elif node_id == 2077:
            df = df.drop(['1951_inflow','1951_poolnum','2077_outflow','2077_buffernum'], axis = 1)
        elif node_id == 102076:
            df = df.drop(['2077_inflow','2077_poolnum'], axis = 1)

    if link_id is not None:
        if link_id == 1949:
            df = df.drop(['1949_inflow','1949_outflow'], axis = 1)
        elif link_id == 1951:
            df = df.drop(['1949_inflow','1949_buffernum','1949_poolnum','1951_inflow','1951_outflow'], axis = 1)
        elif link_id == 2077:
            df = df.drop(['1951_inflow','1951_buffernum','1951_poolnum','2077_inflow','2077_outflow'], axis = 1)

    return df


#TODO 扩充数据
def expand(df):
    pass

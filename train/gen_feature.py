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
        new_df = new_df.rename(columns={"1949_inflow":"label"}) #1949作为发车点，不使用model
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
        new_df = new_df.rename(index=str, columns={'1951_inflow':'label'})
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
        new_df = new_df.rename(index=str, columns={'2077_inflow':'label'})
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
        new_df = new_df.rename(index=str, columns={'2077_outflow':'label'})
        return new_df


#根据frame分组
def group_frame(df, period_dur = 600 , timestep = 60):

    df['period'] = (df['frame'] % period_dur / timestep).astype('int32')
    df = df.drop(['frame'],axis=1)
    #df.groupby(['period'])
    #df.get_group(1)
    return df

#TODO 扩充数据
def expand(df):
    pass

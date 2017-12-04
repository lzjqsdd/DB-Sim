#node/link process and analysis

import pandas as pd
from pandas import DataFrame,Series
import matplotlib.pyplot as plt


col_single_in = ['frame','pre_num','pre_oflow','pre_v','cur_num','cur_inflow','cur_v']

data_1951 = pd.read_csv("../data/sample/1951_node_sample.txt",delim_whitespace=True)
print (data_1951.describe())

from train_model import *


def train(carnum):

    if(carnum == 300):
        train_for_node(node_id = 1949, nodetype = 0, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3}) #period600
        train_for_node(node_id = 1951, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2073, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2075, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2066, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2068, nodetype = 1, train_size = 1, param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2062, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2017, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2562, nodetype = 1, train_size = 1, param = {'max_depth':7, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2621, nodetype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2584, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2581, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2571, nodetype = 1, train_size = 1, param = {'max_depth':13, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2637, nodetype = 1, train_size = 1, param = {'max_depth':18, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 102636, nodetype = 2, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

        ##train for each pool2buffer
        train_for_pool2buffer(link_id = 1949, linktype = 0, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 1951, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2073, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2075, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3})
        train_for_pool2buffer(link_id = 2066, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2068, linktype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2062, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2017, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2562, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2621, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2584, linktype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2581, linktype = 1, train_size = 1, param = {'max_depth':16, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2571, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2637, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

    elif(carnum == 400):
        train_for_node(node_id = 1949, nodetype = 0, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3}) #period600
        train_for_node(node_id = 1951, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2073, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2075, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2066, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2068, nodetype = 1, train_size = 1, param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2062, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2017, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2562, nodetype = 1, train_size = 1, param = {'max_depth':7, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2621, nodetype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2584, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2581, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2571, nodetype = 1, train_size = 1, param = {'max_depth':13, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2637, nodetype = 1, train_size = 1, param = {'max_depth':18, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 102636, nodetype = 2, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

        ##train for each pool2buffer
        train_for_pool2buffer(link_id = 1949, linktype = 0, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 1951, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2073, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2075, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3})
        train_for_pool2buffer(link_id = 2066, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2068, linktype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2062, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2017, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2562, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2621, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2584, linktype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2581, linktype = 1, train_size = 1, param = {'max_depth':16, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2571, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2637, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

    elif(carnum == 500):
        #train_for_node(node_id = 1949, nodetype = 0, train_size = 0.8, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3}, cut_start = 1800, cut_end = 9000) #period600
        #train_for_node(node_id = 1949, nodetype = 0, train_size = 0.8, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3}) #period600
        #train_for_node(node_id = 1949, nodetype = 0, train_size = 0.8, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3}) #period600
        #train_for_node(node_id = 1951, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2073, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2075, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2066, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2068, nodetype = 1, train_size = 1, param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2062, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2017, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2562, nodetype = 1, train_size = 1, param = {'max_depth':7, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2621, nodetype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2584, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2581, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2571, nodetype = 1, train_size = 1, param = {'max_depth':13, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2637, nodetype = 1, train_size = 1, param = {'max_depth':18, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 102636, nodetype = 2, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

        ##train for each pool2buffer
        #train_for_pool2buffer(link_id = 1949, linktype = 0, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 1951, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2073, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2075, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3})
        #train_for_pool2buffer(link_id = 2066, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2068, linktype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2062, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2017, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2562, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2621, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2584, linktype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2581, linktype = 1, train_size = 1, param = {'max_depth':16, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2571, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2637, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

    elif(carnum == 750):
        train_for_node(node_id = 1949, nodetype = 0, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3}) #period600
        train_for_node(node_id = 1951, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2073, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2075, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2066, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2068, nodetype = 1, train_size = 1, param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2062, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2017, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2562, nodetype = 1, train_size = 1, param = {'max_depth':7, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2621, nodetype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2584, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2581, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2571, nodetype = 1, train_size = 1, param = {'max_depth':13, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 2637, nodetype = 1, train_size = 1, param = {'max_depth':18, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        train_for_node(node_id = 102636, nodetype = 2, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

        ##train for each pool2buffer
        train_for_pool2buffer(link_id = 1949, linktype = 0, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 1951, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2073, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2075, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3})
        train_for_pool2buffer(link_id = 2066, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2068, linktype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2062, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2017, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2562, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2621, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2584, linktype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2581, linktype = 1, train_size = 1, param = {'max_depth':16, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2571, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        train_for_pool2buffer(link_id = 2637, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

    elif(carnum == 1000):
        train_for_node(node_id = 1949, nodetype = 0, train_size = 0.8, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3},
                cut_start = 1800, cut_end = 15000) #period600
        #train_for_node(node_id = 1951, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2073, nodetype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2075, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2066, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2068, nodetype = 1, train_size = 1, param = {'max_depth':3, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2062, nodetype = 1, train_size = 1, param = {'max_depth':8, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2017, nodetype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2562, nodetype = 1, train_size = 1, param = {'max_depth':7, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2621, nodetype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2584, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2581, nodetype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2571, nodetype = 1, train_size = 1, param = {'max_depth':13, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 2637, nodetype = 1, train_size = 1, param = {'max_depth':18, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2}) #period600
        #train_for_node(node_id = 102636, nodetype = 2, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})

        ##train for each pool2buffer
        #train_for_pool2buffer(link_id = 1949, linktype = 0, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 1951, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2073, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2075, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':3})
        #train_for_pool2buffer(link_id = 2066, linktype = 1, train_size = 1, param = {'max_depth':4, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2068, linktype = 1, train_size = 1, param = {'max_depth':5, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2062, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2017, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2562, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2621, linktype = 1, train_size = 1, param = {'max_depth':10, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2584, linktype = 1, train_size = 1, param = {'max_depth':15, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2581, linktype = 1, train_size = 1, param = {'max_depth':16, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2571, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})
        #train_for_pool2buffer(link_id = 2637, linktype = 1, train_size = 1, param = {'max_depth':12, 'eta':1, 'silent':1, 'objective':'multi:softmax', 'num_class':2})





if __name__ == '__main__':
    train(int(st.demands[0]))

import xgboost as xgb
import os
import pandas as pd
import numpy as np
#从DataFrame中构造, 每次只构造一个node的一个period的df
#最小设计

class XGBModel:
    '''Summary: XGBModel can be used for only one node

    Attribute:
        train_data: pandas.DataFrame format, passing when init
        test_data: pandas.DataFrame format, passing when init
        clf : xgboost classfier
        node_id : current model will be used for node_id
    '''

    def __init__(self, node_id , train_data = None, test_data = None):
        '''
        Each model only train for one node.

        :param node_id: node_id which it will be trained for.
        :param train_data: Default None.You can load later.
        :param test_data: Defalut None. You can load later.
        '''

        self.node_id = node_id
        self.train_data = train_data
        self.test_data = test_data
        self.clf = None

    def loadData(self, train_data, test_data = None):
        self.train_data = train_data
        self.test_data = test_data

    def train(self, shuffle = False, param = None, model_path=None):
        '''Train for xgboost model

        Parameters
        ----------
            shuffle : bool
                True or False. Shuffle data when True.
            param : dict
                Use defalut params when None.
            savemodel : bool
                Save model to disk when True.
        Returns
        ---------
            clf : Booster
        '''

        if self.train_data is None:
            print("You need load train_data before train!")
            return
        # read in data
        train_y = self.train_data['label']
        train_x = self.train_data.drop(['label'],axis=1)
        dtrain = xgb.DMatrix(data = self.train_data, label=train_y)
        # specify parameters via map
        if param is None:
            param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'multi:softmax',
                     'num_class':8}

        num_round = 10
        bst = xgb.train(param, dtrain, num_round)
        if  model_path is None:
            model_file = str(self.node_id)+'.model'
            full_filename = os.path.join(model_path,model_file)
            bst.save_model(full_filename)

    def loadModel(self, model_path) -> xgb.Booster:
        ''' Load xgboost model from saved modelfile.

        Parameters
        ----------
            model_file: str
                model file path. if None, will use settting values.See also setting class.
                Note! : model must contains prefix path,not only filename.

        Returns
        -------
            clf : Booster

        '''

        model_file = str(self.node_id)+'.model'
        full_filename = os.path.join(model_path,model_file)
        if not os.path.exists(full_filename):
            print(full_filename + " not exits!")
            return

        self.clf = xgb.Booster(model_file = full_filename)
        return self.clf


    def test(self):
        if self.test_data is None:
            print("You need load test_data before test!")
            return

        if self.clf is None:
            print("You need load Model before test!")
            return

        test_x = self.test_data.drop(['label'], axis=1)
        dtest = xgb.DMatrix(test_x)
        res = self.clf.predict(dtest)

        self.score(res, self.test_data.label)

    def score(self, pred, origin):

        err = abs(pred != origin)
        train_error = np.array(err).sum() / len(err)
        print("train error is : ", train_error)
        pass

import xgboost as xgb
import os
import setting as st
import pandas as pd
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

    def __init__(self, train_data, test_data, node_id):
        self.train_data = train_data
        self.test_data = test_data
        self.node_id = node_id

    def train(self, shuffle = False, param = None, savemodel=True):
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

        # read in data
        train_y = self.train_data['label'] / 10.0
        train_x = self.train_data.drop(['label'],axis=1)
        dtrain = xgb.DMatrix(data = self.train_data, label=train_y)
        # specify parameters via map
        if not param:
            param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'binary:logistic'}

        num_round = 10
        bst = xgb.train(param, dtrain, num_round)
        if savemodel:
            model_file = str(self.node_id)+'.model'
            bst.save_model(os.path.join(st.xgboost_model_path,model_file))

    def loadmodel(self, model_file) -> xgb.Booster:
        ''' Load xgboost model from saved modelfile.

        Parameters
        ----------
            model_file: str
                model file path. if None, will use settting values.See also setting class.
                Note! : model doesn't contains prefix path,just filename.

        Returns
        -------
            clf : Booster

        '''


        if not os.path.exists(model_file):
            print(model_file + " not exits!")

        clf = xgb.Booster(model_file = model_file)
        return clf


    def test(self):
        dtest = xgb.DMatrix(self.test_data)
        xgb.predict(dtest)

    def score(self):
        pass

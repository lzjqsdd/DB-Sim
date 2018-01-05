import xgboost as xgb
import os
import setting as st


def train():
    # read in data
    dtrain = xgb.DMatrix('../data/demo/agaricus.txt.train')
    dtest = xgb.DMatrix('../data/demo/agaricus.txt.test')
    # specify parameters via map
    param = {'max_depth':2, 'eta':1, 'silent':1, 'objective':'binary:logistic' }
    num_round = 2
    bst = xgb.train(param, dtrain, num_round)
    bst.save_model(os.path.join(st.xgboost_model_path,'demo.model'))
    # make prediction
    preds = bst.predict(dtest)

def loadmodel():
    dtest = xgb.DMatrix('../data/demo/agaricus.txt.test')

    model_file = os.path.join(st.xgboost_model_path,'demo.model')
    bst = xgb.Booster(model_file = model_file)
    preds = bst.predict(dtest)
    print(preds)


loadmodel()

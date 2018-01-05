#include <stdlib.h>
#include<iostream>
#include<fstream> 
#include<string>
#include<vector>
#include <sstream>
#include <xgboost/c_api.h>
#include <stdio.h> 
#include <string.h>
using namespace std;

void split(string str, char ch, vector<string> &ivec)
{
    stringstream sin(str);
    string word;
    int i=0;
    while (std::getline(sin, word, ch))
    {
        //	cout<<i<<":"<<word<<endl;
        ivec.push_back(word );
        i++;
    }
}

/*
int main(int argc, char *argv[])
{
    cout<<"begin"<<endl;	
    if(argc != 4)
    { 
        cout<<"wrong input"<<endl;
        return 1; //参数不够
    }
    char *uin = argv[1];  //用户id
    //cout<<uin<<endl;
    char *char_character = argv[2];	   //用户特征序列，逗号隔开
    //cout<<char_character<<endl;
    const char *fname = argv[3];       //模型文件路径
    //cout<<fname<<endl;
    vector<string> ivec;
    string test_data=char_character;
    //cout<<test_data<<endl;
    split(test_data,',',ivec);    //解析用户特征，都逗号分隔，放入vector
    int cols=ivec.size();
    float uin_data[1][cols];             //放入二维矩阵
    for ( int i = 0 ; i < ivec.size() ; ++i )
    {
        uin_data[0][i]=atof(ivec[i].c_str());
    }
    BoosterHandle h_booster;
    const float *f;
    bst_ulong out_len;
    DMatrixHandle h_test[1];
    int sample_rows=1;
    XGDMatrixCreateFromMat((float *) uin_data, sample_rows, cols, -1, &h_test[0]);
    XGBoosterCreate(h_test,1,&h_booster);
    //      ret=XGBoosterLoadModelFromBuffer(h_booster,pbuf, iSize);
    int ret=XGBoosterLoadModel(h_booster,fname);  //加载模型
    cout << uin <<" ,load:"<<ret<<endl;	       
    XGBoosterPredict(h_booster, h_test[0], 0,0,&out_len,&f);  //预测
    for (unsigned int i=0;i<out_len;i++)
    {
        cout << uin << " ,prediction[" << i << "]=" << f[i] << endl;
    }
    // free xgboost internal structures
    XGDMatrixFree(h_test[0]);
    XGBoosterFree(h_booster);
    cout<<"end"<<endl;
    return 0;

}
*/


int main()
{
    // create the train data
    int cols=3,rows=5;
    float train[rows][cols];
    for (int i=0;i<rows;i++)
        for (int j=0;j<cols;j++)
            train[i][j] = (i+1) * (j+1);

    float train_labels[rows];
    for (int i=0;i<rows;i++)
        train_labels[i] = 1+i*i*i;


    // convert to DMatrix
    DMatrixHandle h_train[1];
    XGDMatrixCreateFromMat((float *) train, rows, cols, -1, &h_train[0]);

    // load the labels
    XGDMatrixSetFloatInfo(h_train[0], "label", train_labels, rows);

    // read back the labels, just a sanity check
    bst_ulong bst_result;
    const float *out_floats;
    XGDMatrixGetFloatInfo(h_train[0], "label" , &bst_result, &out_floats);
    for (unsigned int i=0;i<bst_result;i++)
        std::cout << "label[" << i << "]=" << out_floats[i] << std::endl;

    // create the booster and load some parameters
    BoosterHandle h_booster;
    XGBoosterCreate(h_train, 1, &h_booster);
    XGBoosterSetParam(h_booster, "booster", "gbtree");
    XGBoosterSetParam(h_booster, "objective", "reg:linear");
    XGBoosterSetParam(h_booster, "max_depth", "5");
    XGBoosterSetParam(h_booster, "eta", "0.1");
    XGBoosterSetParam(h_booster, "min_child_weight", "1");
    XGBoosterSetParam(h_booster, "subsample", "0.5");
    XGBoosterSetParam(h_booster, "colsample_bytree", "1");
    XGBoosterSetParam(h_booster, "num_parallel_tree", "1");

    // perform 200 learning iterations
    for (int iter=0; iter<200; iter++)
        XGBoosterUpdateOneIter(h_booster, iter, h_train[0]);

    // save model
    XGBoosterSaveModel(h_booster, "demo.model");

    // predict
    const int sample_rows = 5;
    float test[sample_rows][cols];
    for (int i=0;i<sample_rows;i++)
        for (int j=0;j<cols;j++)
            test[i][j] = (i+1) * (j+1);
    DMatrixHandle h_test;
    XGDMatrixCreateFromMat((float *) test, sample_rows, cols, -1, &h_test);
    bst_ulong out_len;
    const float *f;
    //XGBoosterPredict(h_booster, h_test, 0,0,&out_len,&f);
    //for (unsigned int i=0;i<out_len;i++)
    //    std::cout << "prediction[" << i << "]=" << f[i] << std::endl;

    //LoadModel and predict
    BoosterHandle t_booster = NULL;
    XGBoosterCreate(NULL, 0, &t_booster);
    XGBoosterLoadModel(t_booster, "demo.model");
    if(t_booster)
        XGBoosterPredict(t_booster, h_test, 0, 0, &out_len, &f);
    for (unsigned int i=0;i<out_len;i++)
        std::cout << "prediction[" << i << "]=" << f[i] << std::endl;


    // free xgboost internal structures
    XGDMatrixFree(h_train[0]);
    XGDMatrixFree(h_test);
    XGBoosterFree(h_booster);
    XGBoosterFree(t_booster);

}

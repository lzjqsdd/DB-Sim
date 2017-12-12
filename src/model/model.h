//common model interface
#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
using namespace std;

class Model{
    public:
        virtual void init() = 0; //init model args
        virtual void train() = 0; //train model
        virtual void predict(const vector<int> &input, vector<int> &output) = 0;
};

#endif

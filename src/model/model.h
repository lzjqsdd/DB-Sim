//common model interface
#ifndef __MODEL_H__
#define __MODEL_H__

#include "../core/config.h"

#include <vector>
using namespace std;

class Model{
    public:
        virtual void init(){}

        virtual void init(const Config& config) = 0; //init model args
        virtual void train() = 0; //train model
        virtual void predict(const vector<float> &input, vector<float> &output) = 0;
        virtual void predict(int node_id, const vector<float> &input, float &output){}
};

#endif

//DataBased FETE
#ifndef __DBFETE_H__
#define __DBFETE_H__

#include "bfete.h"
#include "config.h"
#include "../model/model.h"

#include <map>
#include <set>

class DBFETE: public FETEIf {
    public:
        DBFETE();
        DBFETE(const Config& config);
        DBFETE& operator=(const DBFETE& fete);

        
        void loadNetwork(); //从xml中加载路网
        void init(); //初始化需求
		void generate(); //从场景里放车(agent)
        void doUpdate(); //迭代
        void start(); //启动模拟
        void check(); //检查限制条件

        bool isClean();//判断路网是否已经空了

        Config getConfig();
        vector<vector<int>> getPaths();

    private:
        int generatePerFrame();

    private:
        double min_num;
        double max_num;
        double mean_num;
        double genAgentNumMax;
        double genCount;
        int car_num;

        map<int, shared_ptr<Model>> node_models; //加载的模型，每个node对应一个
        map<int, shared_ptr<Model>> link_models; //加载的模型，每个link对应一个

};


#endif 

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
        void generate(float &node_inflow); //生成入量
        int generatePerFrame();
        vector<float> gen_node_feature(int node_id); //构造特征输入
        vector<float> gen_link_feature(int node_id);
        void showStatus(); //显示当前道路状态

    private:
        double min_num;
        double max_num;
        double mean_num;
        double genAgentNumMax;
        double genCount;
        int car_num; //当前生成的车辆数

        map<int, shared_ptr<Model>> node_models; //加载的模型，每个node对应一个
        map<int, shared_ptr<Model>> link_models; //加载的模型，每个link对应一个

        double origin_num; //起始点的数量
        double dest_num; //超级终点，统计系统输出

};


#endif 

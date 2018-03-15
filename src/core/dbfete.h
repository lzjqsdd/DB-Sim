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
        void generateFromData(); //从实例中发车
        vector<float> gen_node_feature(int node_id); //构造特征输入
        vector<float> gen_node_feature(int node_id,int nodetype); //构造特征输入
        vector<float> gen_link_feature(int node_id);
        vector<float> gen_link_feature(int node_id,int linktype);
        void showStatus(); //显示当前道路状态
        void writeStatus();
        void initSimFiles();//初始化格式化输出文件,csv 格式
        void initStaticData(); //初始化静态发车数据

    private:
        double min_num;
        double max_num;
        double mean_num;
        double genAgentNumMax;
        double genCount;
        int car_num; //当前生成的车辆数
        double readygo_num; //即将出发的车辆数，已生成但是还未发车的

        map<int, shared_ptr<Model>> node_models; //加载的模型，每个node对应一个
        map<int, shared_ptr<Model>> link_models; //加载的模型，每个link对应一个

        double origin_num; //起始点的数量
        double dest_num; //超级终点，统计系统输出

        double hasFlow; //判断当前是否存在流量
        vector<int> static_data; //静态发车数据

};


#endif 

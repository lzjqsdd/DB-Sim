#ifndef __CFETE_H__
#define __CFETE_H__

#include "bfete.h"
#include "config.h"
#include "manager.h"

#include <map>
#include <set>

//Ceil's model
class CFETE: public FETEIf {
    public:
        CFETE();
        CFETE(const Config &config);
        CFETE& operator=(const CFETE& fete);

        void loadNetwork(); //从xml中加载路网
        void init(); //初始化需求
		void generate(); //从场景里放人
        void doUpdate(); //迭代
        void start(); //启动模拟
        void check(); //检查限制条件

        bool isClean();//判断路网是否已经空了

        Config getConfig();

    private:
        Config _config; //从配置文件.conf中读取文件
        Manager * _manager;
        map<int, Link*> links; //全局唯一实际的数据存储
        map<int, Node*> nodes; //方便直接从id检索所有的信息
        int curtime; //当前模拟的时间轴
        bool Finished; //判断是否终止模拟
        int curnum; //当前已经有的人数，也用作编号
		int total_num; //总车数

		std::set<int> startIds; //记录集合点
		std::set<int> endIds; //记录安置点
		std::vector<std::vector<int>> paths; //以id形式记录path
		std::map<int,int> pcurnum; //curnum of every path
};

#endif

#ifndef __FETEIF_H__
#define __FETEIF_H__

#include "config.h"
#include "manager.h"

#include <map>
#include <set>
#include <vector>

//定义抽闲基类
class FETEIf{
    public:
        virtual void loadNetwork() = 0; //从xml中加载路网
        virtual void init() = 0; //初始化需求
		virtual void generate() = 0; //从场景里放人
        virtual void doUpdate() = 0; //迭代
        virtual void start() = 0; //启动模拟
        virtual void check() = 0; //检查限制条件
        virtual bool isClean() = 0;//判断路网是否已经空了
        virtual Config getConfig() = 0;
        virtual vector<vector<int>> getPaths() = 0;

        Config _config; //从配置文件.conf中读取文件
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

	protected:
        Manager * _manager;
};

#endif

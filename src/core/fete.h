#ifndef __FETE_H__
#define __FETE_H__

#include "config.h"
#include "manager.h"

class FETE{
    public:
        FETE();
        FETE(const Config &config);
        FETE& operator=(const FETE& fete);


        void loadNetwork(); //从xml中加载路网
        void init(); //初始化需求
        void doUpdate(); //迭代
        void doUpdateOld(); //采用ceil's方法迭代
        void start(); //启动模拟
        void check(); //检查限制条件
        Config getConfig();
    private:
        Config _config; //从配置文件.conf中读取文件
        Manager * _manager;
        vector<Link*> links;
        vector<Node*> nodes;
};

#endif

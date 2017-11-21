#ifndef __FETE_H__
#define __FETE_H__

#include "bfete.h"
#include "config.h"
#include "manager.h"

#include <map>
#include <set>

//Grawron's model
class GFETE: public FETEIf {
    public:
        GFETE();
        GFETE(const Config &config);
        GFETE& operator=(const GFETE& fete);

        void loadNetwork(); //从xml中加载路网
        void init(); //初始化需求
		void generate(); //从场景里放人
        void doUpdate(); //迭代
        void start(); //启动模拟
        void check(); //检查限制条件

        bool isClean();//判断路网是否已经空了

        Config getConfig();
        vector<vector<int>> getPaths();
};

#endif

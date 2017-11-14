#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <iostream>
#include <vector>
#include <string>
#include <libconfig.h++>

#include "../core/type.h"
#include "../core/link.h"
#include "../core/node.h"
#include "../core/config.h"

using namespace std;

//负责配置初始化、数据加载等工作
//单例模式
class Manager{
    public:
        static Manager* getManager();
        void init();

        void loadConfig(const string& filepath, Config& config);
        void loadLinks(const string& filepath, map<int, Link*>& links, vector<vector<int>>& paths);
        void loadNodes(const string& filepath, map<int, Node*>& nodes);
		void fillLinks(const vector<vector<int>>& paths,map<int, Link*>& links);

    protected:
        Manager();
    private:
        static Manager * _manager;
};


#endif

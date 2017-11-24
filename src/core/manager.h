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
        static shared_ptr<Manager> getManager();
        void init();

        void loadConfig(const string& filepath, Config& config);
        void loadLinks(const string& filepath, map<int, shared_ptr<Link>>& links, vector<vector<int>>& paths);
        void loadNodes(const string& filepath, map<int, shared_ptr<Node>>& nodes);
		void fillLinks(const vector<vector<int>>& paths,map<int, shared_ptr<Link>>& links);

    protected:
        Manager();
    private:
        static shared_ptr<Manager> _manager;
};


#endif

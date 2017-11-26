#ifndef __TETE_H__
#define __TETE_H__

#include "bfete.h"
#include "config.h"
#include "manager.h"

#include <map>
#include <set>

//Test model for static input and output
class TFETE: public FETEIf {
    public:
		class LinkData;
        TFETE();
        TFETE(const Config &config);
        TFETE& operator=(const TFETE& fete);

        void loadNetwork(); //从xml中加载路网
        void init(); //初始化需求
		void generate(); //从场景里放人
        void doUpdate(); //迭代
        void start(); //启动模拟
        void check(); //检查限制条件

        bool isClean();//判断路网是否已经空了
		void loadStaticData(const string& datapath); //加载每时刻的流量数据

        Config getConfig();
        vector<vector<int>> getPaths();
		map<int,map<int,shared_ptr<LinkData>>> static_data;

	public:
		class LinkData{
		public:
			LinkData(int inflow,int outflow,int poolnum):
				inflow(inflow),
				outflow(outflow),
				poolnum(poolnum) {
			}

			int poolnum;
			int inflow;
			int outflow;
		};
};

#endif

#ifndef __FETE_H__
#define __FETE_H__

class FETE{
    public:
        void loadNetwork(); //从xml中加载路网
        void init(); //初始化需求
        void doUpdate(); //迭代
        void start(); //启动模拟
        void check(); //检查限制条件
    private:
};

#endif

#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <utility>
#include <iomanip>
using namespace std;

class Node{
    public:
        Node();
        Node(int id, vector<int> flinks, vector<int>tlinks, float capacity);
        Node(const Node& node);
        Node& operator=(const Node& node);
        friend ostream& operator<<(ostream& os, const Node& node);
        ~Node();

        int id; //node id
        vector<int> flinks;
        vector<int> tlinks;
        bool isOrigin; //标示是否是起点

        float inflow; //记录每个迭代周期的入量
        float capacity; //单位timestep内最大的流量
};

#endif

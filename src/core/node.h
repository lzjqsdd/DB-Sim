#ifndef __NODE_H__
#define __NODE_H__

#include<vector>
#include<utility>
using namespace std;

class Node{
    public:
        Node();
        Node(int id, vector<int> flinks, vector<int>tlinks);
        Node(const Node& node);
        Node& operator=(const Node& node);
        ~Node();

    private:
        int id; //node id
        vector<int> flinks;
        vector<int> tlinks;
        bool isOrigin; //标示是否是起点
};

#endif

#pragma once
#include <list>
#include "Const.h"
class Graph
{
public:
    Graph(int);// Constructor
	~Graph() = default;
    void addEdge(int v, int w);
    void clearEdge();
    int BFS(int s);
    bool isEndOfBoard(int node) const;
    int getTheNodeToGo(const int start, const vector<pair<int, int>> parentsOfNode);
private:

    int m_v;
    vector<list<int>> m_adj;

};



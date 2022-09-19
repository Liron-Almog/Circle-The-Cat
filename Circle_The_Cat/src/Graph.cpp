#include "Const.h"
#include <list>
#include "Graph.h"
#include <utility>

//-----------------costructor---------------
Graph::Graph(int v)
{
    m_v = v;
    m_adj.resize(v);
}
//-----------------clearEdge---------------
void Graph::clearEdge() {

    m_adj.clear();
    m_adj.resize(m_v);
}
//-----------------addEdge---------------
void Graph::addEdge(int v, int w){

    m_adj[v].push_back(w); // Add w to v’s list.
}
//The function executes the BFS algorithm
//---------------BFS------------------
int Graph::BFS(int start)
{
    int startNode = start;
    vector< pair <int, int> > parentsOfNode;

    // Mark all the vertices as not visited
    vector<bool> visited;
    visited.resize(m_v, false);

    // Create a queue for BFS
    std::list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[start] = true;
    queue.push_back(start);

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        int vertexInProcess = queue.front();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex VertexInProcess. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (auto neighbor = m_adj[vertexInProcess].begin(); neighbor != m_adj[vertexInProcess].end(); ++neighbor)
        {
            if (!visited[*neighbor])
            {
                visited[*neighbor] = true;
                queue.push_back(*neighbor);
                parentsOfNode.push_back(make_pair(vertexInProcess, *neighbor));

                if (isEndOfBoard(*neighbor)) 
                    return getTheNodeToGo(startNode, parentsOfNode);
            }
        }
    }
    return CAUGHT_CAT;
}
//The function checks if we reached to the edge 
//------------isEndOfBoard--------------
bool Graph::isEndOfBoard(int node) const{

    if ((node < MAP_SIZE && node > -1) || //first row
        (MAP_SIZE * MAP_SIZE > node && MAP_SIZE * MAP_SIZE - MAP_SIZE < node)) {// last row
        return true;
    }
    //checks if first col or last col
     for (size_t i = 0; i < MAP_SIZE; i++){
         if (node == MAP_SIZE * i || node == MAP_SIZE * i + MAP_SIZE - 1)
             return true;
     }
     return false;
} 
//The function returns The son of start node 
//that leads to shortest path. 
//-----------getTheCellToGo-----------------
int Graph::getTheNodeToGo(const int start, const vector<pair<int, int>> parentsOfNode) {

 
     int i = parentsOfNode.size() - 1;
 
    while (true)
    {
        if (parentsOfNode[i].first == start)
            return parentsOfNode[i].second;//returns the son 
                                           //of start node

        else {
            //search for the father of current number 
            for (size_t cell = 0; cell < parentsOfNode.size()-1; cell++){
                if (parentsOfNode[i].first == parentsOfNode[cell].second) {
                    i = cell;
                    break;
                }      
            }
        }
    }
}


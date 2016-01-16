#ifndef UNDIRECTED_GRAPH_H__
#define UNDIRECTED_GRAPH__

#include <vector>
#include <string>

using std::vector;
using std::string;

class Graph
{
    private:
        int nodes;
        vector<vector<int>> edges;

    public:
        Graph(int V);
        void addEdge(int v, int w);
        vector<int> adj(int v);
        int V();
        string toString();
};

#endif // UNDIRECTED_GRAPH_H__

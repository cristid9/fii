#ifndef DIRECTED_GRAPH_H__
#define DIRECTED_GRAPH_H__

#include <vector>

using std::vector;

class Digraph
{
    private:
        int nodes;
        vector<vector<int>> edges;

    public:
        Digraph(int V);
        void insertArc(int v, int w);
        void removeArc(int v, int w);
//        vector<int> internAdj(int v);
//        vector<int> externAdj(int v);
//        vector<int> accessibleFrom(int v);
        Digraph transpose();
        vector<int> adj(int v);
};

#endif // DIRECTED_GRAPH_H__

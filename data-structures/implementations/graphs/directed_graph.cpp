#include "directed_graph.h"
#include <vector>
#include <algorithm>

using namespace std;

Digraph::Digraph(int v)
{
    nodes = v;

    for (int i = 0; i < v; i++)
        edges.push_back(vector<int>());
}

void Digraph::insertArc(int v, int w)
{
    if (find(edges.begin(), edges.end(), v) != edges.end())
        return;

    edges[v].push_back(w);
}



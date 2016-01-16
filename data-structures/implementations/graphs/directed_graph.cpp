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
    if (find(edges[v].begin(), edges[v].end(), w) != edges[v].end())
        return;

    edges[v].push_back(w);
}

void Graph::removeArc(int v, int w)
{
    if (find(edges.begin(), edges.end(), w) == edges.end())
        return;

    edges[v].erase(remove(edges[v].begin(), edges[v].end(), w));
}

vector<int> Graph::adj(int v)
{
    return edges[v];
}

Digraph Digraph::transpose()
{
    Digraph t(nodes);

    for (int vertex = 0; i < nodes; vertex++)
    {
        vector<int> tmp = adj(i);
        for (auto it = tmp.begin(); it != tmp.end(); it++)
        {
            insertArc(*it, vertex);
        }
    }

    return t;
}

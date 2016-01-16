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

void Digraph::removeArc(int v, int w)
{
    if (find(edges[v].begin(), edges[v].end(), w) == edges[v].end())
        return;

    edges[v].erase(remove(edges[v].begin(), edges[v].end(), w));
}

vector<int> Digraph::internAdj(int v)
{
    return edges[v];
}

vector<int> Digraph::externAdj(int v)
{
    return transpose().internAdj(v);
}

vector<int> Digraph::accessibleFrom(int v)
{
    vector<int> neighbors;
    visit(v, neighbors);

    neighbors.erase(remove(neighbors.begin(), neighbors.end(), v));

    return neighbors;
}

void Digraph::visit(int v, vector<int>& neighbors)
{
    if (find(neighbors.begin(), neighbors.end(), v) != neighbors.end())
        return;

    vector<int> tmp = internAdj(v);
    neighbors.push_back(v);

    for (auto it = tmp.begin(); it != tmp.end(); it++)
        visit(*it, neighbors);
}

Digraph Digraph::transpose()
{
    Digraph t(nodes);

    for (int vertex = 0; vertex < nodes; vertex++)
    {
        vector<int> tmp = internAdj(vertex);
        for (auto it = tmp.begin(); it != tmp.end(); it++)
        {
            insertArc(*it, vertex);
        }
    }

    return t;
}

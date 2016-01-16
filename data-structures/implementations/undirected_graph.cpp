#include "undirected_graph.h"
#include <algorithm>

using std::to_string;
using std::find;
using std::remove;

Graph::Graph(int V)
{
    nodes = V;

    for (int i = 0; i <= V; i++)
        edges.push_back(vector<int>());
}

void Graph::addEdge(int v, int w)
{
    if (find(edges[v].begin(), edges[v].end(), w)
            != edges[v].end())
        return;

    edges[v].push_back(w);
    edges[w].push_back(v);
}

void Graph::removeEdge(int v, int w)
{
    edges[v].erase(remove(edges[v].begin(), edges[v].end(), w));
    edges[w].erase(remove(edges[w].begin(), edges[w].end(), v));
}

vector<int> Graph::adj(int v)
{
    return edges[v];
}

void Graph::visit(int v, vector<int>& accessibleNodes)
{
    if (find(accessibleNodes.begin(), accessibleNodes.end(), v)
            != accessibleNodes.end())
        return;

    vector<int> neighbors = adj(v);
    accessibleNodes.push_back(v);

    for (auto it = neighbors.begin(); it != neighbors.end(); it++)
    {
        visit(*it, accessibleNodes);
    }
}

vector<int> Graph::accessibleFrom(int v)
{
    vector<int> accessibleNodes;
    visit(v, accessibleNodes);
    accessibleNodes.erase(remove(accessibleNodes.begin(),
                accessibleNodes.end(), v));

    return accessibleNodes;
}

int Graph::V()
{
    return nodes;
}

string Graph::toString()
{
    string repres = "{";

    for (int i = 0; i < nodes; i++)
    {
        if (i > 0)
            repres += ", " + to_string(i) + ": [";
        else
            repres += i + ": [";
        for (auto it = edges[i].begin(); it != edges[i].end(); it++)
        {
            repres += (*it) + ", ";
        }
        repres += "]";
    }

    repres += "}";

    return repres;
}

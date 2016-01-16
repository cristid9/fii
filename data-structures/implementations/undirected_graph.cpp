#include "undirected_graph.h"

using std::to_string;

Graph::Graph(int V)
{
    nodes = V;

    for (int i = 0; i < V; i++)
        edges.push_back(vector<int>());
}

void Graph::addEdge(int v, int w)
{
    edges[v].push_back(w);
}

vector<int> Graph::adj(int v)
{
    return edges[v];
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

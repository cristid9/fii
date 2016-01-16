#include "undirected_graph.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    Graph g(7);

    g.addEdge(0, 6);
    g.addEdge(0, 2);
    g.addEdge(0, 1);
    g.addEdge(0, 5);


    g.addEdge(3, 5);

    vector<int> a = g.accessibleFrom(0);
    for (auto it = a.begin(); it != a.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}

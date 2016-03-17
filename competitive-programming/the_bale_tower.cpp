#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

#define SIZE 20

using namespace std;

bool comparator(pair<int, int> a, pair<int, int> b)
{
    return ((a.first < b.first) && (a.second < b.second));
}

int main()
{
    int n;
    vector< pair<int, int> > bales;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        bales.push_back(make_pair(0, 0));
        cin >> bales[i].first;
        cin >> bales[i].second;
    }

    sort(bales.begin(), bales.end(), comparator);

    int count = 1;
    int prev  = n - 1;
    for (int i = n - 2; i >= 0; i--)
    {
        if (comparator(bales[i], bales[prev]))
        {
            count++;
            prev = i;
        }
    
    }

    cout << count << endl;

    return 0;
}

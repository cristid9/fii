#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{

    int n;
    cin >> n;
    
    vector<string> words;
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;

        sort(tmp.begin(), tmp.end());
        words.push_back(tmp);
    }

    sort(words.begin(), words.end());

    int maxSize = 0;
    int curSize = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (words[i] == words[i + 1])
        {
            curSize++;
        }
        else
        {
            maxSize = max(maxSize, curSize);
            curSize = 0;
        }
    }
   
    maxSize = max(maxSize, curSize);
    cout << maxSize + 1 << endl;

    return 0;
}

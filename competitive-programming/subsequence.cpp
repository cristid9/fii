#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void reverse(string &s)
{
    size_t N = s.size();

    for (int i = 0, j = N - 1; i <= j; i++, j--)
        swap(s[i], s[j]);
}

bool isSubseq(string s1, string s2)
{
    int N = s1.size();
    int M = s2.size();

    int i = 0;
    int j = 0;
    
    for (; i < N; i++)
    {
        if (s1[i] == s2[j]) 
        {
            j++;
        }
    }

    if (j != M)
        return false;
    return true;
}

int main()
{
    int tests;
    cin >> tests;

    while (tests--)
    {
        string s1, s2;
        cin >> s1 >> s2;
        
        bool condition = isSubseq(s1, s2);
        reverse(s2);
        condition = condition || isSubseq(s1, s2);
    
        if (condition)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }


    return 0;
}

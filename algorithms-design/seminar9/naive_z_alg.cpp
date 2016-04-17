#include <iostream>
#include <algorithm>
#include <string>

#define Z_SIZE 100

using namespace std;

// runs in O(n^2) because z values are computed inefficiently
bool naive_z(string text, string pat)
{
    // compute z values
    string s = pat + "$" + text;
    size_t N = s.size();
    size_t M = pat.size();

    for (int i = 1; i < N; i++)
    {
        size_t matches = 0;
        for (int j = 0; j < N; j++)
        {
            if (s[j] != s[i + j])
                break;
            matches++;
        }

        if (matches == M)
            return true;
    }

    return false;
}

int main()
{
    cout << naive_z("baabaa", "aab") << endl;

    
    return 0;
}

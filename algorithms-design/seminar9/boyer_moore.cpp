#include <iostream>
#include <algorithm>
#include <string>

#define RIGHT_SIZE 255

using namespace std;

bool boyer_moore(string haystack, string needle)
{
    size_t h_size = haystack.size();
    size_t n_size = needle.size();
    size_t skip;
    
    int right[RIGHT_SIZE];

    for (int i = 0; i < RIGHT_SIZE; i++)
        right[i] = -1;
    for (int i = 0; i < n_size; i++)
        right[needle[i]] = i;

    for (int i = 0; i < h_size; i += skip)
    {
        skip = 0;
        for (int j = n_size - 1; j >= 0; j--)
        {
            if (haystack[i + j] != needle[j])
            {
                skip = max(1, j - right[haystack[i + j]]);
                break;
            }
        }

        if (skip == 0)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    cout << boyer_moore("findneedle", "needle") << endl;
    return 0;
}

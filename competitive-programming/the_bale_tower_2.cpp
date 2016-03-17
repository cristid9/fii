#include <iostream>
#include <utility>

#define N 20

using namespace std;

int count(pair<int, int> *haystack, pair<int, int> needle, int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (haystack[i].first == needle.first 
            && haystack[i].second == needle.second)
        {
            count++;
        }
    }

    return count;
}

void count_possibilities(pair<int, int> *source, pair<int, int> *tmp, 
                         int put, int size, int &max_stack_size)
{
    if (put == size)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (count(source, source[i], size) > count(tmp, source[i], put))
        {
            if (put > 0)
            {
                if (source[i].first < tmp[put - 1].first && source[i].second < tmp[put - 1].second)    
                {
                    tmp[put] = source[i];    
                    max_stack_size = max(max_stack_size, put + 1);
                    count_possibilities(source, tmp, put + 1, size, max_stack_size);
                }
            }
            else
            {
                tmp[put] = source[i];    
                max_stack_size = max(max_stack_size, put + 1);
                count_possibilities(source, tmp, put + 1, size, max_stack_size);
            }
        }
    }
}

int main()
{
    int count;
    cin >> count;
    pair<int, int> bales[N];
    pair<int, int> tmp[N];

    for (int i = 0; i < count; i++)
    {
        cin >> bales[i].first;
        cin >> bales[i].second;
    }
    
    int max_stack_size = 1;
    count_possibilities(bales, tmp, 0, count, max_stack_size);

    cout << max_stack_size << endl;

    return 0;
}

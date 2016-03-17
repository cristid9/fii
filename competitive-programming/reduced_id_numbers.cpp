#include <iostream>

using namespace std;

#define MAX_SIZE 99999
#define MAX_GROUP_SIZE 300

int group_ids[MAX_GROUP_SIZE];
int modified_ids[MAX_GROUP_SIZE];

bool unique(int *v, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                continue;

            if (v[i] == v[j])
                return false;
        }
    }
    return true;
}

int main()
{
    int tests;
    cin >> tests;

    while (tests--)
    {
        int group_members;
        cin >> group_members;
        
        for (int i = 0; i < group_members; i++)
        {
            cin >> group_ids[i];
        }
        
        for (int m = 1; m < MAX_SIZE; m++)
        {
            for (int i = 0; i < group_members; i++)
            {
                modified_ids[i] = group_ids[i] % m;
            }

            if (unique(modified_ids, group_members))
            {
                cout << m << endl;
                break;
            }
        
        }
    }

    return 0;
}

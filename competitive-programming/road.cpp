#include <iostream>

#define MAX_SIZE 20

#define R 1
#define G 2
#define B 3

using namespace std;

int read_row(int road[])
{
    char tile;
    int road_size = 0;
    while (cin.get(tile) != '\n')
    {
        road[road_size] = tile;
        road_size++;
    }

    return road_size;
}

int main()
{
    int road[MAX_SIZE];
    int test_case;
    cin >> test_cases;

    while (test_cases--)
    {
        int size = read_row(road);
        
    }

    return 0;
}

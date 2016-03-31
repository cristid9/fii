#include <iostream>
#include <cstdio>

#define SIZE 1007

using namespace std;

int main()
{
    int tests;
    double sample[SIZE];
    cin >> tests;

    while (tests--)
    {
        int elements;
        cin >> elements;
        double average = 0;
        
        for (int i = 0; i < elements; i++)
        {
            cin >> sample[i];
            average += sample[i];
        }

        average      /= elements;
        int gtAverage = 0;
        for (int i = 0; i < elements; i++) 
        {
            if (sample[i] > average)
                gtAverage++;
        }

        printf("%.3lf%%\n", ((double)(gtAverage * 100)) / ((double)elements));
    }
    
    return 0;
}

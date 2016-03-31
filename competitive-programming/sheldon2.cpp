#include <iostream>
#include <algorithm>
#include <climits>

#define HEAP_SIZE 100000

using namespace std;

void minHeapify(int *heap, int pos)
{
    for (int i = pos; i >= 0; i /= 2)
    {
        if (heap[i / 2] > heap[i])
        {
            swap(heap[i / 2], heap[i]);
        }
        else
            return;
    }
}
/*
void maxHeapify(int *heap, int pos)
{
    for (int i = pos; i >= 0; i /= 2)
    {
        if (heap[i / 2] < heap[i])
        {
            swap(heap[i / 2], heap[i]);
        }
        else
            return;
    }
}
*/

int main()
{
    int minHeap[HEAP_SIZE];

    int insPoint = 0;
    char opType;

    while (cin >> opType)
    {
        if (opType == 'n')
        {
            cin >> minHeap[insPoint];
            minHeap[insPoint] *= minHeap[insPoint];
            minHeapify(minHeap, insPoint);
            insPoint++; 
        }
        else
        {
            swap(minHeap[0], minHeap[insPoint - 1]);
            insPoint--;
            minHeapify(minHeap, insPoint);
        }
    }

    int tempMax = INT_MIN;
    for (int i = 0; i < insPoint; i++)
    {
        if (minHeap[i] > tempMax)
            tempMax = minHeap[i];
    }

    cout << tempMax << endl;


    return 0;
}

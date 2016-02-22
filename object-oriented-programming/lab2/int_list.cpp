#include <algorithm>
#include "int_list.h"

using std::swap;

IntList::IntList() 
{
    Count = 0;
}

bool IntList::Add(int element)
{
    if (Count >= 1000)
        return false;

    Elements[Count] = element;
    Count++;
    return true;
}

bool IntList::Insert(int index, int element)
{
    if (Count == 1000)
        return false;
    
    for (int i = Count - 1; i >= index; i--)
    {
        Elements[i + 1] = Elements[i];
    }

    Elements[index] = element;
    return true;

}

bool IntList::Delete(int index)
{
    if (index <= 0 || index >= Count)
        return false;
    
    for (int i = index; i < Count - 1; i++)
        Elements[i] = Elements[i + 1];

    Count--;
    return true;

}

void IntList::Clear()
{
    Count = 0;
}

int IntList::IndexOf(int valoare, int startPosition)
{
    for (int i = startPosition; i < Count; i++)
    {
        if (Elements[i] == valoare)
            return i;
    }

    return -1;
}

void IntList::RemoveDuplicates()
{
    for (int i = 0; i < Count; i++)
   {
        for (int j = 0; j < Count; j++)
        {
            if (i == j)
                continue;
            
            if (Elements[i] == Elements[j])
            {
                Delete(j);
            }
        }
    }
}

void IntList::Intersection(IntList* withList, IntList* resultList)
{
    for (int i = 0; i < Count; i++)
    {
        if (withList->IndexOf(Elements[i], 0) != -1)
        {
            resultList->Add(Elements[i]);
        }
    }
}

void IntList::Reunion(IntList* withList, IntList* resultList)
{
    for (int i = 0; i < Count; i++)
    {
        resultList->Add(Elements[i]);
    }

    for (int i = 0; i < withList->GetCount(); i++)
    {
        if (resultList->IndexOf(withList->Get(i), 0) != -1)
        {
            resultList->Add(withList->Get(i));
        }
    }
}

void IntList::Sort()
{
    for (int i = 1; i < Count; i++)
    {
        int j = i;
        while (Elements[j] < Elements[j - 1] && j > 0)
        {
            swap(Elements[j], Elements[j - 1]);
            i--;
        }
    }
}

void IntList::Reverse()
{
    for (int i = 0, j = Count - 1; i <= j; i++, j--)
    {
        swap(Elements[i], Elements[j]);
    }
}

int IntList::Get(int index)
{
    return Elements[index];
}

int IntList::GetCount()
{
    return Count;
}

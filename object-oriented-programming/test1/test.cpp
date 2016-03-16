#include "test.h"
#include <iostream>

using namespace std;

Multime::Multime()
{
    count = 0;
}

Multime::Multime(int* array, int count)
{
    if (count < 0 || count > 50)
    {
        
    }

    this->count = count;
    for (int i = 0; i < count; i++)
    {
        this->multime[i] = array[i];
    }
}

void Multime::Print()
{
    for (int i = 0; i < this->count; i++)
        cout << this->multime[i] << " ";
    cout << endl;

}

Multime::Multime(const Multime& altaMultime)
{
    this->count = altaMultime.count;
    for (int i = 0; i < altaMultime.count; i++)
    {
        this->multime[i] = altaMultime.multime[i];
    }
}

bool Multime::Add(int element)
{
    if (count == 50)
        return false;
    this->multime[count] = element;
    count++;
    return true;
}

bool Multime::Remove()
{
    if (count == 0)
        return false;
    count--;
    return true;
}

static bool isIn(int* haystack, int size, int element)
{
    for (int i = 0; i < size; i++)
    {
        if (haystack[i] == element)
            return true;
    }
    return false;
}

Multime Multime::operator+(const Multime & operand)
{
    Multime tmp(this->multime, this->count);
    for (int i = 0; i < operand.count; i++)
    {
        if (!isIn(this->multime, this->count, operand.multime[i]))
        {
            tmp.Add(operand.multime[i]);
        }
    }

    return tmp;
}

Multime Multime::operator-(const Multime & operand)
{
    Multime tmp;
    
    for (int i = 0; i < this->count; i++)
    {
        if (!isIn((int *)operand.multime, operand.count, this->multime[i]))
        {
            tmp.Add(this->multime[i]);
        }
    }


    return tmp;
}

Multime Multime::operator*(const Multime & operand)
{
    Multime tmp;

    for (int i = 0; i < this->count; i++)
    {
        if (isIn((int *)operand.multime, operand.count, this->multime[i])) 
        {
            tmp.Add(this->multime[i]);
        }
    }

    return tmp;
}

Multime& Multime::operator=(Multime& a)
{
/*
    Multime tmp;
    tmp.count = a.count;
    for (int i = 0; i < this->count; i++)
    {
        tmp.multime[i] = a.multime[i];
    }

    return tmp;
*/
    return a;
}

void Multime::CartezianProduct(const Multime &m2)
{
    for (int i = 0; i < this->count; i++)
    {
        for (int i = 0; i < m2.count; i++)
        {
            cout << this->multime[i] << " " << m2.multime[i] << endl; 
        }
    }
}


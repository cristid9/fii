#include <iostream>
#include "lab8.h"

using namespace std;

int main()
{
    Array<int> a(3);
    
    int b = 1;
    int b2 = 2;
    int b3 = 3;

    a += b;
    a += b2;
    a += b3;

    Array<int> c(a);

    c.Insert(0, a);


    // cout << c[0] << endl;
    // cout << c[1] << endl;
    // cout << c[2] << endl;

    Array<int> d(3);

    d += 4;
    d += 5;
    d += 6;

    a = d;
    
    // cout << a[0] << endl;
    // cout << a[1] << endl;
    // cout << a[2] << endl;

    ArrayIterator<int> it  = a.GetBeginIterator();
    ArrayIterator<int> it2 = a.GetEndIterator();
    
    // ++it;
    // --it;

    it = it2;

    cout << *(it.GetElement()) << endl;

    return 0;
}

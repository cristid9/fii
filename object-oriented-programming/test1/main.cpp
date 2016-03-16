#include "test.h"

int main()
{
    int data1[4] = {21, 45, 10, 9};
    int data2[7] = {9, 11, 32, 61, 45, 90, 102};
    Multime m1(data1, 14);
    

    Multime m2(data2, 7);

    m1.Print();
    m2.Print();

    (m1 + m2).Print();
    (m1 * m2).Print();

    Multime m5(m2);
    m5.Print();

    (m1 - m2).Print();

   (m1 - m2).CartezianProduct(m1 * m2);

    return 0;
}

#ifndef MULTIME_H__
#define MULTIME_H__

class Multime
{
    private:
        int multime[50];
        int count;
    public:
        Multime();
        Multime(int* array, int count);
        Multime(const Multime& altaMultime);

        bool  Add(int element);
        bool Remove();

        void Print();


        Multime operator+(const Multime & operand);
        Multime operator-(const Multime & operand);
        Multime operator*(const Multime & operand);

        Multime& operator=(Multime& );

        void CartezianProduct(const Multime &m2);
};
#endif

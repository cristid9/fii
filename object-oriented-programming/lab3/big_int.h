#include <iostream>

using namespace std;

class BigNumber {

    private:

        char Number[256];

        int  CharactersCount;

    public:

        BigNumber (); // Constructor implicit

        BigNumber (int value); 

        BigNumber (const char * number); // Constructor de copiere



        bool Set(int value);

        bool Set(const char * number);



        BigNumber operator+ (const BigNumber & number);

        BigNumber operator* (const BigNumber & number);

        BigNumber operator- (const BigNumber & number);

        BigNumber operator/ (const BigNumber & number);



        friend bool operator == (const BigNumber & n1, const BigNumber & n2);

        friend bool operator != (const BigNumber & n1, const BigNumber & n2);

        friend bool operator <  (const BigNumber & n1, const BigNumber & n2);

        friend bool operator >  (const BigNumber & n1, const BigNumber & n2);

        friend bool operator >= (const BigNumber & n1, const BigNumber & n2);

        friend bool operator <= (const BigNumber & n1, const BigNumber & n2);

        friend ostream & operator<< (ostream & os, BigNumber & n2);

        operator const int();

        char & operator[] (const int index); // returneaza caracterul de pe pozitia index sau \0 in rest

        BigNumber operator() (int start, int end); // returneaza subnumarul de la caracterul start pana la caracterul index sau "0" daca start/index nu sunt valide.
};


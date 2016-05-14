#include <iostream>
#include <set>
#include <cstdlib>
#include <cmath>

using namespace std;

#define N 9999999UL
#define DIGITS 10

bool sieve[N + 2];

// some nasty problem during the contests
int man_atoi(char* tmp, size_t sz)
{
    int nr = 0;

    for (int i = 0; i < sz; i++)
    {
        nr = nr * 10 + tmp[i] - '0';
    }

    return nr;
}

void initSieve()
{
    for (int i = 2; i < N + 2; ++i)
        sieve[i] = true;

    long long int k     = 2;
    long long int limit = sqrt(N + 2) + 1;

    while (k <= limit)
    {
        if (sieve[k])
        {
            long long int j = 2;
            while (k * j < N + 2)
            {
                sieve[k * j] = false;
                j++;
            }
            k++;
        }
        else
        {
            k++;
        }
    }
}

// I know, globals are a bad idea... But you have to admit that the evil exists
// in this world.
int frec[8], cnt;
set<int> known;

void getAllPerm(char* digits, char* tmp, size_t length, int curIndex)
{   
    int x = man_atoi(tmp, curIndex);
    
    if(sieve[x] == 1 && known.find(x) == known.end())
    {
        cnt++;
        known.insert(x);
    }

    for (int i = 0; i < length; i++)
    {
        if(frec[i] == 0)
        {
            tmp[curIndex] = digits[i];
            frec[i] = 1;
            getAllPerm(digits, tmp, length, curIndex + 1);
            frec[i] = 0;
        }
    }
}

int main()
{
    initSieve();

    int tests;
    cin >> tests;
    cin.get();

    char digits[DIGITS];
    char tmp[DIGITS];

    while (tests--)
    {
        int curSize = 0;
        char curChar;

        while (cin.get(curChar))
        {
            if (curChar == '\n')
                break;

            digits[curSize] = curChar;
            curSize++;
        }

        getAllPerm(digits, tmp, curSize, 0);
        
        for(int j = 0; j <= 7; j++) frec[j] = 0;
        known = set<int>();

        cout << cnt << endl;

        cnt = 0;
    }

    return 0;
}



#include <iostream>
#include <cmath>

using namespace std;

int count_factors(long long int n)
{
    int factor = 2;
    int factors = 0;

    while (n > 1)
    {
        if (n % factor == 0)
        {
            while (n % factor == 0)
            {
                n /= factor;
            }
            factors++;
        }
        else
        {
            factor++;
        }

        if (factor * factor > n)
        {
            if (n > 1) factors++;
            break;
        }
    }
    
    return factors;
}

int main()
{
    long long int n;

    while (cin >> n)
    {
        if (n == 0) 
            break;
        cout << n << " : " << count_factors(n) << endl;   
    }

    return 0;
}

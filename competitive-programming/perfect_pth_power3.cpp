#include <iostream>
#include <cmath>

using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

int main()
{

    while (true)
    {
        long long int number;
        cin >> number;

        if (number == 0)
            break;

        bool negativeFlag = false;

        if (number < 0)
        {
            number       = -number;
            negativeFlag = true;
        }

        long long int candidate = 2;
        long long int result    = 0;
        long long int limit     = sqrt(number);   
        bool executed           = false;

        while (candidate <= limit)
        {
            if (number % candidate == 0)
            {
                long long int power = 0;
                while (number % candidate == 0)
                {
                    power++;
                    number /= candidate;
                }

                executed = true;
                result   = gcd(result, power);
            }
            else
            {
                candidate++;
            }
        }
 
        if (!executed)
            result = 1;

        while (negativeFlag && result % 2 == 0)
            result /= 2;
        
        cout << result << endl;
    }


    return 0;
}

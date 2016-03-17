#include <iostream>
#include <cmath>

long long int is_perfect_square(long long int candidate)
{
    for (long long int start = sqrt(candidate) - 1;
            start * start <= candidate; start++)
    {
        if (start * start == candidate)
        {
            return start;
        }
    }

    return -1;
}

using namespace std;

int main()
{
    long long int first_number;
    cin >> first_number;

    for (long long int second_number = first_number + 1; ; second_number++)
    {
        long long int first_pow  = first_number * first_number;
        long long int second_pow = second_number * second_number;

        long long int square;
        if ((square = is_perfect_square(first_pow + second_pow)) > 0)
        {
            cout << first_number << " " << second_number
                 << " " << square
                 << endl;
            break;
        }
    }
    

    return 0;
}

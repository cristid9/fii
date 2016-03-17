#include <iostream>
#include <cmath>

using namespace std;

#define MAX_SIZE 10000000
const double epsilon = 0.00000000000000000000001;

bool is_really_perfect_square(int candidate)
{
    for (int start = sqrt(candidate) - 1; start * start <= candidate; 
            start++)
    {
        if (start * start == candidate)
        {
            return true;
        }
    }

    return false;
}

bool is_perfect_square_candidate(double candidate)
{
    if (candidate - ((int)candidate) > epsilon)
    {
        return false;
    }
    return true;
}

int main()
{
    int first_number;
    cin >> first_number;

    for (int second_number = first_number + 1;
            second_number < MAX_SIZE; second_number++)
    {
        int first_pow = first_number * first_number;
        int second_pow = second_number * second_number;

        if (is_perfect_square_candidate(sqrt(first_pow + second_pow))
                && is_really_perfect_square(first_pow + second_pow))
        {
            cout << first_number << " " << second_number 
                << " " << (int)sqrt(first_pow + second_pow) << endl;
            break;
        }
    }


    return 0;
}


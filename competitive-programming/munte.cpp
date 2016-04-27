#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long int points;
    cin >> points;

    long long int cur_point = 0;
    long long int sticks = 0;

    while (points--)
    {
        int point;
        cin >> point;

        if (cur_point < point)
        {
            sticks += fabs(cur_point - point);
        }
        cur_point = point;
    }

    cout << sticks << endl;


    return 0;
}

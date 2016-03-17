#include <iostream>

using namespace std;

int gaus_formula(int n)
{
    return (n * (n + 1)) / 2;
}

int weighted_sum(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; k++)
    {
        sum += k * gaus_formula(k + 1);    
    }
    return sum;
}

int main()
{
    int datasets;
    cin >> datasets;

    for (int dataset = 1; dataset <= datasets; dataset++)
    {
        int n;
        cin >> n;
        cout << dataset << " " << n << " " << weighted_sum(n) << endl; 
    }

    return 0;
}

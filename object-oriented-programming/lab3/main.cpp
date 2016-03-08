#include <iostream>
#include "big_int.h"

using namespace std;

int main()
{
    {
        BigNumber n {23};
        BigNumber n2 {"+11"};
        BigNumber n3 {"+11"};

        // cout << (n3 < n2) << endl;
    }

    {
        BigNumber n1 {"-11"};
        BigNumber n2 {"-11"};

        // cout << (n1 == n2) << endl;
    }
    
    {
        BigNumber n1 {"-111"};
        BigNumber n2 {"+12"};

        // cout << (n1 != n2) << endl;
    
    }
   
    {
        BigNumber n1 {"+111"};
        BigNumber n2 {"11"};

        // cout << (n1 > n2) << endl;
    }

    {
        BigNumber zero {"+0"};
        BigNumber n4 {"-134324"};
        BigNumber n1 {"+123"};
        BigNumber n2 {"+123"};
        BigNumber n3 {"+1234"};

        // cout << (n1 >= n2) << endl;
        // cout << (n3 >= n2) << endl;
        // cout << (n4 > zero) << endl;
        // cout << (n4 < zero) << endl;
    }
   
    {
        BigNumber n1 {"+123"};
        BigNumber n2 {"+122"};
        BigNumber n3 {"+1234"};

        // cout << (n2 <= n1) << endl;
        // cout << (n1 <= n3) << endl;
  
    }
    
    {
        BigNumber n1 {"-244"};
        BigNumber n2 {"-9"};

        // cout << (n1 + n2) << endl;
    }

    {
        BigNumber n1 {"-200"};
        BigNumber n2 {"-200"};
        
        // cout << ((n1 + n2)[2])<< endl;
    }

    {
        BigNumber n1 {"-200"};
        BigNumber n2 {"-11"};
        // BigNumber n3 = n1 - n2;

        // cout << n3 << endl;
    }

    {
        BigNumber n1 {"+123"};
        BigNumber n2 {"+11"};
        BigNumber n3 = (n2 - n1);

        cout << n3 << endl;
    }

    return 0;
}

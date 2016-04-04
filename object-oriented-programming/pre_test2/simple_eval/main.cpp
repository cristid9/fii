#include <iostream>
#include <cstdio>
#include "eval.h"

using namespace std;

int main()
{
    Eval e;
    cout << e.SetExpression("1+2+3+4+5-6") << endl;
    cout << e.GetExpression() << endl;
    printf("Operatorul + e folosit de %d ori \n",e.GetOperatorCount('+'));
    cout << e.GetOperatorsList() << endl; // ar trebui sa afiseze "+-"
    cout << e.Evaluate() << endl; // ar trebui sa afiseze 9
}

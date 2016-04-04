#include "eval.h"
#include <stack>
#include <cstring>


string Eval::GetExpression()
{
    return expression;
}

// 6p] - seteaza noua expresie pentru evaluare. Returneaza false daca expresia nu este valida
Eval::Eval()
{
    expression = string();
}

bool Eval::SetExpression(const char *expre) 
{
    size_t len = strlen(expre);
    for (int i = 0; i < len; i++)
    {
        if (i % 2 == 0 && !(expre[i] >= '0' && expre[i] <= '9'))
            return false;
        else if (i % 2 != 0 && !(expre[i] == '-' || expre[i] == '+'))
            return false;
    
    }

    expression = string(expre);
    return true;
}

// [2p] - returneaza numarul de operatori de un anumit tip folositi in expresie sau 0 daca operatorul nu e folosit
int Eval::GetOperatorCount(char my_operator)
{
    string ops= GetOperatorsList();
    int count = 0;
    for (auto it = ops.begin(); it != ops.end(); it++ )
    {
        if (*it == my_operator)
            count++;
    }

    return count;
}

// [3p] - returneaza un string cu operatorii utilizati
string Eval::GetOperatorsList()
{
    string ops = string();
    for (auto it = expression.begin(); it != expression.end(); it++)
    {
        if (*it == '+' || *it == '-')
            ops += *it;
    }

    return ops;
}

// [9p] - returneaza rezultatul evaluarii
int Eval::Evaluate()
{
    stack<int> nums;
    stack<int> ops;

    for (auto it = expression.begin(); it != expression.end(); it++)
    {
        if ((it - expression.begin()) % 2 == 0)
        {
            nums.push(*it - '0');
        }
        else
        {
            ops.push(*it);
        }
    }

    while (nums.size() == 1)
    {
        int n1 = nums.top();
        nums.pop();
        int n2 = nums.top();
        nums.pop();

        if (ops.top() == '+')
            nums.push(n1 + n2);
        else
            nums.push(n1 - n2);

        ops.pop();
    }
    
    return nums.top();
}

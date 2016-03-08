#include "big_int.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

static int toChar(int digit)
{
    return '0' + digit;
}

static int toDigit(char d)
{
    return d - '0';
}

BigNumber::BigNumber()
{
    CharactersCount = 0;
}

BigNumber::BigNumber(int value)
{
    CharactersCount = 0;
    Set(value);
}

BigNumber::BigNumber (const char * number) // Constructor de copiere
{
    CharactersCount = 0;
    Set(number);
}

bool BigNumber::Set(int value)
{
    if (value > 0)
        Number[0] = '+';
    else
        Number[0] = '-';

    CharactersCount++;

    int digits = log10(value) + 1;
    for (int index = digits; index >= 1; index--) 
    {
        Number[index] = toChar(value % 10);
        value /= 10;
        CharactersCount++;
    }

    return true; // I don't know any case where somethign other than true is
    // required as return value
}

bool BigNumber::Set(const char * number)
{
    int len = strlen(number);
    if (len > 250)
        return false;

    for (int index = 0; index < len; index++)
    {
        if (strchr("0123456789+-", number[index]) == NULL)
        {
            CharactersCount = 0;
            return false;
        }
        Number[index] = number[index];
        CharactersCount++;
    }

    return true;
}

BigNumber BigNumber::operator+ (const BigNumber & number)
{
    BigNumber zero {"+0"};

    if (*this > zero && number > zero)
    {
        BigNumber result;

        int indexN1 = this->CharactersCount - 1;
        int indexN2 = number.CharactersCount - 1;
        int indexResult = max(indexN1, indexN2) + 1;
        int carry = 0;

        while (indexN1 >= 1 && indexN2 >= 1)
        {
            int sum = toDigit(this->Number[indexN1]) 
                + toDigit(number.Number[indexN2]); 
                + carry;

            result.Number[indexResult] = toChar(sum % 10);
            carry = sum / 10;
            result.CharactersCount++;
            
            indexN1--;
            indexN2--;
            indexResult--;
        }
    
        while (indexN1 >= 1)
        {
            int sum = toDigit(this->Number[indexN1]) + carry;
            result.Number[indexResult] = toChar(sum % 10);
            result.CharactersCount++;
            carry = sum / 10;
            indexN1--;
            indexResult--;
        }

        while (indexN2 >= 1)
        {
            int sum = toDigit(number.Number[indexN2]) + carry;
            result.Number[indexResult] = toChar(sum % 10);
            result.CharactersCount++;
            carry = sum / 10;
            indexN2--;
            indexResult--;
        }
        
        if (carry != 0)
        {
            result.Number[indexResult] = toChar(carry);
            result.CharactersCount++;
            indexResult--;
        }
        else
        {
            for (int index = 1; index < max(this->CharactersCount, number.CharactersCount);
                 index++)
            {
                result.Number[index] = result.Number[index + 1];
            }
        }

        result.Number[0] = '+';
        result.CharactersCount++;

        return result;
    }
    else if (*this < zero && number < zero)
    {
        (*this)[0] = '+';
        BigNumber pos = number;
        pos[0]  = '+';

        BigNumber result = *this + pos;
        result[0] = '-';

        return result;
    }
    else
    {
        if (*this > number)
        {
            BigNumber pos = number;
            pos[0] = '+';
            return *this - number;
        }
        else
        {
            (*this)[0] = '+';
            return *this - number;
        }
    }
}

BigNumber BigNumber::operator- (const BigNumber & number)
{
    BigNumber zero {"+0"};

    if (*this > zero && number > zero)
    {
        BigNumber result;
        BigNumber n1;
        BigNumber n2;
        
        if (*this > number)
        {
            n1 = *this;
            n2 = number;
        }
        else
        {
            n1 = number;
            n2 = *this;
        }
        
        result[0] = '+';

        int indexN1 = n1.CharactersCount - 1;
        int indexN2 = n2.CharactersCount - 1;
        int pending = 0;
        int borrow  = 0;

        while (indexN1 >= 1 && indexN2 >= 1)
        {
            int diff = toDigit(n1[indexN1]) - toDigit(n2[indexN2]) - borrow;
            
            if (diff < 0)
            {
                result[indexN1] = toChar(diff + 10);
                borrow = 1;
            }
            else
            {
                result[indexN1] = toChar(diff);
                borrow = 0;
            }

            if (diff == 0)
            {
                pending++;
            }
            else
            {
                result.CharactersCount += pending + 1;
                pending = 0;
            }

            indexN1--;
            indexN2--;
        }

        if (indexN1 >= 1)
        {
            result.CharactersCount += pending;
            while (indexN1 >= 1)
            {
                int diff = toDigit(n1[indexN1]) - borrow;
                if (diff < 0)
                {
                    result[indexN1] = toChar(diff + 10);
                    borrow = 0;
                }
                else
                {
                    result[indexN1] = toChar(diff);
                    borrow = 0;
                }

                result.CharactersCount++;
                indexN1--;
            }
        }

        return result;
    }
    else if (*this < zero && number > zero)
    {
        (*this)[0] = '+';

        BigNumber result = *this + number;
        result[0] = '-';
        return result;
    }
    else if (*this < zero && number < zero)
    {
        BigNumber pos = number;
        pos[0] = '+';
        BigNumber result = *this - pos;
        return result;
    }
    else if (*this > zero && number < zero)
    {
        BigNumber pos = number;
        pos[0] = '+';
        BigNumber result = *this + number; 
        return result;
    }
}

BigNumber BigNumber::operator* (const BigNumber & number)
{
}

BigNumber BigNumber::operator/ (const BigNumber & number)
{
}

bool operator == (const BigNumber & n1, const BigNumber & n2)
{
    if (n1.CharactersCount == n2.CharactersCount)
    {
        int index = 0;
        while (index < n1.CharactersCount)
        {
            if (n1.Number[index] != n2.Number[index]) 
                return false;
            index++;
        }
        return true;
    }
    
    return false;
}

bool operator != (const BigNumber & n1, const BigNumber & n2)
{
    return !(n1 == n2);
}

bool operator <  (const BigNumber & n1, const BigNumber & n2)
{
    if (n1.Number[0] == '-' && n2.Number[0] == '+')
    {
        return true;
    }
    else if (n1.CharactersCount < n2.CharactersCount)
    {
        return true;
    }

    int index = 1;
    
    while (index < n1.CharactersCount && n1.Number[index] == n2.Number[index])
        index++;

    if (toDigit(n1.Number[index]) < toDigit(n2.Number[index]))
    {
        return true;
    }

    return false;
}

bool operator >  (const BigNumber & n1, const BigNumber & n2)
{
    if (!(n1 < n2) && (n1 != n2))
        return true;
    return false;
}

bool operator >= (const BigNumber & n1, const BigNumber & n2)
{
    return ((n1 > n2) || (n1 == n2));
}

bool operator <= (const BigNumber & n1, const BigNumber & n2)
{
    return ((n1 < n2) || (n1 == n2));
}

BigNumber::operator const int()
{

}

char & BigNumber::operator[] (const int index) // returneaza caracterul de pe pozitia index sau \0 in rest
{
    return Number[index];
}

BigNumber BigNumber::operator() (int start, int end)
{
    
}

ostream & operator<< (ostream & os, BigNumber & number)
{
    for (int i = 0; i < number.CharactersCount; i++)
    {
        os << number[i];
    }
    return os;
}


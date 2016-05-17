#include <string>
#include <iostream>
#include <vector>
#include "visitor.h"

using namespace std;

int main()
{
    // Probably not the best way to represent this...
    
    vector<Fruit*> fruits
    { new Orange("10% c vitamin"), new Apple(), new Banana() };
    
    CVitaminVisitor *v = new CVitaminVisitor();

    for (auto it = fruits.begin(); it != fruits.end(); it++)
    {
        (*it)->accept(v) ;   
    }

    return 0;
}

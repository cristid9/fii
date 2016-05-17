#ifndef VISITOR_H__
#define VISITOR_H__

#include <string>
#include <iostream>
#include "fruit.h"

using namespace std;

class Banana;
class Orange;
class Apple;

class Visitor
{
    public:
        Visitor() {}

        // Not sure why, but it didn't compile without = 0;
        virtual void visit(Orange &orange) = 0;
        virtual void visit(Banana &banana) = 0;
        virtual void visit(Apple &apple) = 0;
};

class CVitaminVisitor : public Visitor
{
public:
    CVitaminVisitor() {}
    
    void visit(Orange &orange);

    void visit(Banana &banana);
    
    void visit(Apple &apple);
};

#endif



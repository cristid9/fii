#ifndef FRUIT_H__
#define FRUIT_H__

#include "visitor.h"
#include <string>

using namespace std;

class Visitor;

class Fruit
{
    private:
        string color;
        int size;
        string taste;
    public: 
        virtual void accept(Visitor *ov) = 0;
};

class Orange : public Fruit
{
    private:
        string cVitamin;

    public:
        Orange(string prop);
        void accept(Visitor *v);
        string getCVitamin() const;
};

class Banana : public Fruit
{
    public:
        void accept(Visitor *v);
};

class Apple : public Fruit
{
    public:
        void accept(Visitor *v);
};

#endif

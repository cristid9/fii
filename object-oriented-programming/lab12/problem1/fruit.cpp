#include "fruit.h"
#include "visitor.h"

Orange::Orange(string prop)
{
    cVitamin = prop;
}

void Orange::accept(Visitor *v)
{
    v->visit(*this);
}

string Orange::getCVitamin() const
{
    return cVitamin;
}

void Banana::accept(Visitor *v)
{
    v->visit(*this);
}

void Apple::accept(Visitor *v)
{
    v->visit(*this);
}

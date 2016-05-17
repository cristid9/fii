#include "visitor.h"
#include "fruit.h"

void CVitaminVisitor::visit(Orange &orange)
{
    cout << orange.getCVitamin()  << endl;    
}

void CVitaminVisitor::visit(Banana &banana)
{
    cout << "Invalid property" << endl;
}
    
void CVitaminVisitor::visit(Apple &apple)
{
    cout << "Invalid property" << endl;
}

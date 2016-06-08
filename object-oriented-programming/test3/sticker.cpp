#include "sticker.h"
#include <iostream>


Sticker::Sticker(Message* p, int xp, int yp, string mesg, string col) :
    x(xp), y(yp), text(mesg), parent(p), culoare(col)
{
}

void Sticker::Afiseaza()
{
    cout << "(" << x << ", " << y << ")"
        << culoare << " " << text << endl;
    for (auto it = msg.begin(); it != msg.end(); ++it)
    {
        cout << (*it)->GetContent() << endl;
    }
}

void Sticker::Attach(Message* el)
{
    if (el == NULL) return;
    msg.push_back(el);
}

int Sticker::GetX()
{
    return x;
}
int Sticker::GetY()
{
    return y;
}

string Sticker::GetContent()
{
    return text;
}

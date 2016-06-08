#include "whiteboard.h"
#include <iostream>

using namespace std;

WhiteBoard::WhiteBoard(Message* p, int xp, int yp, string mesg, string col) :
    x(xp), y(yp), parent(p), text(mesg), culoare(col)
{
}
void WhiteBoard::Afiseaza()
{
    cout << "(" << GetX() << "," 
        << GetY() << ") "  << culoare << " " << GetContent() << endl;
    for (auto it = msg.begin(); it != msg.end(); ++it)
        cout << (*it)->GetContent() << endl;
}


void WhiteBoard::Attach(Message* el)
{
    if (el == NULL)
        return;
    msg.push_back(el);
}

int WhiteBoard::GetX()
{
    return x;
}

int WhiteBoard::GetY()
{
    return y;
}

string WhiteBoard::GetContent()
{
    return text;
}



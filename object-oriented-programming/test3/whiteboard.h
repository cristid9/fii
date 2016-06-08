#ifndef WHITEBOARD_H__
#define WHITEBOARD_H__

#include "message.h"
#include <vector>

using namespace std;

class WhiteBoard : public Message
{
private:
    int x, y;
    string text, culoare;
    vector<Message*> msg;
    Message*  parent;
public:
    WhiteBoard(Message* p, int xp, int yp, string mesg, string col);

    void Afiseaza();
    void Attach(Message*);
    int GetX();
    int GetY();
    
    string GetContent();
};


#endif

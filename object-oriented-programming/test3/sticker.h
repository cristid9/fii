#ifndef STICKER_H__
#define STICKER_H__

#include "message.h"
#include <vector>

class Sticker : public Message
{
private:
    int x, y;
    string text, culoare;
    vector<Message*> msg;
    Message* parent;
public:
    Sticker(Message* p, int xp, int yp, string mesg, string col) ;
    void Afiseaza();
    
    
    void Attach(Message* );
    int GetX();
    int GetY();
    string GetContent();
};


#endif 

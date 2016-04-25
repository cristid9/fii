#include "Agenda.h"

Contancte& Agenda::findByName(string name)
{
    for (auto it = conts.begin(); it != conts.end(); it++)
    {
        if (it->name == name)
        {
            return *it;
        }
    }

    throw "not found";
}

vector<Contancte> Agenda::getFriendList()
{
    return conts;
}

void Agenda::deleteFriend(string name)
{
    for (auto it = conts.begin(); it != conts.end(); it++)
    {
        if (it->name == name)
        {
            conts.erase(it);
            return;
        }
    }
}

void Agenda::add(Contancte newContact)
{
    conts.push_back(newContact);
}



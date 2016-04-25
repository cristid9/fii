#ifndef Agenda_h
#define Agenda_h

#include <vector>
#include <string>
#include "Contancte.h"

using namespace std;


class Agenda {
private:
    vector<Contancte> conts;

public:

    Contancte& findByName(string name);

    vector<Contancte> getFriendList();

    void deleteFriend(string name);

    void add(Contancte newContact);

};

#endif // Agenda_h

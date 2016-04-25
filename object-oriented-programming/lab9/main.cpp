#include <iostream>
#include "Agenda.h"
#include "Coleg.h"

using namespace std;

int main()
{
    Agenda a;

    Coleg newCollegue;
    newCollegue.name = "Morena";

    a.add(newCollegue);

    vector<Contancte> col = a.getFriendList();

    for (auto it = col.begin(); it != col.end(); it++ )
    {
        cout << (it)->name << endl;
    }

    return 0;
}

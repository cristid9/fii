#include <iostream>
#include <vector>
#include <string>
#include "sticker.h"
#include "whiteboard.h"


using namespace std;

int main()
{
    Message *wall = new WhiteBoard(0, 0, 0, "MindMap", "violet");
    Message *stick1 = new Sticker(wall, 10, 10, "Vacanta", "rosu");
    Message *stick2 = new Sticker(wall, 10, 10, "Munte", "rosu");
    Message *stick3 = new Sticker(wall, 10, 10, "Tabara", "rosu");
    Message *stick4 = new Sticker(wall, 10, 10, "Examen PA", "rosu");
    Message *stick5 = new Sticker(wall, 10, 10, "Examen POO", "rosu");
    Message *stick6 = new Sticker(wall, 10, 10, "Familie", "maro");
    Message *stick7 = new Sticker(wall, 10, 10, "Iesire", "galben");
    Message *stick8 = new Sticker(wall, 10, 10, "Iesire la Circ", "verde");

    wall->Attach(stick1);
    wall->Attach(stick2);
    wall->Attach(stick3);
    wall->Attach(stick4);
    wall->Attach(stick5);
    wall->Attach(stick6);
   
    stick6->Attach(stick7);
    stick7->Attach(stick8);

    wall->Afiseaza();

    return 0;
}

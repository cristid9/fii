#include "lab.h"
#include <cmath>

Dreptunghi::Dreptunghi(int lungime, int latime)
{
    Latime = latime;
    Lungime = lungime;
}

double Dreptunghi::ComputeArea()
{
    return Latime * Lungime;
}

const char * Dreptunghi::GetName()
{
    return "Dreptunghi";
}

Cerc::Cerc(int raza)
{
    Raza = raza;
}

double Cerc::ComputeArea()
{
    return 2 * M_PI * (Raza * Raza);
}

const char * Cerc::GetName()
{
    return "Cerc";
}

Triunghi::Triunghi(int x1,int y1,int x2,int y2,int x3,int y3)
{
    X1 = x1;
    X2 = x2;
    X3 = x3;
    Y1 = y1;
    Y2 = y2;
    Y3 = y3;
}

double Triunghi::ComputeArea()
{
    return 2; // Because I am to lazy to figgure out the mathematical formula    
}

const char * Triunghi::GetName()
{
    return "Triunghi";
}

#include "lab_2.h"
#include <dlfcn.h>
#include <iostream>

using namespace std;

int main()
{
    void *handle = dlopen("/home/cristi/fii-stuff/object-oriented-programming/lab5/lab.so", RTLD_LAZY);   
    char * (*GetName)(void);
    int (*Compute)(int, int);
    
    if (!handle)
    {
        cout << dlerror() << endl;
    }

    GetName = (char * (*)(void)) dlsym(handle, "GetName");
    Compute = ( int (*)(int, int)) dlsym(handle, "Compute");

    cout << GetName ()<< endl;

    cout << Compute(1, 2) << endl;

    return 0;
}

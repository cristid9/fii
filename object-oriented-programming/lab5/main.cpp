#include "lab.h"
#include <vector>
#include <dlfcn.h>

using namespace std;

int main()
{
    void *handle = dlopen("lab.so", RTLD_LAZY);   
    char * (*constructor)(int, int) = dlsym(handle, "Dreptunghi");
    Forma *f = constructor(1, 2);
    
    /*
    vector<Forma*> forme;
    
    int i = 0;
    for (auto it = forme.begin(); it != forme.end(); it++, i++)
    {
        if (i % 3 == 0)
        {
            (*it) = new Dreptunghi(1, 2);
        }
        else if (i % 3 == 1)
        {
            (*it) = new Cerc(1);
        }
        else
        {
            (*it) = new Triunghi(1, 1, 2, 2, 3, 3);
        }
    }
*/
    return 0;
}

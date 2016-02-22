#include <iostream>
#include "int_list.h"

using std::cout;
using std::endl;

int main()
{
    // test the constructor
    {
        IntList* list = new IntList();
        if (list->GetCount() != 0)
        {
            cout << "GetCount doesn't works" << endl;
            return 1;
        }
    }

    // test Insert method
    {
        IntList* list = new IntList();
        list->Add(1);
        list->Add(2);
        list->Add(3);
        list->Add(4);

        int retVal = list->Insert(2, 45);

        int expectedForm[] = {1, 2, 45, 3, 4};
        for (int i = 0; i < 5; i++)
        {
            if (expectedForm[i] != list->Get(i))
            {
                cout << "Insert doesn't work" << endl;
                return 1;
            }
        }

        if (!retVal)
        {
            cout << "Insert doesn't work" << endl;
            return 1;
        }
    }

    // test Delete method
    {
        IntList* list = new IntList();
        list->Add(1);
        list->Add(2);
        list->Add(3);
        list->Add(4);
        list->Add(5);

        int retVal = list->Delete(2);
        int expectedForm[] = {1, 2, 4, 5};

        if (!retVal)
        {
            cout << "Delete doesn't work" << endl;
            return 1;
        }
    
        for (int i = 0; i < 4; i++)
        {
            if (expectedForm[i] != list->Get(i))
            {
                cout << "Delete doesn't work" << endl;
                return 1;
            }
        }
    }

    // test 
    {
        IntList* list = new IntList();
    }

    return 0;
}


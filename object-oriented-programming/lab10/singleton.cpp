#include <unistd.h>
#include <thread>
#include <fstream>
#include <iostream>

using namespace std;

class SingletonSemaphore
{
    private:
        static SingletonSemaphore* _instance;
        static int count;
        static bool access;
        const static int treshold = 6; // cai frumosi

    public:
        static SingletonSemaphore* getInstance()
        {
            if (count == treshold)
            {
                return NULL;
            }

            if (_instance == NULL)
            {
                _instance = new SingletonSemaphore();
            }

            count++;

            return _instance;
        }

        bool getAccess() const
        {
            return access;
        }

        void toggle()
        {
            access = access ? false : true;
        }
};

int SingletonSemaphore::count = 0;
SingletonSemaphore* SingletonSemaphore::_instance = NULL;
bool SingletonSemaphore::access = true;

void task1()
{
    SingletonSemaphore* s = SingletonSemaphore::getInstance();
    if (s == NULL)
        return;
    
    int writes = 20;

    while (writes--)
    {
        usleep(rand() % 1000);
        
        while (!s->getAccess())
            ;

        s->toggle();

        fstream fout;
        fout.open("test.txt", std::ios_base::app);
        fout << "[ thread 1 ]" << endl;
        s->toggle();

    }    
}

void task2()
{
    SingletonSemaphore* s = SingletonSemaphore::getInstance();
    if (s == NULL)
        return;

    int writes = 20;

    while (writes--)
    {
        usleep(rand() % 1000);
        while (!s->getAccess())
            ;

        s->toggle();

        fstream fout;
        fout.open("test.txt", std::ios_base::app);
        fout << "[ thread 2 ]" << endl;
        s->toggle();
    }
}

int main()
{
    SingletonSemaphore* s = SingletonSemaphore::getInstance();
    
    thread t1 = thread(task1);
    thread t2 = thread(task2);

    t1.join();
    t2.join();

    return 0;
}

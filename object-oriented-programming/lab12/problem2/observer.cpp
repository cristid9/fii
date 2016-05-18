#include <iostream>
#include <sys/time.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Observer
{
    public:
        virtual void notify(int index, int prime, double tm) = 0;

};

class TerminalObserver : public Observer
{
    public:
        TerminalObserver()
        {
        }

        virtual void notify(int index, int prime, double tm)
        {
            cout << index << " " << prime << " " << tm << endl;
        }
};

class HTMLObserver : public Observer
{
    private:
        string filename;
        string header;
        string body;
        string footer;

    public:
        HTMLObserver(string file)
        {
            filename = file;
            ofstream out(filename);

            header  = "<html>\n";
            header  += "<head> <title> HTMLObserver </title> </head>";
            header  +=  "<body>\n";
            header  +=     "<script type=\"text/javascript\">\n";
            header  +=        "window.setTimeout(function() {\n";
            header  +=           "document.location.reload(true); }, 5000);";
            header  +=      "</script>\n";
            
            body    = "";    
                 
            footer  =   "</body></html>\n";
            
            out << header << body << footer;
            out.close();
        }

        virtual void notify(int index, int prime, double tm)
        {
            ofstream out(filename);
            
            string tmp = "";
            tmp += to_string(index);
            tmp += " ";
            tmp += to_string(prime);
            tmp += " ";
            tmp += to_string(tm);
            tmp += "<br/>\n";
          
            body += tmp;

            out << header << body << footer << endl;
            out.close();
        }

};


class FileObserver : public Observer
{
    private:
        string filename;

    public:
        FileObserver(string file)
        {
            filename = file;
        }

        virtual void notify(int index, int prime, double tm)
        {
            ofstream out(filename);
            
            out << index << " " << prime << " " << tm << endl; 

            out.close();
        }
};


class Worker
{
    private:
        vector<Observer*> observers;
        double secondsStart;
        double lastCheck;

        bool isPrime(int number)
        {
            for (int i = 2; i < number; i++)
            {
                if (i % number == 0)
                    return false;
            }

            return true;
        }

    public:

        Worker()
        {
            struct timeval t1;
            gettimeofday(&t1, NULL);
            secondsStart = t1.tv_sec;
        }

        void addObserver(Observer *obv)
        {
            observers.push_back(obv);
        }

        void computePrimes(int limit)
        {
            int index = 0;
            for (int i = 2; i < limit; ++i)
            {
                struct timeval t1;
                gettimeofday(&t1, NULL);
                double secs = t1.tv_sec;
                
                if (secs - lastCheck > 0.0001)
                {
                    if (isPrime(i))
                    {
                        for (auto it = observers.begin(); 
                                it != observers.end(); it++)
                        {
                           (*it)->notify(index, i, secs - secondsStart);
                        }
                    }
                    index++;
                }

                lastCheck = secs;
            }
        }
        
};

int main()
{
    
    Worker wk;
    HTMLObserver     *ho = new HTMLObserver("_index.html");
    TerminalObserver *to = new TerminalObserver();
    FileObserver     *fo = new FileObserver("primes.log");

    wk.addObserver(ho);
    wk.addObserver(to);
    wk.addObserver(fo);

    wk.computePrimes(1000000000);
    
    return 0;
}


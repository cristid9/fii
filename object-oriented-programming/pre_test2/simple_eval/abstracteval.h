#include <string>

using namespace std;

class AbstractEval
{
    public:
        //[1p] returneaza expresia
        virtual string GetExpression() = 0;
        //
        //      //[6p] - seteaza noua expresie pentru evaluare. Returneaza false daca expresia nu este valida
        virtual bool SetExpression(const char *expre) = 0; 
        //
        //              //[2p] - returneaza numarul de operatori de un anumit tip folositi in expresie sau 0 daca operatorul nu e folosit
        virtual int GetOperatorCount(char my_operator) = 0;
        //                      
        //                          //[3p] - returneaza un string cu operatorii utilizati
        virtual string GetOperatorsList() = 0;
        //
        //                                  //[9p] - returneaza rezultatul evaluarii
        virtual int Evaluate() = 0;
};


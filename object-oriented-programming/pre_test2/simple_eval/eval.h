#ifndef EVAL_H__
#define EVAL_H__

#include "abstracteval.h"
#include <string>

using namespace std;

class Eval : public AbstractEval
{
    private:
        string expression;

    public:    
        Eval();
        
        
        string GetExpression();
        // 6p] - seteaza noua expresie pentru evaluare. Returneaza false daca expresia nu este valida
        bool SetExpression(const char *expre); 
        // [2p] - returneaza numarul de operatori de un anumit tip folositi in expresie sau 0 daca operatorul nu e folosit
        int GetOperatorCount(char my_operator);
        //                          //[3p] - returneaza un string cu operatorii utilizati
        string GetOperatorsList();
        //                                  //[9p] - returneaza rezultatul evaluarii
        int Evaluate();
};

#endif

#ifndef CONTROLLER_
#define CONTROLLER_
#include <iostream>
#include <vector>
#include <string>
#include "Packager_.h"
#include "Execute_.h"
#include "Package_.h"

using namespace std;

class Controller{
   
    string input;
    char masterIndicator;
    string semiString;
    Packager parse;
    Execute executer;
    
    public:
       string receiveInput();
       void displayInput();
       bool receiveAndRun(string);
       char seekOp();
       string clearOp(string);
       bool runParen();
       bool semiParse(string);
       bool execParen(string);
       
};

#endif

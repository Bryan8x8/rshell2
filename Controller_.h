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
    Packager parse;
    Execute executer;
    
    public:
       void receiveInput();
       void displayInput();
       bool receiveAndRun();
};

#endif

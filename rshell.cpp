#include <iostream>
#include <vector>
#include <string>
#include "Packager_.cpp"
#include "Execute_.cpp"
#include "Controller_.cpp"
#include "Package_.cpp"


using namespace std;

int main() {
    Controller control;
    Packager parse;
    bool breakLoop = false;
    std::cout << "Welcome to rshell, enter command 'terminate' to end your session." << std::endl;
    string holdInput;
    while(!breakLoop){
    std::cout<<"$";
    holdInput = control.receiveInput();
    if(!parse.detectParen(holdInput))
    {
    breakLoop = control.receiveAndRun(holdInput); 
    }
    else
    {
        control.execParen(holdInput);
    }
    }
  
    
    
    return 0;
}

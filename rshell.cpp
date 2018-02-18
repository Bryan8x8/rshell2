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
    bool breakLoop = false;
    std::cout << "Welcome to rshell, enter command 'terminate' to end your session." << std::endl;
    while(!breakLoop){
    breakLoop = control.receiveAndRun(); 
    }          
    return 0;
}

#include "Controller_.h"

using namespace std;

void Controller::receiveInput()
{
     getline(cin,input);
};

void Controller::displayInput()
{
    std::cout << input << std::endl;
};

bool Controller::receiveAndRun()
{
    cout <<"$ ";
    bool terminateBool = false;
    receiveInput(); //asking for user input;

    parse.commandParse(input);
    parse.packageCommands(); //input has been packaged
    executer.receivePackage(parse.returnPackageVector()); //package vector has been received by executer
    terminateBool = executer.executePackage(); //package is being executed
    return terminateBool;
};

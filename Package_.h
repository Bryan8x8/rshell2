#ifndef PACKAGE_
#define PACKAGE_
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Package{ 
    
    public:  
    
    char getLogic(int);
    string getCommands(int);
    vector<char> getLogicVec();
    vector<string> getCommandVec();
    void prepareArgVec(vector<string>);
    void addCommand(string);
    void addLogic(char);
    void getVecSizes();
    void printContents();
    
    protected:
        
    vector<char> logic;
    vector<string> commands;
};


#endif 

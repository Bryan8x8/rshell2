#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Package class contains all relevant information that the executer will need in order to process a command
class Package {
    vector<char> logic;
    vector<string> commands;
public: 
    //using default constructor, package()
    // 'get' functions return a specified position of the vectors
    char getLogic(int);
    string getCommands(int);
    vector<char> getLogicVec();
    vector<string> getCommandVec();
    // 'add' functions allow user to add inputs to package vectors
    void addCommand(string);
    void addLogic(char);
    void getVecSizes();
};

char Package::getLogic(int position){
    return logic[position];
};

string Package::getCommands(int position){
    return commands[position];
};

void Package::addCommand(string input){
    commands.push_back(input);
};

void Package::addLogic(char input){
    logic.push_back(input);
};

void Package::getVecSizes(){ //function built for testing and debugging purposes
    std::cout <<"Vector Sizes:" << std::endl;
    std::cout<<"logic vector size: " << logic.size() << std::endl;
    std::cout<<"commands vector size: " << commands.size() << std::endl;

};
vector<string> Package::getCommandVec(){
    return commands;
};
vector<char> Package::getLogicVec(){
    return logic;
};





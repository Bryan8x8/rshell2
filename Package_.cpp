#include "Package_.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

void Package::printContents(){
    std::cout << "Printing out logic vec contents: " << std::endl;
    for(int i = 0; i < logic.size(); i++){
        std::cout << logic[i] << std::endl;
    }
    std::cout << "Printing out command vec contents: " << std::endl;
    for(int i = 0; i < commands.size(); i++){
        std::cout << commands[i] << std::endl;
    }
};


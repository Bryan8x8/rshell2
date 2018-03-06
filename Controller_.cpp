#include "Controller_.h"

using namespace std;

string Controller::receiveInput()
{
     getline(cin,input);
     return input;
};

void Controller::displayInput()
{
    std::cout << input << std::endl;
};

bool Controller::receiveAndRun(string input1)
{
    //cout <<"$ ";
    string tempString;
    int strLen = input.length();
    int endSplit;
    bool terminateBool = false;
    bool parenBool = false;
    //receiveInput(); //asking for user input;
    //parenBool = parse.detectParen(input1);
    parse.commandParse(input1);
    parse.packageCommands(); //input has been packaged
    executer.receivePackage(parse.returnPackageVector()); //package vector has been received by executer
    terminateBool = executer.executePackage(); //package is being executed
    return terminateBool;
    
};

char Controller::seekOp(){
    bool breakBool = false;
    char indicator = 'e';
    int i = 0;
    while((i < semiString.length()) && (!breakBool) && (semiString.length() != 0))
    {
        if((semiString[i] == '&')&&(semiString[i+1] == '&'))
        {
           // cout << "hit & , current working string: " << input1 << endl;
            //cout << i+1 << endl;
            //cout << (input1.length()-(i+2)) << endl;
            //cout <<"hit indic"<<endl;
            breakBool = true;
            semiString = semiString.substr(i+2, (semiString.length()-(i))); //removing operators from string
            indicator = '&';
            return indicator;
            //cout << input1 <<endl;
            
        }
        if((semiString[i] == '|')&&(semiString[i+1] == '|'))
        {
            breakBool = true;
            semiString = semiString.substr(i, semiString.length()-2); //removing operators from string
            indicator = '|';
            return indicator;
        }
        i++;
    }
    //cout << "seekOp return: " << indicator <<endl;
    return indicator;
};

string Controller::clearOp(string input1){
    bool breakBool = false;
    char indicator = 'e';
    int i = 0;
    while((i < input1.length()) && (!breakBool) && (input1.length() != 0))
    {
        if((input1[i] == '&')&&(input1[i+1] == '&'))
        {
            //cout << "hit & , current working string: " << input1 << endl;
            //cout << i+1 << endl;
            //cout << (input1.length()-(i+2)) << endl;
            breakBool = true;
            input1 = input1.substr(i+2, (input1.length()-(i))); //removing operators from string
            indicator = '&';
            //cout << input1 <<endl;
            
        }
        if((input[i] == '|')&&(input[i+1] == '|'))
        {
            breakBool = true;
            input1 = input1.substr(i, input1.length()-2); //removing operators from string
            indicator = '|';
        }
        i++;
    }
    return input1;
};

bool Controller::runParen()
{
    cout << semiString << "mark1" << endl;
    semiString = parse.removeWhiteSpace(semiString); //any initial whitepace removed
    cout << semiString << "mark2" << endl;
    string tempString;
    int strLen = semiString.length();
    int endSplit;
    bool testBool;
    bool operate;
    char opChar;
    tempString = parse.parenCmdParse(semiString);
    cout << semiString << "mark3" << endl;
    cout << tempString << endl;
    //std::cout<< "parens have been parsed out:" << tempString << std::endl;
    semiString = semiString.substr(tempString.length(), semiString.length()-tempString.length()); //this removes the processed string
    //parse.commandParse(tempString); //temp string containing a single command is packaged.
    if(tempString.length() != 0) //detects if single command is present, if so it is packaged and executed.
    {
        //we have entered into the single commands area now we must continue to search for single commands
        testBool = executer.executeSingle(tempString);
        cout << "paren hit" << endl;
        while (semiString.length() != 1)
        {
           //cout << "error test, displaying working string: " << input1 << endl;

            opChar = seekOp();
            //cout << input1 << endl;
            //input1 = clearOp(input1);
            //cout << input1 << endl;
            semiString = parse.removeWhiteSpace(semiString); //found operators and removed whitespace, we can again begin to 
            //cout << input1 << endl;
            semiString = parse.parenCmdParse(semiString);
            semiString = semiString.substr(tempString.length(), semiString.length()-tempString.length()); //this removes the processed string
            cout << "input: " << semiString << endl;
            cout << "testBool: " << testBool << "  OpChar: " << opChar << endl;
            if (((testBool == 1) && (opChar == '&')) || ((testBool == 0) && (opChar == '|'))) 
            {
                cout<<  "Bool Hit" << endl;
                cout << tempString << endl;

                testBool = executer.executeSingle(tempString);
            }
        }
        
    }
    //cout<< "we have exited single commands, input is currently: " << input1 << " with size: " << input1.length() <<endl;
    //we have handled all available sigle commands
    //we will handle the whole paren in here.
    tempString = parse.parseParen(semiString); //we are checking to see if we have find any parenthesis
    //cout << "error happens here" << endl;
    semiString = semiString.substr(tempString.length(), semiString.length() - tempString.length()); //this removes the processed string
    //cout << tempString << endl;
    if(tempString.length() != 0)
    {
        //cout<<"hit"<<endl;
        bool testBool = runParen(); //recursion will handle whatever is inside the parenthesis and return a bool result.
    }
    
};

bool Controller::semiParse(string input1)
{
    bool semiHit = false;
    bool inputEnd = false;
    int i =0;
    while (!semiHit)
    {
        //std::cout<< "semiparse loop hit"<<std::endl;
        if(input1[i] == ';')
        {
            //std::cout<< "building first semi"<<std::endl;
            semiHit = true;
            semiString = input.substr(0, i-1);
            input = input.substr(0, (input.length()-1)); //note we are parsing input for future semi parses
        }
       
        if(i==input1.length())
        {
            //std::cout<<"loop broken"<<std::endl;
            semiHit = true; //this is to end the loop
            inputEnd = true; //input has ended
            semiString = input1;
        }
        i++;
    }
    return inputEnd;
};

bool Controller::execParen(string input1)
{
    //receiveInput(); this is handled in rshell.
    bool inputEnd;
    while(!inputEnd)
    {
    //std::cout<<"exec Parenloop hit"<< std::endl;
    inputEnd = semiParse(input1);
    //std::cout<<"finished semiParse"<< std::endl;
    //std::cout << semiString << std::endl;
    masterIndicator = 'e';
    runParen();
    }
    inputEnd = true;
};

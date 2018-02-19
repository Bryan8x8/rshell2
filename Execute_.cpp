#include "Execute_.h"

using namespace std;

void Execute::receivePackage(vector<Package> inputPack){
    holdPackages = inputPack;
};

void Execute::unpack(Package currentPack){
    holdCommands = currentPack.getCommandVec();
    holdLogic = currentPack.getLogicVec();
};

bool Execute::executeCommands(){
    bool tempBool = true;
    char tempChar = 't';
    //building pipe
    int mypipefd[2];
    int ret;
    char buf[20];
    ret = pipe(mypipefd);
    if(ret == 1){
        perror("pipe");
        exit(1);
    }
    //forking:
    pid_t pid=fork();
    if (pid==0)
    { /* child process */
            //std::cout << "Hit Exec" << std::endl;
            execvp(execArgs[0], (char**)execArgs);

            write(mypipefd[1], "f", 12);
            close(mypipefd[0]);
            exit(127); /* only if execv fails */
    }
    else
    { /* pid!=0; parent process */
        waitpid(pid,0,0); 
        close(mypipefd[1]);
        read(mypipefd[0], buf, 15);
        tempChar = buf[0];
        //std::cout<< "tempChar:" << buf[0] << std::endl;
        if(tempChar == 'f')
        {
            tempBool = false;
        }
    }
    return tempBool;
};
    
void Execute::loadConstChar()
{
    for(int i = 0; i < executionVec.size(); i++ ){
        execArgs[i] = executionVec[i].c_str();
    }
    execArgs[executionVec.size()] = NULL;

};

vector<Package> Execute::returnPackageVector(){
    return holdPackages;
};

void Execute::printContents(){
    std::cout << "Printing out logic vec contents: " << std::endl;
    for(int i = 0; i < holdLogic.size(); i++){
        std::cout << holdLogic[i] << std::endl;
    }
    std::cout << "Printing out command vec contents: " << std::endl;
    for(int i = 0; i < holdCommands.size(); i++){
        std::cout << holdCommands[i] << std::endl;
    }
};

bool Execute::createArgVec (string input){
    vector<string> execArr;
    bool exitBool = false;
    int startSplit;
    int endSplit;
    int j = 0;
    string subString;
    for(int i=0; i<input.length(); i++){
        if(!isspace(input[i])&& ((input[i] != '\'') && (input[i] != '"'))){
            startSplit = i;
            i++;
            while(((!isspace(input[i])) && (i < input.length()))){
                i++;
            }
            endSplit = i - startSplit;
            subString = input.substr(startSplit, endSplit);
            //std::cout << "Loading Command: " << subString << std::endl;
            execArr.push_back(subString);
            startSplit = i+1;
            j++;
        }
        if((input[i] == '"') || (input[i] == '\'')){
            //std::cout<<"Is there something here" << std::endl;
            startSplit = i+1;
            i++;
            while((input[i] != '"') && (input[i] != '\''))
            {
                i++;
            }
            endSplit = i - startSplit;
            subString = input.substr(startSplit, endSplit);
            execArr.push_back(subString);
            startSplit = i+1;
            j++;
        }
        if(subString == "terminate")
        {
            exitBool = true;
        }
    }
    
    executionVec = execArr;
    return exitBool; 
};

string Execute::returnCommand(int input){
  return holdCommands[input];  
};

bool Execute::executePackage(){
    bool exitBool = false;
    for(int i = 0; i < holdPackages.size(); i++){
        unpack(holdPackages[i]); //current package is being unpacked and holdCommand and holdLogic are being populated with current package vectors
        if(holdLogic.size() == 0 && !exitBool) //there is no logic, the package is a single command, execute it.
        {
            exitBool = createArgVec(holdCommands[0]);
            if(exitBool){ 
             i = holdPackages.size(); 
             exitBool = true;
            }
            loadConstChar();
            executeCommands();    
            //cout<<i<<endl;
        }
        if(holdLogic.size() != 0 && !exitBool)
        {
            bool checkBool;
            exitBool = createArgVec(holdCommands[0]);
            if(exitBool){ 
             i = holdPackages.size();  
             exitBool = true;
            }
            loadConstChar();
            checkBool = executeCommands(); //first command in the vector has been executed, and bool is loaded indicating whether the first command failed or succeeded.
            if(!exitBool){
                for(int k = 1; k < holdCommands.size(); k++)
                {
                    if(checkBool && holdLogic[k-1] == '&')
                    {
                    exitBool = createArgVec(holdCommands[k]);
                    if(exitBool){ 
                        k = holdCommands.size(); 
                        exitBool = true;
                    }
                    loadConstChar();
                    checkBool = executeCommands(); 
                    }
                    if(!checkBool && holdLogic[k-1] == '|')
                    {
                    exitBool = createArgVec(holdCommands[k]);
                    if(exitBool){ 
                        k = holdCommands.size(); 
                        exitBool = true;
                    }
                    loadConstChar();
                    checkBool = executeCommands();    
                    }
                }
            }
        }
    }
    return exitBool;
};

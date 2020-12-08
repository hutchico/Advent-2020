#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main()
{
    std::ifstream file;
    std::stringstream ss;
    vector<string> commands;
    vector<int> runCount;
    string buffer;
    int acc = 0;
    int next_instruction = 0;
    int current_instruction = 0;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        commands.push_back(buffer);
    }
    runCount.resize(commands.size(),0);
    //cout << commands[0];
    while(true){
        //Run current command
        current_instruction = next_instruction;
        cout << current_instruction << " " << commands[current_instruction][0] << " " << commands[current_instruction][4] << endl;
        std::stringstream().swap(ss); //Reset stream
        ss.str(commands[current_instruction]);
        if(commands[current_instruction][0] == 'a'){ //Acc
            next_instruction = current_instruction + 1;
            if(commands[current_instruction][4] == '-'){
                getline(ss,buffer,'-');
                getline(ss,buffer);
                acc -= stoi(buffer);
            }
            else{
                getline(ss,buffer,'+');
                getline(ss,buffer);
                acc += stoi(buffer);
            }
            runCount[current_instruction]++;
            next_instruction = current_instruction + 1;
        }
        else if(commands[current_instruction][0] == 'j'){ //Jmp
            if(commands[current_instruction][4] == '-'){
                getline(ss,buffer,'-');
                getline(ss,buffer);
                next_instruction = current_instruction - stoi(buffer);
                runCount[current_instruction]++;
            }
            else{
                getline(ss,buffer,'+');
                getline(ss,buffer);
                next_instruction = current_instruction + stoi(buffer);
                runCount[current_instruction]++;
            }
        }
        else{   //Nop
            next_instruction = current_instruction + 1;
        }


        if(runCount[next_instruction] == 1){    //The next instruction to be run is going to be the duplicate we are looking for
            cout << acc << endl;
            break;
        }
    }

    return 0;
}

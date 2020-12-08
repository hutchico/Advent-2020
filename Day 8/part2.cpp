#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

struct contents{
    string instruction;
    char relative;
    int value;
};

struct node{
    int order;
    bool visited;
    contents code;
    node * next; //The node this points to next per its instructions
    vector<node*> previous; //List of all nodes that point to this one
    vector<node*> anomalies; //List of nodes which would point here were their instructions reversed
};

bool traverse(vector<node> commands){
    vector<node> tree = commands;
    int current_instr = 0;
    int next_instr = 0;
    int acc = 0;
    while(true){
        if(tree[next_instr].visited){
            return false;
        }

        if(next_instr > commands.size() - 2){
            cout << "Acc value: " << acc << endl;
            return true;
        }
        current_instr = next_instr;
        if(tree[current_instr].code.instruction == "jmp"){ //jmp
            if(tree[current_instr].code.relative == '-')
                next_instr = current_instr - tree[current_instr].code.value;
            else
                next_instr = current_instr + tree[current_instr].code.value;
        }
        else if(tree[current_instr].code.instruction == "acc"){ //acc
            if(tree[current_instr].code.relative == '-')
                acc -= tree[current_instr].code.value;
            else
                acc += tree[current_instr].code.value;
            next_instr = current_instr + 1;
        }
        else{ //nop
            next_instr = current_instr + 1;
        }
        tree[current_instr].visited = true;
    }
    return false;
}

int main()
{
    std::ifstream file;
    std::stringstream ss;
    vector<node> commands;
    vector<node> testChange;
    string buffer;
    contents input;
    node tree;
    int relValue = 0;
    int lines = 1;
    //Parse all commands
    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        tree.visited = false;
        tree.order = lines;
        ss.str(buffer);
        input.relative = buffer[4];
        getline(ss,buffer,' ');
        input.instruction = buffer;
        getline(ss,buffer);
        relValue = stoi(buffer);
        if(relValue <= 0) //relValue could be negative due to the way input is parsed
            input.value = -1 * relValue;
        else
            input.value = relValue;
        tree.code = input;
        commands.push_back(tree);
        std::stringstream().swap(ss);
        lines++;
    }
    //Assign nextdirection markers to each node
    for(int i = 0; i < commands.size(); i++){
        if(commands[i].code.instruction == "jmp"){  //Next line for jmp instructions is relative to itself
            if(commands[i].code.relative == '-'){
                commands[i].next = &commands[i-commands[i].code.value];
            }
            else
                commands[i].next = &commands[i+commands[i].code.value];
        }
        else{   //acc and nop instructions just point to the next line
            commands[i].next = &commands[i+1];
        }
    }
    //Determine all nodes that point to a given node
    for(int i = 0; i < commands.size(); i++){
        for(int j = 0; j < commands.size(); j++)
            if(i == j)
                continue;
            else{
                if(&commands[i] == commands[j].next) //If the given node is pointed to by the checked node
                    commands[i].previous.push_back(&commands[j]); //add pointer to this checked node to vector
            }
    }

    //Anomalies: Examine nodes that would point somewhere else were their instruction reversed
    for(int i = 0; i < commands.size(); i++){
        if(commands[i].code.instruction == "jmp"){  //Pretend this is a nop instruction
            commands[i+1].anomalies.push_back(&commands[i]);
        }
        else if (commands[i].code.instruction == "nop"){   //Pretend this is a jmp instruction
            if(commands[i].code.relative == '-'){
                commands[i-commands[i].code.value].anomalies.push_back(&commands[i]);
            }
            else
                commands[i+commands[i].code.value].anomalies.push_back(&commands[i]);
        }
    }
/*
    //Verify contents of each node
    for(int i = 0; i < commands.size(); i++){
            cout << i + 1 << " " << commands[i].code.instruction << " " << commands[i].code.relative << commands[i].code.value << " " << commands[i].anomalies.size() << endl;
    }

    //Traversal: Attempt to execute the program, stopping when it begins to loop
    cout << traverse(commands);
*/
    //Bruteforce solution because screwit
    for(int i = 0; i < commands.size(); i++){
        testChange = commands;
        if(testChange[i].code.instruction == "acc") //If it's an acc instruction don't touch it
            continue;
        else if(testChange[i].code.instruction == "jmp"){ //swap this jmp instruction to nop
            testChange[i].code.instruction = "nop";
        }
        else{
            testChange[i].code.instruction = "jmp"; //swap this nop instruction to jmp
        }
        if(traverse(testChange)){
            cout << "Run successful! Line changed: " << i + 1 << endl;
            break;
        }
    }


    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Rule{
    int ruleMin;
    int ruleMax;
    char target;
    std::string entry;
};

bool isValidP1(Rule toCheck){
    int occurence = 0;
    char target = toCheck.target;
    std::string toScan = toCheck.entry;
    for(int i = 0; i < toCheck.entry.length(); i++){
        if(toScan[i] == target)
            occurence++;
    }
    if(occurence <= toCheck.ruleMax && occurence >= toCheck.ruleMin)
        return true;
    else
        return false;
}

bool isValidP2(Rule toCheck){
    if(toCheck.entry[toCheck.ruleMin] == toCheck.target){
        if(toCheck.entry[toCheck.ruleMax] == toCheck.target)
            return false;
        else
            return true;
    }
    else if(toCheck.entry[toCheck.ruleMax] == toCheck.target)
        return true;
    else
        return false;
}

int main()
{
    std::ifstream file;
    std::string buffer;
    std::vector<Rule> inputArr;
    Rule inputs;
    int valid = 0;

    file.open("input.txt");
    while(true){
        getline(file,buffer,'-');   //First number
        if(file.eof() == true)
            break;
        inputs.ruleMin = stoi(buffer);
        getline(file,buffer,' ');   //Second number
        inputs.ruleMax = stoi(buffer);
        getline(file,buffer,':');   //Character to scan for
        inputs.target = buffer[0];
        getline(file,buffer);       //Test string
        inputs.entry = buffer;
        inputArr.push_back(inputs);
    }

    for(int i = 0; i < inputArr.size(); i++){
        if(isValidP1(inputArr[i]))
            valid++;
    }
    std::cout << "valid part 1: " << valid << std::endl;

    valid = 0;  //Reset counter between runs

    for(int i = 0; i < inputArr.size(); i++){
        if(isValidP2(inputArr[i]))
            valid++;
    }
    std::cout << "valid part 2: " << valid << std::endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;

struct bag{
    string name;
    vector<int> contentsNo;
    vector<string> children;
};

//Turns out recursion isn't 100% necessary for part 1
int better_containsGold(vector<string> &names, vector<bag> inputs){
    for(int i = 0; i < names.size(); i++){
        for(int j = 0; j < inputs.size(); j++){
            for(int k = 0; k < inputs[j].children.size(); k++){
                if(inputs[j].children[k] == names[i]){
                    for(int l = 0; l < names.size(); l++){
                        if(inputs[j].name == names[l]){
                            break;
                        }
                        else if(l == names.size() - 1)
                            names.push_back(inputs[j].name);
                    }
                    break;
                }
            }
        }
    }
    return names.size();
}

bool containsGold(string target, vector<bag> inputs, int index){
    int calls_to_make = 0;
    int childIndex = 0;

    if(inputs[index].contentsNo.size() == 0){    //This bag is empty and is not shiny gold
        return false;                               //Shiny gold bags are not empty
    }

    calls_to_make = inputs[index].contentsNo.size();
    //This is the worst part of this code, runs the full list multiple times in every function call
    for(int i = 0; i < calls_to_make; i++){
        for(int j = 0; j < inputs.size(); j++){ //Find the index for target child bag
            if(inputs[j].name == inputs[index].children[i]){
                childIndex = j;
                break;
            }
        }
        if(inputs[index].children[i] == "shiny gold")
            return true;
        if(containsGold(inputs[index].children[i],inputs,childIndex))
            return true;
    }
    return false;
}

int goldContents(string target, vector<bag> inputs){
    int calls_to_make = 0;
    int index;
    int sum_contents = 0;
    for(int i = 0; i < inputs.size(); i++){ //Find the index for our target bag
        if(inputs[i].name == target){
            index = i;
            break;
        }
    }

    if(inputs[index].contentsNo.size() == 0){
        return 1;
    }

    calls_to_make = inputs[index].contentsNo.size();
    for(int i = 0; i < calls_to_make; i++){
        sum_contents += inputs[index].contentsNo[i] * goldContents(inputs[index].children[i],inputs);
    }
    return sum_contents + 1;    //The contents of the bag plus the bag itself
}

int main()
{
    std::fstream file;
    std::stringstream ss;
    vector<bag> rules;
    vector<string> contents;
    vector<string> containsShinyGold;
    struct bag input;
    string buffer;
    string bagname;
    int goldBags = 0;
    int goldIndex;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;

        ss.str(buffer);
        getline(ss,bagname,' '); //adjective
        getline(ss,buffer,' ');  //color
        bagname.append(" " + buffer);
        input.name = bagname;
        getline(ss,buffer,' '); //bags
        getline(ss,buffer,' '); //contain
        while(getline(ss,buffer,',')){
            contents.push_back(buffer);
        }
        for(int i = 0; i < contents.size(); i++){
            if(contents[i][0] == 'n'){
                break;
            }
            std::stringstream().swap(ss);   //Reset the stream object
            ss.str(contents[i]);
            if(i > 0)
                ss.ignore(1);
            getline(ss,buffer,' '); //integer
            input.contentsNo.push_back(stoi(buffer));
            getline(ss,bagname,' '); //adjective
            getline(ss,buffer,' '); //color
            bagname.append(" " + buffer);
            input.children.push_back(bagname);
        }
        rules.push_back(input);
        input.children.clear();
        input.contentsNo.clear();
        contents.clear();
        std::stringstream().swap(ss);
    }
    file.close();

    //Keep this commented, it's there for posterity but is worse than the later solution.
/*
    for(int i = 0; i < rules.size(); i++){
        cout << rules[i].name << endl;
        if(containsGold(rules[i].name,rules,i))
            goldBags++;
    }

    cout << goldBags << endl << endl;
*/

    //Second attempt is much better but works largely by accident.
    for(int i = 0; i < rules.size(); i++){
        for(int j = 0; j < rules[i].contentsNo.size(); j++){
            if(rules[i].children[j] == "shiny gold"){
                containsShinyGold.push_back(rules[i].name);
                break;
            }
        }
    }

    cout << better_containsGold(containsShinyGold,rules) << endl;

    for(int i = 0; i < rules.size(); i++){
        if(rules[i].name == "shiny gold"){
            goldIndex = i;
            break;
        }
    }

    for(int i = 0; i < rules[goldIndex].contentsNo.size(); i++){
        goldBags += rules[goldIndex].contentsNo[i] * goldContents(rules[goldIndex].children[i],rules);
    }
    cout << goldBags << endl;
}

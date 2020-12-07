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


//Future reference idea: Start at shiny gold, work outward.
bool containsGold(string target, vector<bag> inputs){
    int calls_to_make = 0;
    int index;
    for(int i = 0; i < inputs.size(); i++){ //Find the index for our target
        if(inputs[i].name == target){
            index = i;
            break;
        }
    }

    if(inputs[index].contentsNo.size() == 0){    //This bag is empty and is not shiny gold
        return false;                               //Shiny gold bags for my personal input set are not empty
    }

    calls_to_make = inputs[index].contentsNo.size();
    for(int i = 0; i < calls_to_make; i++){
        if(inputs[index].children[i] == "shiny gold")
            return true;
        if(containsGold(inputs[index].children[i],inputs))
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

    ///NOTE: This first function for part 1 takes approximately 2 minutes to run.
    ///It is incredibly inefficient! Keep commented unless verifying part 1.
    /*
    for(int i = 0; i < rules.size(); i++){
        if(containsGold(rules[i].name,rules))
            goldBags++;
    }

    cout << goldBags << endl << endl;
    */
    for(int i = 0; i < rules.size(); i++){
        if(rules[i].name == "shiny gold"){
            goldIndex = i;
            break;
        }
    }

    goldBags = 0;

    for(int i = 0; i < rules[goldIndex].contentsNo.size(); i++){
        goldBags += rules[goldIndex].contentsNo[i] * goldContents(rules[goldIndex].children[i],rules);
    }
    cout << goldBags << endl;
}

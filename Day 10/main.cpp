#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "merge.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::unordered_map;

struct node{
    int value;
    vector<node *> next;
    vector<node *> previous;
};

int main()
{
    vector<int> jolts;
    vector<node> adapters;
    node single;
    std::ifstream file;
    string buffer;
    unordered_map<int,long long> memo;
    int deviceRating;
    int oneDiff = 1;    //Start at 1 for the jump out of/into adapters
    int threeDiff = 1;
    bool found = false;


    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        jolts.push_back(stoi(buffer));
    }

    mergeSort(jolts,0,jolts.size()-1);

    deviceRating = jolts[jolts.size()-1] + 3;

    for(int i = 0; i < jolts.size(); i++){
        if(i == jolts.size()){  //Different procedure for the last element and the device
            break;
        }
        if(jolts[i+1] - jolts[i] == 1)
            oneDiff++;
        else if(jolts[i+1] - jolts[i] == 3)
            threeDiff++;
    }

    cout << oneDiff * threeDiff << endl;

    //Populate reference vector, then assign pointer redirects
    for(int i = 0; i < jolts.size(); i++){
        single.value = jolts[i];
        adapters.push_back(single);
    }

    for(int i = 0; i < adapters.size(); i++){ //stop at the last node so it has a next * value of null
        if(adapters[i].value == adapters[i+1].value - 1){ //1step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+1].value - 2){ //2step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+1].value - 3){ //3step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+2].value - 1){ //1step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+2].value - 2){ //2step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+2].value - 3){ //3step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+3].value - 1){ //1step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+3].value - 2){ //2step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(adapters[i].value == adapters[i+3].value - 3){ //3step diff
            adapters[i].next.push_back(&adapters[i+1]);
        }
        if(i > 0){
            if(adapters[i].value == adapters[i-1].value + 1){
                adapters[i].previous.push_back(&adapters[i-1]);
            }
            if(adapters[i].value == adapters[i-1].value + 2){
                adapters[i].previous.push_back(&adapters[i-1]);
            }
            if(adapters[i].value == adapters[i-1].value + 3){
                adapters[i].previous.push_back(&adapters[i-1]);
            }
        }
        if(i > 1){
            if(adapters[i].value == adapters[i-2].value + 1){
                adapters[i].previous.push_back(&adapters[i-2]);
            }
            if(adapters[i].value == adapters[i-2].value + 2){
                adapters[i].previous.push_back(&adapters[i-2]);
            }
            if(adapters[i].value == adapters[i-2].value + 3){
                adapters[i].previous.push_back(&adapters[i-2]);
            }
        }
        if(i > 2){
            if(adapters[i].value == adapters[i-3].value + 1){
                adapters[i].previous.push_back(&adapters[i-3]);
            }
            if(adapters[i].value == adapters[i-3].value + 2){
                adapters[i].previous.push_back(&adapters[i-3]);
            }
            if(adapters[i].value == adapters[i-3].value + 3){
                adapters[i].previous.push_back(&adapters[i-3]);
            }
        }
    }

    if(adapters[0].value <= 3 && adapters[0].previous.size() == 0){
        adapters[0].previous.resize(1);
    }
    if(adapters[1].value <= 3 && adapters[1].previous.size() < 2){
        adapters[1].previous.resize(2);
    }
    if(adapters[2].value <= 3 && adapters[2].previous.size() < 3){
        adapters[2].previous.resize(3);
    }

    memo[0] = 1;

    for(int i = 1; i < 4; i++){
        for(int j = 0; j < 3; j++){
            if(adapters[j].value == i){
                memo[i] = adapters[j].previous.size();
                found = true;
                break;
            }
        }
        if(!found){
            memo[i] = 0;
        }
        found = false;
    }

    for(int i = 3; i < deviceRating; i++){
        for(int j = 0; j < adapters.size(); j++){
            if(j > i){
                found = false;
                break;
            }
            if(i == adapters[j].value){
                found = true;
                break;
            }
        }
        if(!found){
            memo[i] = 0;
            continue;
        }
        memo[i] = memo.at(i-1) + memo.at(i-2) + memo.at(i-3);
        found = false;
    }

    cout << memo.at(adapters[adapters.size()-1].value) << endl << endl;

    return 0;
}

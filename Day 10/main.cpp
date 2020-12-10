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
    unordered_map<int,int> memo;
    int deviceRating;
    int oneDiff = 0;
    int threeDiff = 1; //Start at 1 for the jump out of adapters
    int mappedVal = 0;
    long comb;


    jolts.push_back(0);
    file.open("modinput.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        jolts.push_back(stoi(buffer));
    }

    mergeSort(jolts,0,jolts.size()-1);

    deviceRating = jolts[jolts.size()-1] + 3;

    for(int i = 0; i < jolts.size(); i++){
        //cout << jolts[i] << " " << jolts[i+1] << endl;
        if(i == jolts.size()){  //Different procedure for the last element and the device
            //threeDiff++;    //always a difference of three
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

        //cout << adapters[i].value << " " << adapters[i].next.size() << endl;
    }
        //cout << adapters[adapters.size()-1].value << " " << adapters[adapters.size()-1].next.size() << endl;







    //cout << memo.at(adapters.size()-1) << endl;



    return 0;
}

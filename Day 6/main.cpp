#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int count_uniques(vector<string> inputs){
    int seen = 0;
    vector<char> li;
    bool present = false;
    //Logically the first line will contain all unique characters
    for(int i = 0; i < inputs[0].size(); i++){
        seen++;
        li.push_back(inputs[0][i]); //This needs to be separate to initialize innermost loop
    }

    for(int i = 1; i < inputs.size(); i++){ //Vector
        for(int j = 0; j < inputs[i].size(); j++){ //Individual string
            for(int k = 0; k < li.size(); k++){     //Each character in li
                if(inputs[i][j] == li[k]){
                    present = true;
                    break;
                }
            }
            if(!present){
                seen++;
                li.push_back(inputs[i][j]);
            }
            present = false;
        }
    }
    return seen;
}

int count_shared(vector<string> inputs){
    int seen = 0;
    int counted = 0;

    //The first line contains the only possible "shared answers" for the input
    //For each character in line 0, scan each other line. If character present in all lines, increment.

    for(int i = 0; i < inputs[0].size(); i++){  //First input
        for(int j = 1; j < inputs.size(); j++){ //Entire input array
            for(int k = 0; k < inputs[j].size(); k++){  //Individual input length
                if(inputs[0][i] == inputs[j][k]){
                    seen++;
                    break;
                }
            }
        }
        if(seen == inputs.size() - 1)
            counted++;
        seen = 0;
    }
    return counted;
}


int main()
{
    std::fstream file;
    vector<string> inputs;
    string buffer;
    int total_answers = 0;
    int shared_answers = 0;

    file.open("input.txt");
    //gonna try something different today and process inputs while reading
    while(!file.eof()){
        while(true){
            getline(file,buffer);
            if(buffer == "")
                break;
            else
                inputs.push_back(buffer);
        }
        total_answers += count_uniques(inputs);
        shared_answers += count_shared(inputs);
        inputs.clear();
    }
    file.close();

    cout << total_answers << endl;
    cout << shared_answers << endl;

    return 0;
}

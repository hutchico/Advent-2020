#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::pair;
using std::endl;
using std::string;

/*
struct ticket{
    vector<pair<int,int>> depLoc;
    vector<pair<int,int>> depSta;
    vector<pair<int,int>> depPla;
    vector<pair<int,int>> depTra;
    vector<pair<int,int>> depDat;
    vector<pair<int,int>> depTim;
    vector<pair<int,int>> arrLoc;
    vector<pair<int,int>> arrSta;
    vector<pair<int,int>> arrPla;
    vector<pair<int,int>> arrTra;
    vector<pair<int,int>> tClass;
    vector<pair<int,int>> dur;
    vector<pair<int,int>> price;
    vector<pair<int,int>> route;
    vector<pair<int,int>> row;
    vector<pair<int,int>> seat;
    vector<pair<int,int>> train;
    vector<pair<int,int>> type;
    vector<pair<int,int>> wagon;
    vector<pair<int,int>> zone;
};
*/

struct ruleset{
    vector<string> names;
    vector<vector<pair<int,int>>> ranges;
};

int main()
{
    std::ifstream file;
    std::stringstream ss;
    string readBuffer;  //these names seem meaningful but are functionally temp1, temp2, and temp3
    string parseBuffer;
    string fieldName;

    ruleset rules;
    vector<pair<int,int>> line;
    vector<int> my;
    vector<int> tick;
    vector<int> invalid_values;

    int invalid_sum = 0;

    /*
    int minLow; //Integer range for comparing validity
    int maxLow;
    int minHgh; //Integer range for comparing validity
    int maxHgh;
    */

    file.open("input.txt");
    while(true){                    //process rules
        getline(file,readBuffer);
        if(readBuffer == ""){
            break;
        }
        ss.str(readBuffer);
        getline(ss,readBuffer,':');
        fieldName = readBuffer;
        rules.names.push_back(fieldName);
        ss.ignore(1); //drop the space
        getline(ss,readBuffer,'-');
        getline(ss,parseBuffer,' ');
        line.push_back(std::make_pair(stoi(readBuffer),stoi(parseBuffer)));
        ss.ignore(3);
        getline(ss,readBuffer,'-');
        getline(ss,parseBuffer);
        line.push_back(std::make_pair(stoi(readBuffer),stoi(parseBuffer)));
        rules.ranges.push_back(line);
        line.clear();
        std::stringstream().swap(ss);
    }

    getline(file,readBuffer); //your ticket:
    getline(file,readBuffer);
    readBuffer.append(",");
    ss.str(readBuffer);
    for(int i = 0; i < rules.names.size(); i++){
        getline(ss,readBuffer,',');
        my.push_back(stoi(readBuffer));
    }

    getline(file,readBuffer);
    getline(file,readBuffer); //nearby tickets:
    while(true){
        getline(file,readBuffer);
        if(readBuffer == "")
            break;
        readBuffer.append(",");
        std::stringstream().swap(ss);
        ss.str(readBuffer);
        for(int i = 0; i < rules.names.size(); i++){
            getline(ss,readBuffer,',');
            tick.push_back(stoi(readBuffer));
        }



        for(int i = 0; i < tick.size(); i++){
            int cut = 0;
            //cout << tick[i] << endl;
            for(int j = 0; j < rules.names.size(); j++){
                int minLow = rules.ranges[j][0].first;
                int maxLow = rules.ranges[j][0].second;
                int minHgh = rules.ranges[j][1].first;
                int maxHgh = rules.ranges[j][1].second;
                //cout << minLow << " " << maxLow << " " << minHgh << " " << maxHgh << endl;
                if((tick[i] >= minLow && tick[i] <= maxLow) || (tick[i] >= minHgh && tick[i] <= maxHgh)){
                    cut++;
                }
            }
            if(cut == 0){
                invalid_values.push_back(tick[i]);
                //cout << "added: " << tick[i] << endl;
            }
        }
        //cout << endl;
        tick.clear();
    }

    for(int i = 0; i < invalid_values.size(); i++)
        invalid_sum += invalid_values[i];

    cout << invalid_sum << endl;

    return 0;
}

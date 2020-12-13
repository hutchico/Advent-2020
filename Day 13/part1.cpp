#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include "merge.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main()
{
    std::ifstream file;
    string buffer;
    int depTime;
    vector<int> bus;
    vector<int> stampOffset;
    std::map<int,int> busMod;
    std::stringstream ss;

    file.open("input.txt");
    getline(file,buffer);
    depTime = stoi(buffer);
    getline(file,buffer);
    buffer.append(",");
    ss.str(buffer);
    while(true){
        getline(ss,buffer,',');
        if(buffer == "x")       //Ignoring X busses
            continue;
        else if(ss.eof())
            break;
        else
            bus.push_back(stoi(buffer));
    }
    for(int i = 0; i < bus.size(); i++){
        stampOffset.push_back(bus[i] - (depTime % bus[i]));
    }

    file.close();

    for(int i = 0; i < bus.size(); i++){
        busMod[stampOffset[i]] = bus[i];
    }

    mergeSort(stampOffset,0,stampOffset.size()-1);

    cout << stampOffset[0] * busMod[stampOffset[0]];

    return 0;
}

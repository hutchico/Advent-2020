#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using std::cout;
using std::vector;
using std::endl;
using std::unordered_map;

int main()
{
    std::ifstream file;
    std::string buffer;
    std::stringstream ss;
    vector<int> mem;
    unordered_map<int,int> occ;       //number of times this number has occured
    unordered_map<int,int> turn_last; //the last turn this number was encountered on
    int input;

    int turn = 1;
    int previous = 0;

    //0,1,5,10,3,12,19

    file.open("input.txt");
    getline(file,buffer);
    file.close();
    buffer.append(",");

    ss.str(buffer);
    getline(ss,buffer,',');
    while(!ss.eof()){
        input = stoi(buffer);
        mem.push_back(input);
        turn_last[input] = turn;
        occ[input] = 1;
        turn++;
        getline(ss,buffer,',');
    }
    occ[input] = 0; //reset assignment for most recent input
    previous = turn - 1;

    while(mem.size() < 30000001){
        if(occ[mem[previous-1]] > 0){   //check if number is new
            mem.push_back(previous - turn_last[mem[previous-1]]);
            occ[mem[previous-1]] = occ[mem[previous-1]] + 1;
            turn_last[mem[previous-1]] = previous;
        }
        else{
            mem.push_back(0);
            occ[mem[previous-1]] = 1;
            turn_last[mem[previous-1]] = previous;

        }
        previous = turn;
        turn++;
    }

    cout << mem[2019] << " " << mem[29999999] << endl;

    return 0;
}

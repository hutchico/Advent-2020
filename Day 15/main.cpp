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
    int loc;
    int previous;

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
    turn--;

    while(mem.size() < 30000000){
        previous = mem[turn-1];
        loc = occ[previous];

        if(loc > 0){   //check if number is new
            mem.push_back(turn - turn_last[previous]);
            occ[previous] = loc + 1;
            turn_last[previous] = turn;
        }
        else{
            mem.push_back(0);
            occ[previous] = 1;
            turn_last[previous] = turn;

        }
        turn++;
    }

    cout << mem[2019] << " " << mem[29999999] << endl;

    return 0;
}

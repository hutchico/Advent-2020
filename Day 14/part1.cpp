#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <math.h>

using std::vector;
using std::string;
using std::cout;
using std::endl;

uint64_t convert_dec(string num){
    uint64_t sum = 0;
    for(int i = num.size() - 1; i > -1 ; i--){
        if(num[i] == '1')
            sum += pow(2,35 - i);
        cout << sum << endl;
    }
    //DEBUG: confirm conversion
    //cout << sum << endl;

    return sum;
};

string convert_binary(string input){
    uint64_t num = stoull(input);
    string blank = "000000000000000000000000000000000000";

    for(int i = 36; i > -1; i--){
        if(num < pow(2,i))
            continue;
        else{
            blank[35-i] = '1';
            num -= pow(2,i);
        }
    }
    //DEBUG: confirm conversion
    //cout << blank << endl;

    return blank;
};

string apply_mask(string mask, string value){
    for(int i = 0; i < mask.size(); i++){
        if(mask[i] != 'X')
            value[i] = mask[i];
    }
    //DEBUG: confirm conversion
    //cout << value << endl;

    return value;
};

int main()
{
    std::ifstream file;
    string buffer;
    string addr;
    string value;
    std::stringstream ss;
    string mask;
    vector<string> memOps;
    std::map<int,uint64_t> mem;
    file.open("input.txt");
    uint64_t sum = 0;

    getline(file,buffer);
    while(true){
        if(buffer == "")
            break;
        ss.str(buffer);
        ss.ignore(7); //"mask = "
        getline(ss,mask);
        while(true){
            getline(file,buffer);
            if(buffer == "")
                break;
            if(buffer[1] != 'e')
                break;
            else
                memOps.push_back(buffer);
        }

        for(int i = 0; i < memOps.size(); i++){
            std::stringstream().swap(ss);
            ss.str(memOps[i]);
            ss.ignore(4);
            getline(ss,addr,']');
            ss.ignore(3);
            getline(ss,value);
            cout << stoi(addr) << endl;
            mem[stoi(addr)] = convert_dec(apply_mask(mask,convert_binary(value)));
        }
        std::stringstream().swap(ss);
        memOps.clear();
    }

    for (auto const& x : mem){
        sum += x.second;
    }
    cout << sum << endl;
    return 0;
}

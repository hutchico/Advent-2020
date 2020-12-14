#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
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
        if(mask[i] != '0')
            value[i] = mask[i];
    }
    //DEBUG: confirm conversion
    //cout << value << endl;

    return value;
};

int count_bits(int num){    //Determine bits needed to represent the largest number.
    int sum = 0;
    int maximum = 37;
    while(num > 0){
        if(num > pow(2,maximum)){
            sum++;
            num -= pow(2,maximum);
        }
        maximum--;
    }
    return sum;
}

void write_mem(std::map<uint64_t,uint64_t> &mem, string addr, uint64_t val){
    //TODO: Figure out how to stop this function from duplicating calls when written recursively.
    //          Then rewrite it recursively.
    vector<string> mod_addr;
    string mid;
    int instances = 0;
    string bin;
    int addrSize = addr.size();
    for(int i = addr.size() - 1; i > -1 ; i--){
            if(addr[i] == 'X'){ //count occurrences for call multiplication
               instances++;
            }
    }

    for(int i = 0; i < pow(2,instances); i++){
        mod_addr.push_back(addr);
    }
    int bits_needed = count_bits(mod_addr.size()-1);
    for(int i = mod_addr.size() - 1; i > -1; i--){
        //Idea: replace X in a given address with a binary rep of that array address
        bin = convert_binary(std::to_string(i));
        if(i != 0)
            bin.erase(0,bin.size()-bits_needed);


        for(int k = bin.size() - 1; k > -1 ; k--){
            for(int j = addrSize - 1; j > -1; j--){
                if(mod_addr[i][j] != 'X')
                    continue;
                else{
                    mod_addr[i][j] = bin[k];
                    break;
                }
            }
        }
    }


    for(int i = 0; i < mod_addr.size(); i++){
        mem[convert_dec(mod_addr[i])] = val;
    }

}

int main(){
    std::ifstream file;
    string buffer;
    string addr;
    string value;
    uint64_t decValue = 0;
    std::stringstream ss;
    string mask;
    string mid;
    vector<string> memOps;
    std::map<uint64_t,uint64_t> mem;
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
            decValue = stoull(value);
            addr = apply_mask(mask,convert_binary(addr));
            write_mem(mem,addr,decValue);
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

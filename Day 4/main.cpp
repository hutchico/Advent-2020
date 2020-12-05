#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Passport{
public:
    Passport(){
        birthYear = -1; issueYear = -1; expiresYear = -1; height = "nul"; hair = "nul"; eye = "nul"; pid = "nul"; cid = -1; total_valid = 0;
    }

    void setBYR(int val){birthYear = val;};
    void setIYR(int val){issueYear = val;};
    void setEYR(int val){expiresYear = val;};
    void setHGT(string val){height = val;};
    void setHCL(string val){hair = val;};
    void setECL(string val){eye = val;};
    void setPID(string val){pid = val;};
    void setCID(int val){cid = val;};

    bool valid_p1(){
        if(birthYear != -1 && issueYear != -1 && expiresYear != -1 && height != "nul" && hair != "nul" && eye != "nul" && pid != "nul")
            return true;
        else
            return false;
    }
    bool valid_p2(){
        if(birthYear != -1 && issueYear != -1 && expiresYear != -1 && height != "nul" && hair != "nul" && eye != "nul" && pid != "nul"){
            if(birthYear >= 1920 && birthYear <= 2002)  //1
                total_valid++;
            if(issueYear >= 2010 && issueYear <= 2020)  //2
                total_valid++;
            if(expiresYear >= 2020 && expiresYear <= 2030)  //3
                total_valid++;

            string hgtMeas = "";                        //4
            hgtMeas.push_back(height[height.size()-2]);
            hgtMeas.push_back(height[height.size()-1]);
            if(hgtMeas == "cm" || hgtMeas == "in"){                       //If hgtmeas ISN'T cm or in, auto fail
                if(hgtMeas == "cm"){
                    if(stoi(height) >= 150 && stoi(height) <= 193)
                        total_valid++;
                }
                else if(stoi(height) >= 59 && stoi(height) <= 76)   //can assume hgtmeas is in because it is NOT cm
                    total_valid++;
            }

            char hclPrefix = hair[0];                   //5
            //Must start with # and be of length 7 (# and six characters)
            if(hclPrefix == '#' && hair.length() == 7){                   //Validate each character for numbers or letters
                int checked = 0;
                for(int i = 1; i < hair.length(); i++){ //Check it's either 0-9 or a-z
                    if((int(hair[i]) >= 48 && int(hair[i]) <= 57) || (int(hair[i]) >= 97 && int(hair[i]) <= 102))
                        checked++;
                }
                if(checked == 6)
                    total_valid++;
            }
                                                    //6
            if(eye == "amb" || eye == "blu" || eye == "brn" || eye == "gry" || eye == "grn" || eye == "hzl" || eye == "oth")
                total_valid++;
                                                    //7
            if(pid.length() == 9){
                int checked = 0;
                for(int i = 0; i < 9; i++){
                    if(int(pid[i]) >= 48 && int(pid[i]) <= 57)
                        checked++;
                }
                if(checked == 9)
                    total_valid++;
            }
            if(total_valid == 7)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    //FUNCTION: Clear all set values in the object while reading from file
    void reset(){
        birthYear = -1; issueYear = -1; expiresYear = -1; height = "nul"; hair = "nul"; eye = "nul"; pid = "nul"; cid = -1;
    }
    //DEBUG: List contents of the class object
    void get_vars(){
        cout << birthYear << " " << issueYear << " " << expiresYear << " " << height << " " << hair << " " << eye << " " << pid << " " << cid << endl;
    }
private:
    int birthYear;
    int issueYear;
    int expiresYear;
    string height;
    string hair;
    string eye;
    string pid;
    int cid;
    int total_valid;
};

int getStringValue(string input){   //Convert each identifier into a 8-9 digit identifier
    string converted_value = "";
    for(int i = 0; i < input.size(); i++){
        converted_value.append(std::to_string(int(input[i])));
    }
    return stoi(converted_value);
}

int main()
{
    std::ifstream file;
    std::stringstream ss;
    std::stringstream temp;
    vector<Passport> database;
    vector<string> tokenized;
    Passport obj;
    string field;
    string buffer;
    int valid_num = 0;
    bool loop = true;

    file.open("input.txt");
    while(true){
        //should cover the whole file
        if(file.eof() == true)
            break;
        if(field == "\n")
            break;
        if(buffer == "\n")
            break;
        while(loop){ //repeat for each individual passport
            getline(file,field);
            ss.str(field);
            if(field == ""){
               database.push_back(obj);
               obj.reset();
               loop = false;
               break;
            }
            while(getline(ss,buffer,' '))
                tokenized.push_back(buffer);
            std::stringstream().swap(ss);
            for(int i = 0; i < tokenized.size(); i++){
                buffer.clear();
                for(int j = 0; j < 3; j++){
                    buffer.push_back(tokenized[i][j]);
                }
                //tokenized[i].copy(buffer,4,0);
                tokenized[i].erase(0,4);
                switch(getStringValue(buffer)){
                case 98121114 : buffer = tokenized[i]; obj.setBYR(stoi(buffer)); break;
                case 105121114 : buffer = tokenized[i]; obj.setIYR(stoi(buffer)); break;
                case 101121114 : buffer = tokenized[i]; obj.setEYR(stoi(buffer)); break;
                case 104103116 : buffer = tokenized[i]; obj.setHGT(buffer); break;
                case 10499108 : buffer = tokenized[i]; obj.setHCL(buffer); break;
                case 10199108 : buffer = tokenized[i]; obj.setECL(buffer); break;
                case 112105100 : buffer = tokenized[i]; obj.setPID(buffer); break;
                case 99105100 : buffer = tokenized[i]; obj.setCID(stoi(buffer)); break;
                default : cout << "mismatch read" << endl; break;
                }
            }
            tokenized.clear();
        }
        loop = true;
    }
    file.close();

    for(int i = 0; i < database.size(); i++){
        if(database[i].valid_p1())
            valid_num++;
    }

    cout << valid_num << endl;

    valid_num = 0;

    for(int i = 0; i < database.size(); i++){
        if(database[i].valid_p2())
            valid_num++;
    }

    cout << valid_num << endl;


    return 0;
}

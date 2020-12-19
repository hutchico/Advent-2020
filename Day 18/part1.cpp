#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <assert.h> //DEBUG

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stack;


long long resolve_eq(string &line){
    long long ri = 0;
    long long li = 0;
    char input = '@'; //initialize char for while loop
    char op = '*';
    //cout << line << endl;
    if(line[0] != 'n'){
        ri = (long long)(line[0] - 48);
        line.erase(0,1);
    }
    else{
        line.erase(0,1);
        ri = resolve_eq(line);
    }
    //cout << ri << endl;

    //cout << line << endl;
    while(input != 'd' && line.size() > 0){
        input = line[0];
        //cout << input << endl;
        line.erase(0,1);
        //cout << line << endl;
        if(input == 'd')
            break;
        op = input;
        input = line[0];
        //cout << input << endl;
        line.erase(0,1);
        if(input == 'n'){
            li = resolve_eq(line);
        }
        else{
            li = (long long)(input - 48);
        }
        //cout << ri << " " << li << endl;
        if(op == '+'){
            //cout << "--" << ri << endl;
            ri = ri + li;
            //cout << "---" << ri << endl;
        }
        else{
            //cout << "__" << ri << endl;
            ri = ri * li;
            //cout << "___" << ri << endl;
        }
    }

    return ri;
}

int main()
{
    std::ifstream file;
    string buffer;
    vector<string> math;

    long long sum = 0;

    file.open("input.txt");
    while(true){
        string actual = "";
        getline(file,buffer);
        if(buffer == "")
            break;
        while(buffer.size() > 0){
            char input = buffer[0];
            buffer.erase(0,1);
            if(input == ' ')
                continue;
            else if(input == '(')
                actual.append("n");
            else if(input == ')')
                actual.append("d");
            else
                actual.append(string(1,input));
        }
        math.push_back(actual);
    }
    //cout << math[5] << endl;
    //cout << resolve_eq(math[5]) << endl;

    ///OOO flow: operations resolved left to right; when right operand is a parenthetical, the right operand is resolved first

    for(int i = 0; i < math.size(); i++){
        long long part = resolve_eq(math[i]);
        cout << i << " " << part << endl;
        sum += part;
    }
    cout << sum << endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;


int main()
{
    vector<int> expense;
    string buffer;
    ifstream file;
    int len;
    file.open("input");
    while(true){
        getline(file,buffer);
        if(file.eof() == false)
            expense.push_back(stoi(buffer));
        else
            break;
    }
    file.close();

    len = expense.size();

    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            for(int k = 0; k < len; k++){
               if(expense[i] + expense[j] + expense[k] == 2020)
                    std::cout << expense[i] * expense[j] * expense[k];
            }
        }
    }
}

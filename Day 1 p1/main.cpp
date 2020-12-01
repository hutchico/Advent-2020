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
    int len; //Size of the resulting vector = number of inputs to process
    bool done = false;

    //First to read inputs, stuff into a vector
    file.open("input");
    while(true){
        getline(file,buffer);
        if(file.eof() == false)
            expense.push_back(stoi(buffer));
        else
            break;
    }
    file.close();

    //And now the messy nested loop garbage
    //Bit of a bruteforce solution but gets the job done
    len = expense.size();

    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            if(i == j)  //Don't add an input to itself
                break;
            else if(expense[i] + expense[j] == 2020){
                cout << expense[i] << endl << expense[j] << endl;
                cout << "Product: " << expense[i] * expense[j] << endl;
                done = true;
                break;
            }
        }
        if(done)
            break;
    }

    return 0;
}

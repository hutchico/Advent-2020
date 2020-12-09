#include <iostream>
#include <fstream>
#include <vector>
#include "merge.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main()
{
    vector<unsigned long long> numbers;
    std::ifstream file;
    string buffer;
    int scalehigh = 24;
    int scalelow = 0;
    int targetValue;
    int targetLoc;
    long int sum = 0;
    bool isValid = false;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        numbers.push_back(stoull(buffer));
    }
    for(int i = 0; i < numbers.size(); i++){
        for(int j = scalelow; j < scalehigh + 1; j++){
            for(int k = j + 1; k < scalehigh + 1; k++){
                //if(j == k)
                //    continue;
                if(numbers[j] + numbers[k] == numbers[scalehigh+1]){
                    isValid = true;
                    break;
                }
            }
            if(isValid)
                break;
        }
        if(!isValid){   //Inner loops failed to find a matching sum
            cout << endl << numbers[scalehigh+1] << endl << endl;
            targetValue = numbers[scalehigh+1];
            targetLoc = scalehigh + 1;
            isValid = false; //Reset this variable for part 2
            break;
        }
        scalelow++;
        scalehigh++;
        isValid = false;
    }

    for(int i = targetLoc; i > 0; i--){
        for(int j = 0; j < i; j++){
            for(int k = j; j < i; k++){
                sum += numbers[k];
                //cout << sum << endl;
                if(sum == targetValue){ //Attempt to shortcircuit the process en route
                    isValid = true;
                    cout << "values found between " << numbers[j] << " and " << numbers[k] << endl;
                    scalelow = j;
                    scalehigh = k;
                    break;
                }
                if(sum > targetValue)
                    break;
            }
            if(isValid)
                break;
            if(sum == targetValue){
                isValid = true;
                cout << "values found between " << numbers[j] << " and " << numbers[i] << endl;
                scalelow = j;
                scalehigh = i;
                break;
            }
            sum = 0;
        }
        if(isValid)
            break;
    }

    mergeSort(numbers,scalelow,scalehigh);
    cout << numbers[scalelow] + numbers[scalehigh] << endl;


    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using std::string;
using std::cout;
using std::endl;
using std::vector;

struct pass{
    string location;
    int pass_id;
};

void merge(vector<struct pass> &input, int low, int mid, int up){
    //yeah yeah it's copied from the internet, what isn't these days
    int n1 = mid - low + 1;
    int n2 = up - mid;

    vector<struct pass> arr1;
    vector<struct pass> arr2;

    for(int i = 0; i < n1; i++)
        arr1.push_back(input[low+i]);
    for(int i = 0; i < n2; i++)
        arr2.push_back(input[mid+1+i]);

    int i = 0;
    int j = 0;
    int k = low;

    while(i < n1 && j < n2){
        if(arr1[i].pass_id <= arr2[j].pass_id){
            input[k] = arr1[i];
            i++;
        }
        else {
            input[k] = arr2[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        input[k] = arr1[i];
        i++;
        k++;
    }

    while(j < n2){
        input[k] = arr2[j];
        j++;
        k++;
    }

}

void mergeSort(vector<struct pass> &input, int lower, int upper){
    if(lower >= upper)
        return;
    int mid = (lower + upper - 1) / 2;
    mergeSort(input,lower,mid);
    mergeSort(input,mid+1,upper);
    merge(input,lower,mid,upper);
}


int get_ID(string input){
    //Reminder to self that Front implies 0-63 and Back implies 64-127
    //Algorithm: Back increases lower bound, Front decreases upper bound
    //              Same logic applies to Right and Left, respectively.
    //Amount starts at 2^6 and decreases to 2^0
    int lower = 0;
    int upper = 127;
    int power = 6;
    int row;
    for(int i = 0; i < 7; i++){
        if(input[i] == 'F')
            upper -= pow(2,power);
        else
            lower += pow(2,power);
        power--;
    }
    //Condition: lower == upper; assignment here is thus arbitrary
    row = lower;

    lower = 0;
    upper = 7;
    power = 2;
    for(int i = 7; i < 10; i++){
        if(input[i] == 'L')
            upper -= pow(2,power);
        else
            lower += pow(2,power);
        power--;
    }
    return row * 8 + lower;
}

int main()
{
    struct pass input;
    vector<struct pass> passes;
    string buffer;
    std::ifstream file;
    int highest_id = -1;
    int holder;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(file.eof())
            break;
        input.location = buffer;
        passes.push_back(input);
    }

    for(int i = 0; i < passes.size(); i++){
        holder = get_ID(passes[i].location);
        passes[i].pass_id = holder;
        if(holder > highest_id){
            highest_id = holder;
        }
    }
    cout << highest_id << endl;

    mergeSort(passes,0,passes.size()-1);

    for(int i = 0; i < passes.size()-1; i++){
        if(passes[i].pass_id != (passes[i+1].pass_id - 1))
            cout << passes[i].pass_id + 1 << endl;
    }

    return 0;
}

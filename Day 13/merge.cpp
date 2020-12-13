#include "merge.h"

void merge(std::vector<int> &input, int low, int mid, int up){
    //yeah yeah it's copied from the internet, what isn't these days
    int n1 = mid - low + 1;
    int n2 = up - mid;

    std::vector<int> arr1;
    std::vector<int> arr2;

    for(int i = 0; i < n1; i++)
        arr1.push_back(input[low+i]);
    for(int i = 0; i < n2; i++)
        arr2.push_back(input[mid+1+i]);

    int i = 0;
    int j = 0;
    int k = low;

    while(i < n1 && j < n2){
        if(arr1[i] <= arr2[j]){
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

void mergeSort(std::vector<int> &input, int lower, int upper){
    if(lower >= upper)
        return;
    int mid = (lower + upper - 1) / 2;
    mergeSort(input,lower,mid);
    mergeSort(input,mid+1,upper);
    merge(input,lower,mid,upper);
}

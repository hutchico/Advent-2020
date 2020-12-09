#ifndef MERGE_H
#define MERGE_H

#include <vector>

void mergeSort(std::vector<unsigned long long> &input, int lower, int upper);
void merge(std::vector<unsigned long long> &input, int low, int mid, int up);

#endif

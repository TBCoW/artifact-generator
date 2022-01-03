#ifndef SORTINGMETHODS_H_
#define SORTINGMETHODS_H_
#include <vector>
#include <string>

void swap(int* a, int* b);

//quicksort algorithm with artifact names
int doublepartition(std::vector<int>& vec, int low, int high, std::vector<std::string>& nam, int namLow, int namHigh);
void doublequicksort(std::vector<int>& stat, int statLow, int statHigh, std::vector<std::string>& name, int nameLow, int nameHigh);

#endif

#include "sortingmethods.h"

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap(std::string* a, std::string* b)
{
	std::string temp = *a;
	*a = *b;
	*b = temp;
}

int doublepartition(std::vector<int>& vec, int low, int high, std::vector<std::string>& nam, int namLow, int namHigh)
{
	int pivot = vec[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (vec[j] <= pivot)
		{
			i++;
			swap(&vec[i], &vec[j]);
			swap(&nam[i], &nam[j]);
		}
	}
	swap(&vec[i + 1], &vec[high]);
	swap(&nam[i + 1], &nam[high]);
	return (i + 1);
}

void doublequicksort(std::vector<int>& stat, int statLow, int statHigh, std::vector<std::string>& name, int nameLow, int nameHigh)
{
	if (statLow < statHigh)
	{
		int q;
		q = doublepartition(stat, statLow, statHigh, name, nameLow, nameHigh);
		doublequicksort(stat, statLow, q - 1, name, nameLow, q - 1);
		doublequicksort(stat, q + 1, statHigh, name, q + 1, nameHigh);
	}
}


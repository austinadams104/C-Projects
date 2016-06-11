#include "Sort.h"


int main()
{
	testFunction("Std::Sort", stdSort);
	testFunction("Bubble Sort", bubbleSort);
	testFunction("Insertion Sort", insertionSort);
	testFunction("Selection Sort", selectionSort);
	testFunction("Merge Sort", mergeSort);
	testFunction("Quick Sort", quickSortWrapper);

	char dummy;
	std::cin >> dummy;
}


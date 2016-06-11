#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//as discussed in class, partition A[low,...,high] into two subarrays by using a pivot, and
//return the index of the pivot in the resulting partition, please
//complete the following function
int partition(int A[], int low, int high)
{
	int pivot = A[high];
	int left = low;
	for (int i = low; i < high; i++)
	{
		if (A[i] <= pivot)
		{
			swap(A[left], A[i]);
			left++;
		}
	}
	std::swap(A[left], A[high]);
	return left;
}

//sort the elements in A[low,...,high], please complete the following
//function, in the function you need to call the function
//partition(), as discussed in class
void quickSort(int A[], int low, int high)
{
	if (low >= high) return;
	int i = partition(A, low, high);
	quickSort(A, low, i - 1);
	quickSort(A, i + 1, high);
}

int main()
{
	//open files
	ifstream inputFile;
	inputFile.open("hw7_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	int A[100];
	int value;
	int n = 0;

	//read numbers from the input file, after the while loop all
	//numbers are stored in A[0,...,n-1], i.e., n is the number of
	//elements in A
	while(inputFile >> value)
	{
		A[n] = value;
		n++;
	}

	//call quicksort
	quickSort(A, 0, n-1);

	cout << "The following is the list after quick sort:" << endl;
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
	
	return 0;
}

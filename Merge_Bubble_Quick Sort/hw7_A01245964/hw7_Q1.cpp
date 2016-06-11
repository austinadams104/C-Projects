#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//sort all numbers in A[0,...,n-1] by bubble sort, please complete the
//following function
void bubbleSort(int A[], int n)
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int i = 0; i < n - 1; i++)
		{

			if (A[i] > A[i + 1])
			{
				swap(A[i], A[i + 1]);
				swapped = true;
			}
		}
	}
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

	//call bubble sort
	bubbleSort(A, n);

	cout << "The following is the list after bubble sort:" << endl;
	for(int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;

	inputFile.close();
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//merge the two sorted subarrays A[low,...,mid] and A[mid+1,...,high],
//please complete the following function
void merge(int A[], int low, int mid, int high)
{
	int m1 = mid - low + 1;
	int m2 = high - mid;

	int *B = new int[m1];
	int *C = new int[m2];

	for (int i = 0; i < m1; i++)
		B[i] = A[low + i];
	for (int j = 0; j < m2; j++)
		C[j] = A[mid + 1 + j];

	int i = 0, j = 0;
	int k = low;

	while (i < m1 && j < m2){
		if (B[i] <= C[j]){
			A[k] = B[i];
			i++;
		}
		else{
			A[k] = C[j];
			j++;
		}
		k++;
	}
	while (i < m1)
	{
		A[k] = B[i];
		i++;
		k++;
	}
	while (j < m2){
		A[k] = C[j];
		j++;
		k++;
	}
	delete[]B;
	delete[]C;
}

//sort all numbers in A[low,...,high], please complete the following function
void mergeSort(int A[], int low, int high)
{
	if (high == low) return;
	int mid = (low + high) / 2;
	mergeSort(A, low, mid);
	mergeSort(A, mid+1, high);
	merge(A, low, mid, high);
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

	mergeSort(A, 0, n-1);

	cout << "The following is the list after mergesort:" << endl;
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	
	cout << endl;

	inputFile.close();
	return 0;
}

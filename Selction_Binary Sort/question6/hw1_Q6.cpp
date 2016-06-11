#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int ARRAY_SIZE = 100;

void input(int A[], int & n, const string & fileName) 
{
	ifstream inputFile;
	int value;

	inputFile.open(fileName.c_str());

	//read data until the end of the file
	while(inputFile >> value)
	{
		A[n] = value;
		n++;
	}

	inputFile.close();
}

void output(int C[], int B[], const int n, const string & fileName) 
{
	ofstream outputFile;
	outputFile.open(fileName.c_str());
	for (int i = 0; i < n; i++)
		 outputFile << "The position of " << B[i] << " is " << C[i] << endl; 
	  	 //outputFile << A[i] << "  "; 
	 
	outputFile.close();
}

//please complete the following function. x is the search value. If x is in the array, return the index of x in the array; otherwise return -1. 
int binarySearch(int array[], int first, int last, int x)
{
}

int main()
{
	int A[ARRAY_SIZE], B[ARRAY_SIZE], C[ARRAY_SIZE];// array C is used to hold the search results temporarily
	int n = 0;// the number of elements stored in A
	int m = 0;// the number of elements stored in B
	string dataFile = "hw1_Q6_data.txt"; // the name of the data file 
	string searchFile = "hw1_Q6_search.txt"; // the name of the search file 
	string outputFile = "hw1_Q6_output.txt"; // the name of the output file 

    //input all numbers from the data file to the array A
	input(A, n, dataFile); 
    
	//input all numbers from the search file to the array B
	input(B, m, searchFile); 

	//for (int i = 0; i< n; i++)
	//	cout << A[i] << " "; 
	//cout << endl;


	//print the search results on the screen
	for (int i = 0; i < m; i++)
	{
		C[i] = binarySearch(A, 0, n-1, B[i]); 
		cout << "The position of " << B[i] << " is " << C[i] << endl; 
	}

	//output the search results to the output file
	output(C, B, m, outputFile);

	cout << endl; 

	return 0;
}

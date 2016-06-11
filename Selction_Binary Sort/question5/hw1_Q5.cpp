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

void output(int A[], const int n, const string & fileName) 
{
	ofstream outputFile;
	outputFile.open(fileName.c_str());
	for (int i = 0; i < n; i++)
	  	 outputFile << A[i] << "  "; 
	 
	outputFile.close();
}

//please finish the following procedure
void selectionSort(int A[], int n)
{
	for(int i = 0; i < n -1; i++){
		int minimum = A[i];
		int minimumPosition = i;
		for(int j = i; j < n; j++){
			if (A[j] < minimum){
				A[j] = minimum;
				minimumPosition = j;
			}
		}
		swap(A[i], A[minimumPotion])
	}
		
}


int main()
{
	int A[ARRAY_SIZE];
	int n = 0;// the number of elements stored in A
	string inputFile = "hw1_Q5_input.txt"; // the name of the input file 
	string outputFile = "hw1_Q5_output.txt"; // the name of the output file 

	//read the numbers from the input file to array A and the value n
	//will also be set correctly
	input(A, n, inputFile); 

    //call the selection sort procedure
	selectionSort(A, n); 

    //print the numbers of A out in the screen/console 
	for (int i = 0; i < n; i++)
		cout << A[i] << "  "; 

	cout << endl; 

	//output the sorted numbers in A to output file
	output(A, n, outputFile);

	return 0;
}

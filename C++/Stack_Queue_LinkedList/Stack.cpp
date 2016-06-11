#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Stack
{
	private:
		int *stackArray;
		int size;// the size of the array stackArray
		int top;

	public:
		Stack(int size_input);
		~Stack() {delete [] stackArray;}
		void push (int x);//push a new value x to the top
		int pop ();    //remove the top value and return it
		bool isEmpty();//check whether the stack is empty
		bool isFull();//check whether the stack is full
};

Stack::Stack(int size_input)
{
	// set the stack size
	size = size_input;
	// dynamically create an array of size equal to ''size''
	stackArray = new int[size];
	top = 0;
}


bool Stack::isEmpty() 
{
	if (top == 0)
		return true;
	else
		return false;
}

bool Stack::isFull() 
{
	if (top == size)
		return true;
	else
		return false;
}

//please complete the following function
int Stack::pop()
{
	if (top > 0){
		top--;
		return stackArray[top];
	}
	else
		cout << "Stack is empty.\n";
}

//please complete the following function
void Stack::push(int x)
{
	if (top < size){
		stackArray[top] = x;
		top++;
	}
	else
		cout << "Stack is full.\n";
}


const int STACK_SIZE = 30;  

int main()
{
	Stack stack(STACK_SIZE); 
	string inputFileName = "hw2_Q3_input.txt"; // input file with operations 
	string outputFileName = "hw2_Q3_output.txt"; // output file

	//open files
	ifstream inputFile;
	inputFile.open(inputFileName.c_str());
	if (!inputFile)
	{
		cout << "Error opening the file " << inputFileName << endl;
		exit(0);
	}
	
	ofstream outputFile;
	outputFile.open(outputFileName.c_str());
	
	if (!outputFile)
	{
		cout << "Error opening the file " << outputFileName << endl;
		exit(0);
	}


	//read operations from the input file
	string op;
	int value, x;
	while(inputFile >> op)
	{
		if (op == "pop") // a pop operation, 
		{
		    x = stack.pop();
			outputFile << x << endl;// the pop result is printed to the output file
			cout << x << endl;// the pop result is printed to the console/screen
		}
		else // a push operation
		{
			inputFile >> value;
			stack.push(value);
		}
	}

	inputFile.close();
	outputFile.close();

	return 0;
}

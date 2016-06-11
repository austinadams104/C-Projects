//use a linked list to maintain a sorted list of numbers in descending
//order

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

const int ARRAY_SIZE = 100;

//input the data from a file to an array A, n is used to calculate the total number of
//data in the file
void input(int A[], int & n, const string & fileName) 
{
	ifstream inputFile;
	int value;

	inputFile.open(fileName.c_str());

	if (!inputFile)
	{
		cout << "Error opening the file " << fileName << endl;
		exit(0);
	}

	//read data until the end of the file and calculate n
	while(inputFile >> value)
	{
		A[n] = value;
		n++;
	}

	inputFile.close();
}


struct ListNode
{
	int value;
	ListNode *next;
	//struct constructor
	ListNode (int input_value, ListNode * input_next = NULL)
	{
		value = input_value;
		next = input_next;
	}
};

//define a class for the linked list
class LinkedList
{
	private:
		ListNode *head;// the head of the linked list

	public:
		LinkedList() {head = NULL;}
		~LinkedList();
		void insert(int x);// add a number x the end of the list
		void remove(int x);//remove x from the list
		void reverse();//reverse the list
		void printListToFile(const string & fileName) const; // print the list to a file
		void printList() const; // print the list to the console (computer's screen), this function may be helpful when you test your program
};

//please complete the following function
void LinkedList::insert(int x)
{
	ListNode *xNode = new ListNode(x);
	if (head == NULL || head->value < x)
	{
		xNode->next = head;
		head = xNode;
		return;
	}
	else{
		ListNode *temp = head;
		while (temp->next != NULL && temp->next->value > x){
			temp = temp->next;
		}
		if (temp->next != NULL && temp->next->value == x) return;
		if (temp->value == x)return;
		xNode->next = temp->next;
		temp->next = xNode;
	}
}

//please complete the following function
void LinkedList::remove(int x)
{
	ListNode *xNode = new ListNode(x);
	if (head == NULL || head->value < x) return;
	else{
		ListNode *temp = head;
		if (temp->value == x){
			head = temp->next;
			return;
		}
		if (temp->next != NULL && temp->next->value == x){
			temp->next = temp->next->next;
			return;
		}		
		while (temp->next->next != NULL && temp->next->next->value > x){
			temp = temp->next;
		}
		if (temp->next->next != NULL && temp->next->next->value == x){
			temp->next->next = temp->next->next->next;
			return;
		}
	}
}

//please complete the following function
void LinkedList::reverse()
{
	ListNode *previous = NULL;
	ListNode *current = head;
	ListNode *post;

	while (current != NULL){
		post = current->next;
		current->next = previous;
		previous = current;
		current = post;
	}
	head = previous;

}

void LinkedList::printList() const
{
	ListNode *p = head;
	while (p != NULL)
	{
		if (p->next == NULL)
			cout << p->value << endl; 
		else
			cout << p->value << " -> ";
		p = p->next;
	}
}

void LinkedList::printListToFile(const string & fileName) const
{
	ofstream outputFile;
	outputFile.open(fileName.c_str());
	if (!outputFile)
	{
		cout << "Error opening the file " << fileName << endl;
		exit(0);
	}

	ListNode *p = head;
	while (p != NULL)
	{
		if (p->next == NULL)
			outputFile << p->value << endl; 
		else
			outputFile << p->value << " -> ";
		p = p->next;
	}

	outputFile.close();
}

//destructor, delete all nodes
LinkedList::~LinkedList()
{
	ListNode *p = head;
	while (p != NULL)
	{
		ListNode * garbageNode = p;
		p = p->next;
		delete garbageNode;
	}
}

int main()
{
	int A[ARRAY_SIZE];// store numbers for insert
	int B[ARRAY_SIZE]; // store numbers for remove
	int n = 0;// the number of elements that will be stored in A
	int m = 0;// the number of elements that will be stored in B
	string inputFile1 = "hw2_Q1_insertData.txt"; // file with data for insert 
	string inputFile2 = "hw2_Q1_removeData.txt"; // file with data for remove 

	//input data from the two files
	input(A, n, inputFile1); 
	input(B, m, inputFile2); 

	LinkedList list;

	//do insert operations
	for (int i = 0; i < n; i++)
		list.insert(A[i]);
	
	//do remove operations
	for (int i = 0; i < m; i++)
		list.remove(B[i]);
	
	//list.printList();
	
	//reverse the list
	list.reverse();

	list.printList();

	//print the list to the output file
	string outputFile = "hw2_Q1_output.txt"; // the output file 
	list.printListToFile(outputFile);

	return 0;
}

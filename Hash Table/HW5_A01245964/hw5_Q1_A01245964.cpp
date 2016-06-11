#include<iostream>
#include<fstream>
#include<string>
using namespace std;

ofstream outputFile;//defined as a global variable

struct Element
{
	int key;
	Element * next;
	Element(int key_input, Element * next_input = NULL)
	{
		key = key_input;
		next = next_input;
	}
};

class HashTable // separate chaining 
{
	private:
		int m; // the size of the table
		Element ** T; //the hash table
		int hash(int); // the hash function

	public:
		HashTable(int size);
		void insert(int x);// insert a new element with key x
		void remove(int x);// remove an element whose key is x
		bool search(int x); // search an element whose key is x and return true if it is found 
		void printTableEntry(int i);//print the list in T[i]
};


//please complete the following function
bool HashTable::search (int x)
{
	Element *temp = T[hash(x)];
	if (temp == NULL){
		return false;
	}
	while (temp != NULL && temp->key != x)
	{
		temp = temp->next;
	}
		if (temp == NULL)
			return false;
		else
			return true;
}

//please complete the following function
void HashTable::remove (int x)
{
	Element *temp = T[hash(x)];
	if (temp->key == x){
		T[hash(x)] = temp->next;
	}
	while (temp->next != NULL && temp->next->key != x){
		temp = temp->next;
	}
	if (temp->next == NULL){
		return;
	}
	if (temp->next->key == x){
		temp->next = temp->next->next;
		return;
	}
}

//please complete the following function
void HashTable::insert(int x)
{
	Element *temp = T[hash(x)];
	Element *newElement = new Element(x);
	newElement->next = temp;
	T[hash(x)] = newElement;
}

void HashTable::printTableEntry(int i)
{
	cout << "Entry " << i << ":  "; 
	outputFile << "Entry " << i << ":  "; 

	Element * p = T[i];
	while (p != NULL)
	{
		cout << p->key;
		outputFile << p->key;

		if(p->next != NULL)
		{
			cout << "->";
			outputFile << "->";
		}
		p = p -> next;
	}
	cout << endl;
	outputFile << endl;
}

int HashTable::hash(int x)
{
	return x % m;
}

HashTable::HashTable(int tableSize)
{
	m = tableSize;
	T = new Element * [m];
	for(int i = 0; i < m; i++)
		T[i] = NULL;
}

int main()
{

	//open files
	ifstream inputFile;
	inputFile.open("hw5_Q1_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	//outputFile has been defined as a global variable
	outputFile.open("hw5_Q1_output.txt");
	if (!outputFile)
		cout << "Error opening the output file " << endl;

	string op;
	int tableSize;
	//read the hash table size
	inputFile >> tableSize;

	HashTable hashtable(tableSize);

	//read operations from the input file
	int x;
	while(inputFile >> op)
	{
		if (op == "insert")
		{
			inputFile >> x; // read the value x for insert
			hashtable.insert(x);
		}
		if (op == "remove")
		{
			inputFile >> x; // read the value x for remove 
			hashtable.remove(x);
		}
		if (op == "search")
		{
			inputFile >> x;
			if (hashtable.search(x) == true)
			{
				cout << "The key " << x << " is in the current hash table." << endl;
				outputFile << "The key " << x << " is in the current hash table." << endl;
			}
			else// x is not in the hash table
			{
				cout << "The key " << x << " is not in the current hash table." << endl;
				outputFile << "The key " << x << " is not in the current hash table." << endl;
			}
		}
	}
	cout << endl;
	outputFile << endl;

	cout << "The following is the current hash table:" << endl;
	outputFile << "The following is the current hash table:" << endl;

	//print out the current hash table
	for (int i = 0; i < tableSize; i++)
		hashtable.printTableEntry(i);


	inputFile.close();
	outputFile.close();

	return 1;
}

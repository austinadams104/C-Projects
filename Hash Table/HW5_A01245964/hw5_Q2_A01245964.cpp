#include<iostream>
#include<fstream>
#include<string>
using namespace std;

ofstream outputFile;//defined as a global variable

//alternatively, you may define an enumerated date type for the flag as follows
//enum EntryType {EMPTY, ACTIVE, DELETED};

struct Element
{
	int key;
	int flag;//0 means EMPTY, 1 means ACTIVE, 2 means DELETED
	//EntryType flag;
};

class HashTable // separate chaining 
{
	private:
		int m; // the size of the table
		Element * T; //the hash table
		int hash(int); // the hash function
		int probe(int x, int i);
		int linearProbe(int x, int i);

	public:
		HashTable(int size);// set the size of the table
		void insert(int x);// insert a new element with key x 
		void remove(int x);// remove an element whose key is x
		int search(int x); // search an element whose key is x and return the index, and if there is no such key, return -1 
		void printTableEntry();//print the list in T[i]
};

//please complete the following three functions

// search an element whose key is x and return the index of the element in T, and if there is no such key, return -1 
int HashTable::search (int x)
{
	int i = 0;
	while (i < m){
		int k = probe(x, i);
		if (T[k].flag == 1 && T[k].key == x){
			return k;
		}
		if (T[k].flag == 0)
			return -1;
		else i++;
	}
	return -1;
}

void HashTable::remove (int x)
{
	int i = 0;
	while (i < m){
		int k = probe(x, i);
		if (T[k].flag == 1 && T[k].key == x){
			T[k].flag = 2;
		}
		if (T[k].flag == 0)
			return;
		else
			i++;
	}
	return;
}

void HashTable::insert(int x)
{
	int i = 0;
	while (i < m){
		int k = probe(x, i);
		if (T[k].flag == 0 || T[k].flag == 2){		// if empty or deleted..
			T[k].key = x;
			T[k].flag = 1;
			return;
		}
		else
			i++;
	}
	cout << "The table is full..." << endl;
}

void HashTable::printTableEntry()
{
	for (int i = 0; i < m; i++)
	{
		switch (T[i].flag)
		{
			case 0:
				cout << "The entry "<< i << " is empty." << endl;
				outputFile << "The entry "<< i << " is empty." << endl;
				break;
			case 1:
				cout << "The entry "<< i << " is " << T[i].key << endl; 
				outputFile << "The entry "<< i << " is " << T[i].key << endl; 
				break;
			case 2:
				cout << "The entry "<< i << " is " << T[i].key << ", but is deleted."<< endl; 
				outputFile << "The entry "<< i << " is " << T[i].key << ", but is deleted."<< endl; 
				break;
			default:
				cout << "No such entry flag.\n";
				outputFile << "No such entry flag.\n";
		}
	}
	cout << endl;
}

int HashTable::hash(int x)
{
	return x % m;
}

int HashTable::probe(int x, int i)
{
	return linearProbe(x, i);
}

int HashTable::linearProbe(int x, int i)
{
	return (hash(x) + i) % m;
}


HashTable::HashTable(int size)
{
	m = size;
	T = new Element[m];
	for(int i = 0; i < m; i++)
		T[i].flag = 0;
}

int main()
{
	//open files
	ifstream inputFile;
	inputFile.open("hw5_Q2_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	//outputFile has been defined as a global variable
	outputFile.open("hw5_Q2_output.txt");
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
			int k = hashtable.search(x); 
			if (k != -1)
			{
				cout << "The key " << x << " is in T[" << k <<"]." << endl;
				outputFile << "The key " << x << " is in T[" << k <<"]." << endl;
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
	hashtable.printTableEntry();

	inputFile.close();
	outputFile.close();

	return 1;
}
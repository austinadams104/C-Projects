#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int ARRAY_SIZE = 50;// defined as a global constant for simplicity
ofstream outputFile;//defined as a global variable

class Heap
{
	private:
		int array_size;// the size of the array, index from 0 to array_size-1
		int heap_size;// keys of the heap are in H[1...heap_size]; the index of H starts from 1 for convenience
		int * H;
		int left(int i) { return i * 2; } //the index of the left child of node i
		int right(int i) { return 2 * i + 1; } //the index of the right child of node i
		int parent(int i) { return i / 2; }//the index of the parent of node i
		void percolateDown(int);

	public:
		Heap(int * A, int num);
		Heap(int array_size_input = 5);
		~Heap() { delete [] H; };
		int deleteMin();
		void insert(int);
		void printHeap();
		void buildHeap();
		void heapSort();
};

//sort all elements of the heap and still use H to store the sorted list in descending order
void Heap::heapSort()
{
	int n = heap_size;
	for (int i = heap_size; i > 0; i --)
		H[i] = deleteMin();

	cout << endl;
	outputFile << endl;
	cout << "The following are the keys in the heap sorted in descending order: " << endl;
	outputFile << "The following are the keys in the heap sorted in descending order: " << endl;

	for (int i = 1; i <= n; i++)
	{
		cout << H[i] << " ";
		outputFile << H[i] << " ";
	}

	cout << endl;
	outputFile << endl;
}

int Heap::deleteMin()
{
	int temp = H[1];
	H[1] = H[heap_size];
	heap_size--;
	percolateDown(1);
	return temp;
}

//build the heap for the elements in H[1...heap_size] and you can make
//use of the procedure percolateDown(int i), as discussed in class
void Heap::buildHeap()
{
	for (int i = heap_size / 2; i > 0; i--){
		percolateDown(i);
	}
}

//percolate down from H[i]
void Heap::percolateDown(int i)
{
	while (left(i) <= heap_size){
		int min = left(i);
		if (right(i) <= heap_size){
			if (H[right(i)] < H[left(i)]){
				min = right(i);
			}
		}
		if (H[i] < H[min]){
			break;
		}
		else{
			swap(H[i], H[min]);
			i = min;
		}
	}
}

//insert a new key x into the heap H
void Heap::insert(int x)
{
	heap_size++;
	H[heap_size] = x;
	int i = heap_size;
	while (i > 1 && H[i] < H[parent(i)]){
		swap(H[i], H[parent(i)]);
		i = parent(i);
	}
}
//A is an array, num is the number of elements in A
Heap::Heap(int *A, int num)
{
	array_size = ARRAY_SIZE;
	H = new int [array_size];
	for (int i = 1; i <= num; i++)
		H[i] = A[i-1]; //as the index of A starts from 0, so we use i-1 here for A

	heap_size = num;
	buildHeap();
}

void Heap::printHeap()
{
	cout << endl;
	outputFile << endl;
	cout << "The following are the keys in the heap:" << endl;
	outputFile << "The following are the keys in the heap:" << endl;
	for (int i = 1; i <= heap_size; i++)
	{
		cout << H[i] << " ";
		outputFile  << H[i] << " ";
	}
	cout << endl;
	outputFile << endl;
}

int main()
{
	int A[10] = {24, 13, 18, 31, 65, 26, 19, 68, 21, 37};

	//build a heap using the elements of array A
	Heap heap(A, 10);

	//open files
	ifstream inputFile;
	inputFile.open("hw6_Q1_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	//outputFile has been defined as a global variable
	outputFile.open("hw6_Q1_output.txt");
	if (!outputFile)
		cout << "Error opening the output file " << endl;

	string op;
	//read operations from the input file
	int x;
	while(inputFile >> op)
	{
		if (op == "insert")
		{
			inputFile >> x; // read the value x for insert
			heap.insert(x);
		}
		if (op == "deleteMin")
		{
			int temp = heap.deleteMin();
			cout << temp << endl;
			outputFile << temp << endl;
		}
	}

	//print the heap
	heap.printHeap();

	//sort all keys in the heap in descending order and print the sorted list 
	heap.heapSort();

	inputFile.close();
	outputFile.close();

	return 1;
}

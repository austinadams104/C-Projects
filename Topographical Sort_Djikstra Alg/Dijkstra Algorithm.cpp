#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//enum colorType {white, blue, red};

const int MAX = 10000;

struct Vertex
{
	int id;//the id of the vertex
	int weight; //the weight of an edge (u,v), where v is the current node and v is in the adj list of vertex u
	Vertex * next;
	Vertex(int id_input, int weight_input, Vertex * next_input = NULL)
	{
		id = id_input;
		weight = weight_input;
		next = next_input;
	}
};

class Heap
{
private:
		int array_size;// the size of the array, index from 0 to array_size-1
		int heap_size;// elements are in H[1...heap_size]
		int * map;//map[i] is the index of the value A[i+1] in the current heap H
		int * inv_map;//invMap[i] is the index of H[i] in the intial heap, i.e., invMap[i]-1 is its index in A
		int * H;
		int left(int i) { return i * 2; }
		int right(int i) { return 2 * i + 1; }
		int parent(int i) { return i / 2; }
		void percolateDown(int);
		void swap(int i, int j);
public:
		Heap(int * A, int num);
		~Heap() { delete[] H; };
		int deleteMin();
		void insert(int);
		void printHeap();
		void printArray();
		void buildHeap();
		int decreaseKey(int j, int new_key);// j is the index of A, return the index of the smallest key in A
		int getHeapsize(){ return heap_size; }
	};
void Heap::printHeap()
	{
		for (int i = 1; i <= heap_size; i++)
			cout << H[i] << " ";
		cout << endl;
	}


Heap::Heap(int *A, int num)
	{
		array_size = num + 1;
		H = new int[array_size];
		map = new int[array_size];
		inv_map = new int[array_size];
		for (int i = 1; i < array_size; i++)
		{
			H[i] = A[i - 1];
			map[i] = i;
			inv_map[i] = i;
		}

		heap_size = num;
		buildHeap();
	}

void Heap::buildHeap()
	{
		for (int i = heap_size / 2; i > 0; i--)
			percolateDown(i);
	}

void Heap::percolateDown(int i)	{
	int min;
	while (left(i) <= heap_size)
	{
		//min records the index of the smaller child
		min = left(i);
		if (right(i) <= heap_size && H[right(i)] < H[left(i)])
			min = right(i);
		if (H[i] < H[min])
			break;
		else
		{
			swap(i, min);
			i = min;
		}
	}
}

void Heap::swap(int i, int j)
	{
		int temp = H[i];
		H[i] = H[j];
		H[j] = temp;

		map[inv_map[i]] = j;
		map[inv_map[j]] = i;

		int index = inv_map[i];
		inv_map[i] = inv_map[j];
		inv_map[j] = index;
	}

	//return the index of the smallest key in A
int Heap::deleteMin()
	{
		int index = inv_map[1] - 1;
		//H[1] = H[heap_size];
		swap(1, heap_size);

		heap_size--;
		percolateDown(1);

		return index;
	}

int Heap::decreaseKey(int j, int new_key)
{
	int i = map[j + 1];//obtain the index of the value in the current H
	H[i] = new_key;
	//percolate up
	while (i > 1 && H[i] < H[parent(i)])
	{
		swap(i, parent(i));
		i = parent(i);
	}
	return i;
}
class Graph
{
	private:
		int * pre;//the predecessor array (a dynamic array)
		int * dis;//the shortest path distance array (a dynamic array)

	public:
		int n;//the number of vertices, the ids of the vertices are from 0 to n-1  
		Vertex ** adj;//adj[i] points the head of the adjacency list of vertex i
		
		Graph(int n_input);//the class constructor

		void Dijkstra(int s);//compute a shortest path tree from the source vertex s in a general graph

		void printSP(int source, int v);//print the shortest path from the source vertex to v
		int getSPdis(int v);//return the shortest path distance from the source vertex to v

		void setAdjLists(int * adjM);// convert the adj matrix M to adj list
		void printAdjLists();//print the adj list of the graph
};

//please complete the following function, s is the source vertex;
//essentially, your task is to compute the correct information for the two
//arrays pre[0...n-1] and dis[0...n-1]
void Graph::Dijkstra(int s = 0)
{
	for (int i = 0; i < n; i++)
	{
		dis[i] = MAX;
		pre[i] = n;          // n means NULL because there is no vertex whose id is n
	}

	dis[s] = 0; //the distance of the source is 0

	//implement the priority queue by a heap 
	Heap Q(dis, n);

	while (Q.getHeapsize() > 0)//Q is not empty
	{
		//Extract-Min(Q);
		int u = Q.deleteMin();

		//visit the adj list of u
		Vertex * v = adj[u];
		while (v != NULL)
		{
			if (dis[v->id] > dis[u] + v->weight)//v->weight = w(u,v)
			{
				dis[v->id] = dis[u] + v->weight;
				Q.decreaseKey(v->id, dis[v->id]);
				pre[v->id] = u;
			}
			v = v->next;
		}
	}
}

//return the shortest path distances computed by the Dijkstra's algorithm
int Graph::getSPdis(int v)
{
	return dis[v];
}

void Graph::printSP(int source, int v)
{
	if (v == source)
		cout << source;
	else
	{
		printSP(source, pre[v]);
		cout << "->" << v;
	}
}


Graph::Graph(int n_input)
{
	n = n_input;
	adj = new Vertex * [n];
	//initialize adj[i] to NULL
	for(int i = 0; i < n; i++)
		adj[i] = NULL;
	
	//create the two dynamic arrays of size n for the n vertices
	pre = new int [n];
	dis = new int [n];
}

void Graph::setAdjLists(int * adjM)
{
	for(int i = 0; i < n; i++)
	{
		//create the i-th adj list adj[i], note that I consider the
		//vertices in the reverse order from n-1 to 0 so that I can
		//construct the list in order from 0 to n-1 because a new
		//vertex is always inserted to the front
		for(int j = n-1; j >= 0; j--)
		{
			if(adjM[i * n + j] > 0)
			{
				//create a new node and add it to the front of adj[i]
				Vertex * v = new Vertex (j, adjM[i * n + j]);
				v->next = adj[i];
				adj[i] = v;
			}
		}
	}
}

void Graph::printAdjLists()
{
	cout << "The following are the adjacent lists with edge weights in the parentheses:" << endl;
	for(int i = 0; i < n; i++)
	{
		cout << "Adj list of vertex " << i << ": "; 
		Vertex *v = adj[i];
		while(v != NULL)
		{
			if (v->next != NULL)
				cout << v->id << "(" << v->weight << ")" << "->";
			else
				cout << v->id << "(" << v->weight << ")";
			v = v->next;
		}
		cout << endl;
	}

	cout << endl;
}

int main()
{
	//open files
	ifstream inputFile;
	inputFile.open("hw9_Q2_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;

	int n;
	//read the number in the first line, which is the number of vertices of
	//the input graph
	inputFile >> n;

	cout << "The number of vertices is: " << n << endl << endl;

	//next we read the adjacency matrix from the file to an array M.
	//Here we use a one-dimensional array to simulate a two-dimesional
	//adjacency matrix because we already know the length of each row
	//is n
	int * M = new int[n * n];
	int i = 0;
	int value;
	while (inputFile >> value)
	{
		M[i] = value;
		i++;
	}
	inputFile.close();

	//uncomment the following piece of code if you want to check
	//whether the adj matrix is read correctly from the input file
	/*
	cout << "The following is the matrix:" << endl;
	for(int i = 0; i < n * n; i++)
	{
	if(i % n == 0)
	cout << endl;
	cout << M[i] << " ";
	}
	cout << endl;
	*/

	//initialize the graph by passing n to it
	Graph graph(n);
	graph.setAdjLists(M);

	//uncomment the following line if you want to print the adj lists
	graph.printAdjLists();

	int source_vertex = 0;

	graph.Dijkstra(source_vertex);

	//after the Dijkstra's algorithm, the following for loop is supposed to
	//print the shortest paths from the source vertex to all other
	//vertices
	for (int i = 1; i <= n - 1; i++)
	{
		cout << "The shortest path from the source vertex " << source_vertex << " to vertex " << i << ": ";
		graph.printSP(source_vertex, i);// print the shortest path from 0 to 5 with source 0
		cout << endl;
	}

	cout << endl;

	//the following for loop is supposed to
	//print the shortest path distances from the source vertex to all other
	//vertices
	for (int i = 1; i <= n - 1; i++)
	{
		cout << "The shortest path distance from the source vertex " << source_vertex << " to vertex " << i << " is: ";
		cout << graph.getSPdis(i) << endl;
	}

	return 0;
}
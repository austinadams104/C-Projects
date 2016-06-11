#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum colorType {white, blue, red};

struct Vertex
{
	int id;//the id of the vertex
	Vertex * next;
	Vertex(int id_input, Vertex * input_next = NULL)
	{
		id = id_input;
		next = input_next;
	}
};

class Graph
{
	private:
		colorType * color; // record the colors of the vertices during BFS; if you are not comfortable with enum type, you may simply define color as an integer type and then use 0, 1, 2, to reresent the three colors 
		int * pre; // record the predecessors during BFS
		int * dis;// record the shortest path distances during BFS

	public:
		int n;//the number of vertices, the ids of the vertices are from 0 to n-1  
		Vertex ** adj;//adj[i] points the head of the adjacency list of vertex i, for i from 0 to n-1

        //the following two functions are for the BFS traversal as we discussed in class, but you may choose to use different ways
		//void BFS(int id);//BFS traversal, id is the source vertex, with default 0
		//void BFSVisit(int id);//the function that acutually does BFS, search a particular connected component from id 

		Graph(int n_input);//constructor
		void setAdjLists(int * adjM);//build the adjacency lists from the adecency matrix adjM
		void printAdjLists();//print the adjacency lists of the graph

		//void printSP(int source, int v);//this is the function I would use to print shortest path from the source to v

};

//initialize the graph by getting the number of vertices from n_input
Graph::Graph(int n_input)
{
	n = n_input;
	adj = new Vertex * [n];
	//initialize adj[i] to NULL
	for(int i = 0; i < n; i++)
		adj[i] = NULL;

	color = new colorType [n];//create a dynamic array for storing color in BFS
	pre = new int [n];//create a dynamic array for storing predecessors in BFS
	dis = new int [n];//create a dynamic array for storing shortest path distances in BFS
}

//construct the adj lists from the adj matrix adjM; note that the matrix adjM is
//actually a one-dimenional array, which is used to simulate the two-dimensional
//adjacent matrix
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
			if(adjM[i * n + j] == 1)
			{
				//create a new node and add it to the front of adj[i]
				Vertex * v = new Vertex (j);
				v->next = adj[i];
				adj[i] = v;
			}
		}
	}
}

//print the adj lists
void Graph::printAdjLists()
{
	for(int i = 0; i < n; i++)
	{
		cout << "Adj list of vertex " << i << ": "; 
		Vertex *v = adj[i];
		while(v != NULL)
		{
			if (v->next != NULL)
				cout << v->id << "->";
			else
				cout << v->id;
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
	inputFile.open("hw8_Q5_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	int n;
	//read the number in the first line, which is the number of vertices of
	//the input graph
	inputFile >> n;

	//cout << "The number of vertices is: " << n << endl;

	//Next we read the adjacency matrix from the file to an array M.
	//Because there is no way to create a dyanimic two-dimensional array, I
	//choose to use a one-dimesional array to simulate a two-dimesional
	//adjacency matrix because we already know the length of each row
	//is n. In this way, M[i,j] is actually M[i*n + j]. 
	int * M = new int [n * n];
	int i = 0;
	int value;
	while(inputFile >> value)
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

	//compute the adjacency lists from the matrix M
	graph.setAdjLists(M);

	//uncomment the following line if you want to print out the adj lists
	//graph.printAdjLists();

	return 0;
}


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
		colorType * color;
		int * pre;
		int * dis;

	public:
		int n;//the number of vertices, the ids of the vertices are from 0 to n-1  
		Vertex ** adj;//adj[i] points the head of the adjacency list of vertex i

        //the following are two functions I would use for the DFS        
		void DFS(int);//depth first search, id is the source vertex, with default 0 
		void DFSVisit(int);//the function that acutually does depth first search, search a particular component 

		Graph(int n_input);//constructor
		void setAdjLists(int * adjM);//build the adjacency lists from the adecency matrix adjM
		void printAdjLists();//print the adjacency lists of the graph
};

void Graph::DFS(int s){
	for (int i = 0; i <= n - 1; i++){
		color[i] = white;
		pre[i] = NULL;
	}
	cout << "The following is the DFS traversal vertex order, staring from vertex 0:\n";
	DFSVisit(s);
	for (int i = 0; i <= n - 1; i++){
		if (color[i] == white){
			DFSVisit(i);
		}
	}
}
void Graph::DFSVisit(int s){
	color[s] = blue;
	int i = s;
	cout << i << " ";
	Vertex *v = adj[s];
	while (v != NULL){
		if (color[v->id] == white){
			pre[v->id] = s;
			DFSVisit(v->id);
		}
		v = v->next;
	}
	color[s] = red;
}

//initialize the graph by getting the number of vertices from n_input
Graph::Graph(int n_input)
{
	n = n_input;
	adj = new Vertex * [n];
	//initialize adj[i] to NULL
	for(int i = 0; i < n; i++)
		adj[i] = NULL;
	
	color = new colorType [n];//define the color array for DFS
	pre = new int [n]; //define the predecessor array for DFS
}

//construct the adj lists from the adj matrix adjM
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
	inputFile.open("hw8_Q6_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	int n;
	//read the number in the first line, which is the number of vertices of
	//the input graph
	inputFile >> n;

	//cout << "The number of vertices is: " << n << endl;

	//next we read the adjacency matrix from the file to an array M.
	//Here we use a one-dimensional array to simulate a two-dimesional
	//adjacency matrix because we already know the length of each row
	//is n
	int * M = new int [n * n];
	int i = 0;
	int value;
	while(inputFile >> value)
	{
		M[i] = value;
		i++;
	}

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
	graph.DFS(0);
	//uncomment the following line to print the adjacency lists
	//graph.printAdjLists();

	inputFile.close();
	return 0;
}


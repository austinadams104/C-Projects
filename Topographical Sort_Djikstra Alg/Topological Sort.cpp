#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
	public:
		int n;//the number of vertices, the ids of the vertices are from 0 to n-1  
		Vertex ** adj;//adj[i] points the head of the adjacency list of vertex i

		void topSort();//do topological sort

		Graph(int n_input);//constructor
		void setAdjLists(int * adjM);//build the adjacency lists from the adecency matrix adjM
		void printAdjLists();//print the adjacency lists of the graph
};

//please finish the following function, which is supposed to print out
//the topological order of the vertices
void Graph::topSort()
{
	//use an array to store the indegrees of the vertices
	int * indegree = new int[n];

	//initialize their indegrees to zero
	for (int i = 0; i < n; i++)
		indegree[i] = 0;

	//compute the indegree of each vertex
	for (int u = 0; u < n; u++)
	{
		Vertex * v = adj[u];
		while (v != NULL)
		{
			indegree[v->id] ++;
			v = v->next;
		}
	}

	//use an array Q to implement a queue
	int * Q = new int[n];
	int front, rear;
	front = -1;//indicate Q is empty

	for (int i = 0; i < n; i++)
	{
		if (indegree[i] == 0)
		{
			if (front == -1)//the queue is empty
			{
				front = rear = 0;
				Q[0] = i;
			}
			else
			{
				rear++;
				if (rear >= n)
					cout << "error enqueuing...\n";
				else
					Q[rear] = i;
			}

		}
	}

	int counter = 0; //record the number of vertices that have been printed out

	while (front != -1 && front <= rear)//the queue is not empty
	{
		//dequque
		int u = Q[front];
		front++;

		//print the vertex
		cout << u << " ";
		counter++;

		//check the adjacecy list of u
		Vertex * v = adj[u];
		while (v != NULL)
		{
			indegree[v->id] --;
			if (indegree[v->id] == 0)
			{
				//enqueue v
				rear++;
				if (rear >= n)
					cout << "error enqueuing...\n";
				else
					Q[rear] = v->id;
			}

			v = v->next;
		}
	}

	cout << endl;

	//check whether the graph is a DAG
	if (counter < n)
		cout << "The graph is not a DAG.\n";
}

Graph::Graph(int n_input)
{
	n = n_input;
	adj = new Vertex * [n];
	//initialize adj[i] to NULL
	for(int i = 0; i < n; i++)
		adj[i] = NULL;
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
	inputFile.open("hw9_Q1_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	int n;
	//read the number in the first line, which is the number of vertices of
	//the input graph
	inputFile >> n;

	cout << "The number of vertices is: " << n << endl;

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

	cout << "The following is a topological order:" << endl;
	graph.topSort();

	cout << endl;

	return 0;
}

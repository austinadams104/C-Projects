#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream outputFile; //outputFile is defined as a global variable

struct TreeNode
{
	int key;
	TreeNode *left;				
	TreeNode *right;				

	//constructor of the struct
	TreeNode (int key1, TreeNode *left1 = NULL, TreeNode *right1 = NULL)
	{
		key = key1;
		left = left1;
		right = right1;
	}
};

class BST
{
	private:
		TreeNode * root; // the root of the tree
		void destroySubTree(TreeNode *);// delete all nodes of the tree
		void displayPreOrder(TreeNode *); //pre-order traversal
		void displayInOrder(TreeNode *);//in-order traversal
		void displayPostOrder(TreeNode *); //post-order traversal
		void remove(TreeNode * & v, int x); 

	public:
		BST() { root = NULL; }
		~BST() { destroySubTree(root); }
		void insert(int x);
		bool search(int x);
		void displayPreOrder() { displayPreOrder(root); }// pre-order traversal
		void displayInOrder() { displayInOrder(root); }//in-order traversal
		void displayPosteOrder() { displayPostOrder(root); }//post-order traversal
		void remove(int x) { remove(root,x); }
		int findMin();
};

void BST::destroySubTree(TreeNode *v)
{
	if (v == NULL)
		return;
	else
	{
		destroySubTree(v->left);
		destroySubTree(v->right);
		delete v;
	}
}

void BST::displayPreOrder(TreeNode *v)
{
	if (v != NULL)
	{
		cout << v->key << "  ";
		outputFile << v->key << "  ";
		displayPreOrder(v->left);
		displayPreOrder(v->right);
	}
}

void BST::displayInOrder(TreeNode *v)
{
	if (v != NULL)
	{
		displayInOrder(v->left);
		cout << v->key << "  ";
		outputFile << v->key << "  ";
		displayInOrder(v->right);
	}
}

void BST::displayPostOrder(TreeNode *v)
{
	if (v != NULL)
	{
		displayPostOrder(v->left);
		displayPostOrder(v->right);
		cout << v->key << "  ";
		outputFile << v->key << "  ";
	}
}


int BST::findMin()
{
}


void BST::insert(int x)
{
}


bool BST::search(int x)
{
}

void BST::remove(TreeNode * & v, int x)
{
}

int main()
{
	BST tree;

	string inputFileName = "hw3_Q4_input.txt"; // input file with operations 
	string outputFileName = "hw3_Q4_output.txt"; // output file

	//open files
	ifstream inputFile;
	inputFile.open(inputFileName.c_str());
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	outputFile.open(outputFileName.c_str());
	if (!outputFile)
		cout << "Error opening the output file " << endl;

	//read operations from the input file
	string op;
	int x;
	while(inputFile >> op)
	{
		if (op == "insert")
		{
			inputFile >> x; // read the value x for insert
			tree.insert(x);
		}
		if (op == "remove")
		{
			inputFile >> x; // read the value x for remove 
			tree.remove(x);
		}
		if (op == "search")
		{
			inputFile >> x;
			if (tree.search(x) == true)
			{
				cout << "The key " << x << " is in the current tree.\n";
				outputFile << "The key " << x << " is in the current tree.\n";
			}
			else// x is not in the tree
			{
				cout << "The key " << x << " is not in the current tree.\n";
				outputFile << "The key " << x << " is not in the current tree.\n";
			}
		}
		if (op == "findMin")
		{
			cout << "The smallest key in the current tree is " << tree.findMin() << endl;
			outputFile << "The smallest key in the current tree is " << tree.findMin() << endl;
		}
	}

	//print the pre-odrder traversal to both screen and the outputfile
	cout << "The pre-order traversal list is: " << endl;
	outputFile << "The pre-order traversal list is: " << endl;
	tree.displayPreOrder();
	cout << endl;
	outputFile << endl;

	//print the in-odrder traversal to both screen and the outputfile
	cout << "The in-order traversal list is: " << endl;
	outputFile << "The in-order traversal list is: " << endl;
	tree.displayInOrder();
	cout << endl;
	outputFile << endl;

	inputFile.close();
	outputFile.close();

	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream outputFile; //outputFile is defined as a global variable

struct TreeNode
{
	int value;
	TreeNode *left;				
	TreeNode *right;				

	//constructor of the struct
	TreeNode (int key, TreeNode *left1 = NULL, TreeNode *right1 = NULL)
	{
		value = key;
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
		void insert(TreeNode * & v, int x);
		bool search(TreeNode * & v, int x);
	public:
		BST() { root = NULL; }
		~BST() { destroySubTree(root); }
		void insert(int x) { insert(root, x); }
		bool search(int x) { return search(root, x); }
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
		cout << v->value << "  ";
		outputFile << v->value << "  ";
		displayPreOrder(v->left);
		displayPreOrder(v->right);
	}
}

void BST::displayInOrder(TreeNode *v)
{
	if (v != NULL)
	{
		displayInOrder(v->left);
		cout << v->value << "  ";
		outputFile << v->value << "  ";
		displayInOrder(v->right);
	}
}

void BST::displayPostOrder(TreeNode *v)
{
	if (v != NULL)
	{
		displayPostOrder(v->left);
		displayPostOrder(v->right);
		cout << v->value << "  ";
		outputFile << v->value << "  ";
	}
}


int BST::findMin()
{
	if (root == NULL) return -1;
	TreeNode *v = root;
	while (v->left != NULL)
	{
		v = v->left;
	}
	return v->value;
}


void BST::insert(TreeNode * & v, int x)
{
	if (v == NULL){
		v = new TreeNode(x);
		return;
	}
	if (v->value == x) return;
	if (x < v->value) 
		insert(v->left, x);
	else 
		insert(v->right, x); 
}

bool BST::search(TreeNode * & v, int x)
{
	if (v == NULL) return false;
	if (v->value == x) return true;
	if (x < v->value) return search(v->left, x);
	if (x > v->value) return search(v->right, x);
}

void BST::remove(TreeNode * & v, int x)
{
	if (v == NULL) return;
	if (x < v->value) remove(v->left, x);
	if (x > v->value) remove(v->right, x);
	if (x == v->value){
		if (v->left == NULL){
			TreeNode *temp = v;
			v = v->right;
			delete temp;
			return;
		}
		if (v->right == NULL){
			TreeNode* temp = v;
			v = v->left;
			delete temp;
			return;
		}
		if (v->left != NULL && v->right != NULL){
			TreeNode *u = v->right;
			while (u->left != NULL){
				u = u->left;
			}
			v->value = u->value;
			remove(u, u->value);
		}
	}
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

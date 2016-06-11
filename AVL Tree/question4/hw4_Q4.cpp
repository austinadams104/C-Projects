#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream outputFile; //outputFile is defined as a global variable

struct AvlNode
{
	int key;
	int height;
	AvlNode *left;				
	AvlNode *right;				

	AvlNode (int key1, int height1 = 0, AvlNode *left1 = NULL, AvlNode *right1 = NULL)
	{
		key = key1;
		height = height1;
		left = left1;
		right = right1;
	}
};

class AvlTree 
{
	private:
		AvlNode * root;
		void destroySubTree(AvlNode * v);//destroy a subtree rooted at v
		void displayPreOrder(AvlNode *);//pre-order traversal
		void displayInOrder(AvlNode *);//in-order traversal
		void displayPostOrder(AvlNode *);//post-order traversal
		void remove(AvlNode * &, int);//remove
		void insert(AvlNode * &, int);//insert
		void balance(AvlNode * &); //make the tree balanced after each insert/remove
		void rightRotate (AvlNode * &);//right rotation
		void leftRotate (AvlNode * &);//left rotation
		void doubleLeftRightRotate (AvlNode * &);//left right double rotation
		void doubleRightLeftRotate (AvlNode * &);//right left double rotation

	public:
		AvlTree() { root = NULL; }
		~AvlTree() { destroySubTree(root); }
		AvlNode * search(int);
		void displayPreOrder() { displayPreOrder(root); }
		void displayInOrder() { displayInOrder(root); }
		void displayPostOrder() { displayPostOrder(root); }
		void insert(int x) { insert(root,x); }//insert a new key x
		void remove(int x) { remove(root,x); }//remove a key x
		int getHeight(AvlNode * v);//return the height of node v
		int getTreeHeight() {return getHeight(root);}//return the height of the tree
		int getRoot() {return root->key;}//return the root
};

int AvlTree::getHeight(AvlNode * v)
{
	if (v == NULL)
		return -1;
	else
		return v->height;
}

void AvlTree::destroySubTree(AvlNode *v)
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

void AvlTree::insert(AvlNode * & v, int x)
{
	if (v == NULL)
		v = new AvlNode(x);
	else if (x == v->key)
		return;
	else if (x < v->key)
		insert(v->left, x);
	else
		insert(v->right, x);

	balance(v);
}

//please complete the following five functions
void AvlTree::balance(AvlNode * & v)
{
}

void AvlTree::rightRotate (AvlNode * & k2)
{
}

void AvlTree::leftRotate (AvlNode * & k1)
{
}

void AvlTree::doubleLeftRightRotate (AvlNode * & v)
{
}

void AvlTree::doubleRightLeftRotate (AvlNode * & v)
{
}

void AvlTree::displayPreOrder(AvlNode *v)
{
	if (v != NULL)
	{
		cout << v->key << "  ";
		outputFile << v->key << "  ";
		displayPreOrder(v->left);
		displayPreOrder(v->right);
	}
}

void AvlTree::displayInOrder(AvlNode *v)
{
	if (v != NULL)
	{
		displayInOrder(v->left);
		cout << v->key << "  ";
		outputFile << v->key << "  ";
		displayInOrder(v->right);
	}
}

void AvlTree::displayPostOrder(AvlNode *v)
{
	if (v != NULL)
	{
		displayPostOrder(v->left);
		displayPostOrder(v->right);
		cout << v->key << "  ";
		outputFile << v->key << "  ";
	}
}

AvlNode * AvlTree::search(int x)
{
	AvlNode *v = root;
	while (v != NULL && v->key != x)
	{
		if (x < v->key)
			v = v->left;
		else
			v = v->right;
	}

	if (v != NULL)
		return v;
	else
		return NULL;
}

void AvlTree::remove(AvlNode * & v, int x)
{
	if (v == NULL)
		return;
	if (x < v->key)
		remove(v->left, x);
	else if (x > v->key)
		remove(v->right, x);
	else//x == v->key
	{
		// if at least one child is NULL
		if (v->left == NULL || v->right == NULL)
		{
			AvlNode * garbageNode = v;
			if (v->right == NULL)
				v = v->left;
			else
				v = v->right;
		}
		else // v has two children
		{
			AvlNode * u = v->right;
			//find the smallest key on the right subtree of v
			while(u->left != NULL)
				u = u->left;
			//assign the key value of u to v
			v->key = u->key;
			//remove the node u from the right subtree of v
			remove(v->right,u->key);
		}
	}

	balance(v);
}

int main()
{
	AvlTree tree;
	
	//open the input file
	ifstream inputFile;
	inputFile.open("hw4_Q4_input.txt");
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	//open the output file, outputFile is defined as a global variable
	outputFile.open("hw4_Q4_output.txt");
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
		else if (op == "remove")
		{
			inputFile >> x; // read the value x for remove 
			tree.remove(x);
		}
		else
			cout << "Error reading opeartions"; 
	}

	//print the pre-odrder traversal to both screen and the outputfile
	cout << "The pre-order traversal list is: " << endl;
	outputFile << "The pre-order traversal list is: " << endl;
	tree.displayPreOrder();
	cout << endl;
	outputFile << endl;

	//print the in-order traversal to both screen and the outputfile
	cout << "The in-order traversal list is: " << endl;
	outputFile << "The in-order traversal list is: " << endl;
	tree.displayInOrder();
	cout << endl;
	outputFile << endl;
	
	//print the root and its height to both screen and the output file 
	cout << "The root is: " << tree.getRoot() << endl;
	outputFile << "The root is: " << tree.getRoot() << endl;
	cout << "The height of the tree is: " << tree.getTreeHeight() << endl;
	outputFile << "The height of the tree is: " << tree.getTreeHeight() << endl;
	
	/* The following commented code may help you debug your program.
	 * You may change "16" to other keys as you need. 
	AvlNode * v = tree.search(16);
	if (v != NULL)
	{
	    cout << "The key is found. Its height is: " << tree.getHeight(v) << endl;
		if (v->left != NULL) 
			cout << "It's left child is: " << v->left->key << "." << endl;
		else
			cout << "It does not have a left child. " << endl;
		
		if (v->right != NULL) 
			cout << "It's right child is: " << v->right->key << "." << endl;
		else
			cout << "It does not have a right child. " << endl;
	}
	else
		cout << "The key is not found." << endl;
	*/


	inputFile.close();
	outputFile.close();

	return 0;
}

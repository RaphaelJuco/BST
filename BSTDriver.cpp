// Binary Search Tree Program
// Author: Raphael Juco
// Purpose: Build a Binary Search Tree program that allows us to analyze the 
//			smallest and highest branch height, number of nodes, and the 
//			determination if the tree is balanced or complete.
//

#include <iostream>
#include <fstream>
#include <queue> 

using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
	// constructor that allows us to create a new node containing the data 
	node(int x)	
	{
		data = x;
		left = nullptr;
		right = nullptr;
	}
};

// forward declarations
void insert(node* temp, int num);
int smallestBranchHeight(node* root);
int highestBranchHeight(node* root);
int countNodes(node* root);
bool balanced(node* root);
int findDepth(node* temp);
int max(int a, int b);
bool complete(node* root);


// main()
// Precondition: file being opened must be a valid file or 
//				 it will not make the BST
// Postconditions: if file is successfully opened, rootPtr 
//				   contains the data in the file
int main() {
	node* rootPtr = nullptr; 
	int current;
	ifstream inFile;

	inFile.open("CSS343_A1_F3.txt");

	if (!inFile) {
		cout << "File cannot be opened";
		return 0;
	}
	cout << "The data set in file are: " << endl;
	while (inFile >> current) {
		if (rootPtr == nullptr) { // creates the root node 
			rootPtr = new node(current);
			cout << current << endl;
			continue;
		}
		insert(rootPtr, current);
	}
	cout << "The smallest branch height is ";
	cout << smallestBranchHeight(rootPtr) << endl;
	cout << "The highest branch height is ";
	cout << highestBranchHeight(rootPtr) << endl;
	cout << "The total nodes in the tree is ";
	cout << countNodes(rootPtr) << endl;

	if (balanced(rootPtr)) {
		cout << "The BST is balanced" << endl;
	}
	else {
		cout << "The BST is not balanced" << endl;
	}
	if (complete(rootPtr)) {
		cout << "The BST is complete" << endl;
	}
	else {
		cout << "The BST is not complete" << endl;
	}

	inFile.close();
}

// insert: inserts passed in int into the next available 
//		   empty place
// Precondition: passed in node* is the root of the tree
// Postconditions: creates a new node containing passed in 
//				   data num and is placed in the next empty 
//				   place in the tree
void insert(node* temp, int num){
	queue<node*> q;
	q.push(temp); // puts the root in a queue
	cout << num << endl;
	// order level traversal using queue
	while (!q.empty()) { 
		node* temp = q.front(); // pointer to the front of queue
		q.pop(); 
		
		if (!temp->left) { // if left is empty then 
			temp->left = new node(num); // inserts node there
			break;
		}
		else {
			q.push(temp->left); 
		}

		if (!temp->right) {
			temp->right = new node(num);
			break;
		}
		else {
			q.push(temp->right);
		}
	}
}

// smallestBranchHeight: finds the shortest path between the root
//						 to the nearest leaf node of the BST
// Precondition: none
// Postconditions: returns a non negative number
int smallestBranchHeight(node* root) {
	if (root == nullptr) {
		return 0;
	}
	if (root->left == nullptr && root->right == nullptr) {
		return 1;
	}
	if (!root->left) {
		return smallestBranchHeight(root->right) + 1;
	}
	if (!root->right) {
		return smallestBranchHeight(root->left) + 1;
	}
	return min(smallestBranchHeight(root->left), smallestBranchHeight(root->right)) + 1;
}

// highestBranchHeight: finds the longest path between the root
//						to the farthest leaf node of the BST
// Precondition: none
// Postconditions: returns a non negative number
int highestBranchHeight(node* root) {
	if (root == nullptr) {
		return 0;
	}
	else{
		int leftSide = highestBranchHeight(root->left);
		int rightSide = highestBranchHeight(root->right);

		if (leftSide > rightSide) {
			return(leftSide + 1);
		}
		else {
			return(rightSide + 1);
		}
	}
}

// countNodes: counts all the nodes in the tree, including the root
// Precondition: none
// Postconditions: returns a non negative number
int countNodes(node* root) {
	if (root == nullptr) {
		return 0;
	}
	return 1 + countNodes(root->left) + countNodes(root->right);
}

// balanced: determines if the BST is a balanced tree
// Precondition: utility functions used are pre-defined 
// Postconditions: return true if BST is balanced and false
//				   and false if not
bool balanced(node* root) {
	int leftSide, rightSide;

	if (root == nullptr) {
		return true;
	}

	leftSide = findDepth(root->left);
	rightSide = findDepth(root->right);

	int dif = abs(leftSide - rightSide);

	if (dif <= (1 && balanced(root->left) && balanced(root->right))) {
		return true;
	}

	return false;
}

// findDepth: finds the deepest that the passed in
//			  node can go to
// Precondition: none
// Postconditions: returns a non negative number 
int findDepth(node* temp) {
	if (temp == nullptr) {
		return 0;
	}
	return 1 + max(findDepth(temp->left), findDepth(temp->right));
}

// max: returns the bigger number between the two passed in ints
// Precondition: passed in int are non negative values
// Postconditions: none
int max(int a, int b){
	if (a >= b) {
		return a;
	}
	return b;
}

// complete: determines if the BST is a complete tree
// Precondition: none
// Postconditions: returns true if tree is a complete, 
//				   returns false if tree is not complete
bool complete(node* root) {
	if (root == nullptr) {
		return true;
	}

	queue<node*> q;
	q.push(root); 
	bool indicator = false; // indicates if a non full node is seen

	// order level traversal using queue
	while (!q.empty()) {
		node* temp = q.front();
		q.pop();

		// checks the left side of tree for non full nodes
		if (temp->left) {
			if (indicator == true) {
				return false;
			}
			q.push(temp->left);
		}
		else {
			indicator = true;
		}

		// checks the right side of tree for non full nodes
		if (temp->right){
			if (indicator == true) {
				return false;
			}
			q.push(temp->right);
		}
		else {
			indicator = true;
		}
	}

	return true;
}


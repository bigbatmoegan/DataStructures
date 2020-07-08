#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// define a node
struct node {
	int value;
	struct node* left;
	struct node* right;
};

// create a new node

struct node* newNode(int value)
{
	struct node* temp=(node*)malloc(sizeof(node));
	temp->value=value;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

// add nodes to the tree in order from array

struct node* addToBST(struct node* temp, int value)
{
	//create the main node if tree is empty
	if(temp==NULL)
	{
		return newNode(value);
	}
	
	//go down the tree and place value
	if(value<temp->value)
	{
		temp->left=addToBST(temp->left, value);
	}
	else if(value>temp->value)
	{
		temp->right=addToBST(temp->right, value);
	}
	
	//return unchanged pointer
	return temp;
}
//CHANGE THIS TO PRINT IN TREE ORDER
/*              65
        41                87
	17      52         76     95
6     20  45   57    71  79 92  99  */

void printLevel(struct node* tree, int row)
{
	if(row==1)
	{
		std::cout << tree->value << " ";
	}
	else if(row>1)
	{
		printLevel(tree->left, row-1);
		printLevel(tree->right, row-1);
	}
}
	

void printBST(struct node* temp)
{
	int height=4;
	for(int i=1; i<=height; i++)
	{
		printLevel(temp, i);
		std::cout << "\n";
	}
}

int kthSmall(struct node* temp, int small, int *nodeCount)
{
	//base case
	if(temp==NULL)
	{
		return 1;
	}
	int left=kthSmall(temp->left, small, nodeCount);
	//check if k is smallest on left subtree
	//
	if(left!=1)
	{
		return left;
	}
	//check if k is on current node
	if(++*nodeCount==small)
	{
		return temp->value;
	}
	//if not in here then go to right side
	return kthSmall(temp->right, small, nodeCount);
}

int main()
{
	struct node* tree;
	tree=NULL;
	tree=addToBST(tree,65);
	addToBST(tree,41);
	addToBST(tree,17);
	addToBST(tree,6);
	addToBST(tree,20);
	addToBST(tree,52);
	addToBST(tree,45);
	addToBST(tree,57);
	addToBST(tree,87);
	addToBST(tree,76);
	addToBST(tree,71);
	addToBST(tree,79);
	addToBST(tree,95);
	addToBST(tree,92);
	addToBST(tree,99);
	printBST(tree);
	int k=0;
	//create an int to track the smallest number node.
	//It increases each loop until it matches user entered k
	int small=0;
	std::cout <<"Please enter a value for k: ";
	std::cin >> k;
	std::cout << "The " << k << "th smallest element is: " << kthSmall(tree, k, &small) << std::endl;
	
	
	return 0;
}
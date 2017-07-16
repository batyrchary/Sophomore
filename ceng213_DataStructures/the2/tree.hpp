#ifndef TREE_H_
#define TREE_H_

#include<iostream>
using namespace std;
#include<string>
#include<stack>
#include<vector>

struct TNode {

	TNode(string element=NULL, TNode *fChild=NULL, TNode *nSibling=NULL, TNode *ata=NULL):value(element),firstChild(fChild),nextSibling(nSibling), parent(ata){}// yazmama gerek yok sanki default constructor halledyo gibi

	string      value;		// node value
	TNode	*firstChild;		// pointer to left child
	TNode	*nextSibling;		// pointer to right child
	TNode	*parent;
};

class Tree {

public:
Tree();
Tree(string element);
void setWord(string element);
void insert(string parent, string newN);
void printSubClass(string node);
void printSuperClass(string node);       
void printIntermediateClass(string node1, string node2);


void printWordNet(TNode *node, int space);

public:
	TNode *root;	// root node of the tree
	stack<TNode*> s1;
	stack<TNode*> s2;
	vector<TNode*> vb;

};


#endif






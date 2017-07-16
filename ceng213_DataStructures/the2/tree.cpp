#include "tree.hpp"
#include<iostream>
#include<stack>
#include<string>
using namespace std;

Tree::Tree()
{
	root=new TNode();
}

Tree::Tree(string element)
{
	root=new TNode(element);
	s1.push(root);
}


void Tree::insert(string parent, string newN)
{
	TNode *tmp;
	TNode *New = new TNode(newN);

	while(!s1.empty())
	{
		tmp=s1.top();
		s2.push(s1.top());
		s1.pop();
		
		if(tmp->value == parent)
		{	
			break;
		}
	}
	while(!s2.empty())
	{
		s1.push(s2.top());
		s2.pop();
	}

	
	New->parent=tmp;  					//Root kendi kendine parent degil cunku biz root i constructorda halledyoz

	if(tmp->firstChild == NULL)
	{		
		tmp->firstChild=New;
		s1.push(New);	
	}	
	else
	{
		tmp=tmp->firstChild;
		while(tmp->nextSibling != NULL)
			tmp=tmp->nextSibling;
		tmp->nextSibling=New;
		s1.push(New);
	}
	

}
      


void Tree::printSubClass(string node)
{
	TNode *tmp;

	while(!s1.empty())
	{
		tmp=s1.top();
		s2.push(s1.top());
		s1.pop();
		
		if(tmp->value == node)
		{	
			break;
		}
	}
	while(!s2.empty())
	{
		s1.push(s2.top());
		s2.pop();
	}
	
	vb.push_back(tmp);
	int i=0;
	
	while(i<vb.size())
	{
		tmp=vb[i];
		if(tmp->firstChild)
		{	
			tmp=tmp->firstChild;
			vb.push_back(tmp);
			while(tmp->nextSibling != NULL)
			{
				tmp=tmp->nextSibling;
				vb.push_back(tmp);
			}
		}
		i=i+1;					
	}
	
	for(int ii=0; ii<vb.size(); ii++)
		cout<<vb[ii]->value<<endl;
	
	while(!vb.empty())
		vb.pop_back();
}


void Tree::printSuperClass(string node)
{
	TNode *tmp;

	while(!s1.empty())
	{
		tmp=s1.top();
		s2.push(s1.top());
		s1.pop();
		
		if(tmp->value == node)
		{	
			break;
		}
	}
	while(!s2.empty())
	{
		s1.push(s2.top());
		s2.pop();
	}
	
	while(tmp->parent !=NULL)
	{
		cout<<tmp->value;
		cout<<" "<<"<"<<" ";
		tmp=tmp->parent;
	}
	cout<<tmp->value<<endl;
}

void Tree::printIntermediateClass(string node1, string node2)
{
	TNode *tmp1;

	while(!s1.empty())
	{
		tmp1=s1.top();
		s2.push(s1.top());
		s1.pop();
		
		if(tmp1->value == node1)
		{	
			break;
		}
	}
	while(!s2.empty())
	{
		s1.push(s2.top());
		s2.pop();
	}
TNode *tmp2;

	while(!s1.empty())
	{
		tmp2=s1.top();
		s2.push(s1.top());
		s1.pop();
		
		if(tmp2->value == node2)
		{	
			break;
		}
	}
	while(!s2.empty())
	{
		s1.push(s2.top());
		s2.pop();
	}

	while(tmp1->value != tmp2->value)
	{
		cout<<tmp1->value<<" "<<"<"<<" ";
		tmp1=tmp1->parent;
	}
	cout<<tmp1->value<<endl;

}


void Tree::printWordNet(TNode *node, int space)
{

	if(node != NULL)
	{
		for(int i=0;i<space;i++)
		{
			cout<<" ";
		}
		cout<<node->value<<endl;	
		printWordNet(node->firstChild,space+2);
		printWordNet(node->nextSibling,space);		
	}
}




/*
int main(){

Tree t1("standard");
t1.insert("standard","scale");
t1.insert("scale","richter_scale");
t1.insert("standard","medium_of_exchange");
t1.insert("medium_of_exchange","currency");
t1.insert("currency","coin");
t1.insert("medium_of_exchange","money");
t1.insert("money","fund");
t1.insert("coin","nickel");
t1.insert("coin","dime");


t1.printSubClass("standart");
cout<<endl<<"nextTASK"<<endl<<endl;
t1.printSuperClass("fund");
cout<<endl<<"nextTASK"<<endl<<endl;
t1.printIntermediateClass("fund","medium_of_exchange");

cout<<endl<<"nextTASK"<<endl<<endl;
t1.printWordNet(t1.root,0);

/*
cout<<(t1.root)->value<<endl;
cout<<(t1.root)->firstChild->value<<endl;
cout<<(t1.root)->firstChild->nextSibling->value<<endl;
cout<<(t1.root)->firstChild->firstChild->value<<endl;
cout<<(t1.root)->firstChild->firstChild->nextSibling->value<<endl;
cout<<(t1.root)->firstChild->nextSibling->firstChild->value<<endl;
*/

//return 0;}

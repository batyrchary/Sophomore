#include"wordnet.hpp"
#include"tree.hpp"
#include<iostream>
using namespace std;
#include <fstream>
#include <string>
#include<cstring>


void WordNet::BuildWordNet(string name)
{
  ifstream file;
    string line;

    file.open(name.c_str());
    getline(file, line);



Tree *t1 = new Tree(line);

this->setRoot(t1);

   while (!file.eof())
    {
		getline(file, line);
		if(2<line.length())
		{		
			string newN=line.substr(0,line.find(" "));
			line=line.substr(line.find(" ")+1,line.length());
			string parent=line.substr(line.find(" ")+1,line.length());
			root->insert(parent,newN);
		}
   }

    file.close();


}

void WordNet::HandleTask(string name)
{
		
		int indexOfSpace=name.length();		
		indexOfSpace=name.find(" ");
		string command=name.substr(0,indexOfSpace);
		
		name=name.substr(indexOfSpace+1,name.length());
		indexOfSpace=name.length();
		indexOfSpace=name.find(" ");
		
		string w1=name.substr(0,indexOfSpace);
		
		name=name.substr(indexOfSpace+1,name.length());
		indexOfSpace=name.length();
		string w2=name;

	if(command=="PrintWordNet")
	{
		(this->getRoot())->printWordNet(this->getRoot()->root,0);
	}
	else if(command=="PrintSubclasses")
	{
		(this->getRoot())->printSubClass(w1);
		
	}
	else if(command=="PrintSuperclasses")
	{
		(this->getRoot())->printSuperClass(w1);

	}
	else if(command=="PrintIntermediateClasses")
	{
		(this->getRoot())->printIntermediateClass(w1,w2);
	}
}


/*
int main(){

WordNet* object=new WordNet();

object->BuildWordNet("relations.txt");



//(object->getRoot())->printWordNet(object->getRoot()->root,0);
//(object->getRoot())->printSubClass("standard");
//(object->getRoot())->printSubClass("currency");
//(object->getRoot())->printSubClass("fund");
//(object->getRoot())->printSuperClass("standard");
//(object->getRoot())->printSuperClass("fund");
//(object->getRoot())->printSuperClass("currency");
//(object->getRoot())->printIntermediateClass("medium_of_exchange","medium_of_exchange");
//(object->getRoot())->printIntermediateClass("fund","medium_of_exchange");
//(object->getRoot())->printIntermediateClass("coin","medium_of_exchange");



//cout<<(object->getRoot())->root->value<<endl;
//cout<<(object->getRoot())->root->value<<endl;
//cout<<(object->getRoot())->root->firstChild->value<<endl;
//cout<<(object->getRoot())->root->firstChild->nextSibling->value<<endl;
//cout<<(object.getRoot())->root->firstChild->nextSibling->value<<endl;
//cout<<(object.getRoot())->root->firstChild->firstChild->value<<endl;
//cout<<(object.getRoot())->root->firstChild->nextSibling->firstChild->value<<endl;
//cout<<(object.getRoot())->root->firstChild->nextSibling->firstChild->nextSibling->value<<endl;
//cout<<(object.getRoot())->root->firstChild->nextSibling->firstChild->firstChild->value<<endl;
//cout<<(object.getRoot())->root->firstChild->nextSibling->firstChild->firstChild->firstChild->value<<endl;
//cout<<(object.getRoot())->root->firstChild->nextSibling->firstChild->firstChild->firstChild->nextSibling->value<<endl;







return 0;}*/

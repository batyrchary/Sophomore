#include"tree.hpp"
#include<iostream>
using namespace std;



int main(){

Tree *t1=new Tree("standard");
t1->insert("standard","scale");
t1->insert("scale","richter_scale");
t1->insert("standard","medium_of_exchange");
t1->insert("medium_of_exchange","currency");
t1->insert("currency","coin");
t1->insert("medium_of_exchange","money");
t1->insert("money","fund");
t1->insert("coin","nickel");
t1->insert("coin","dime");


t1->printSubClass("standart");
cout<<endl<<"nextTASK"<<endl<<endl;
t1->printSuperClass("fund");
cout<<endl<<"nextTASK"<<endl<<endl;
t1->printIntermediateClass("fund","medium_of_exchange");

cout<<endl<<"nextTASK"<<endl<<endl;
t1->printWordNet(t1->root,0);

/*
cout<<(t1.root)->value<<endl;
cout<<(t1.root)->firstChild->value<<endl;
cout<<(t1.root)->firstChild->nextSibling->value<<endl;
cout<<(t1.root)->firstChild->firstChild->value<<endl;
cout<<(t1.root)->firstChild->firstChild->nextSibling->value<<endl;
cout<<(t1.root)->firstChild->nextSibling->firstChild->value<<endl;
*/

return 0;}

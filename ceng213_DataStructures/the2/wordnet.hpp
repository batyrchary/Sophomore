#ifndef WN_H_
#define WN_H_
#include<string>
#include "tree.hpp"
#include<iostream>
using namespace std;

class WordNet{

  public:

    void BuildWordNet(string);
    void HandleTask(string);
    Tree* getRoot(){return root;} 
    void setRoot(Tree* r){root=r;}
  private:
    Tree *root;

};

#endif

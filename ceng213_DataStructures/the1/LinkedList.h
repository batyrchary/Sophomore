#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <cstdlib>
#include "LinkedNode.h"

template<class T>
class LinkedList {
private:
	LinkedNode<T> *head;
	LinkedNode<T> *tail;	
public:
    /* Default constructor. Initialize member variables. */ 
	LinkedList();
	
	/* Default destructor. Free all the memory used. */
	~LinkedList();
	
	/* Returns head of the linked list. */
	LinkedNode<T>* getHead() const;
	
	/* Returns tail of the linked list. */
	LinkedNode<T>* getTail() const;
	
	/* Returns idx-th node of the linked list under 0-based numbering.
	 */
	LinkedNode<T>* getNodeAt(int idx) const;
	
	/* Inserts a new node containing _data_ at the beginning of the linked list.
	 */
	void insertFirst(T &data);	
	
	/* Inserts a new node containing _data_ after _node_.
	 */
	void insertNode(LinkedNode<T>* node, T &data);
		
	/* Deletes _node_ from the linked list
	 */
	void deleteNode(LinkedNode<T>* node);
};




template<class T>
LinkedList<T>::LinkedList()
{
	head=NULL;
	tail=NULL;
}



/* Default destructor. Free all the memory used. */
template<class T>	
LinkedList<T>::~LinkedList()
{
	LinkedNode<T> *tmp=tail;
	while(tmp != NULL)
	{
		LinkedNode<T> *tmp2=tmp;
		tmp=tmp->getPrev();		
		//tmp=tmp->prev;				
		delete tmp2;
	}
	head=NULL;
	tail=NULL;
}



/* Returns head of the linked list. */
template<class T>
LinkedNode<T>* LinkedList<T>::getHead() const
{
	return head;
}


/*Returns tail of the linked list. */
template<class T>
LinkedNode<T>* LinkedList<T>::getTail() const
{
	return tail;
}


/* Returns idx-th node of the linked list under 0-based numbering.*/
template<class T>
LinkedNode<T>* LinkedList<T>::getNodeAt(int idx) const
{
	LinkedNode<T> *tmp;
	tmp=head;
	for(int i=0; i<idx; i++)
	{
		tmp=tmp->getNext();
		
	}
	return tmp;
}


/*Inserts a new node containing _data_ at the beginning of the linked list.*/
template<class T>
void LinkedList<T>::insertFirst(T &data)
{
	LinkedNode<T> * tmp = new LinkedNode<T>();	
	tmp->setData(data);

	if(head==NULL)
	{
		head=tmp;
		tail=tmp;
	}
	else
	{
		head->setPrev(tmp);
		tmp->setNext(head);
		//head->prev=tmp;
		//tmp->next=head;
		head=tmp;
	}
	

}	


	
/* Inserts a new node containing _data_ after _node_.*/
template<class T>
void LinkedList<T>::insertNode(LinkedNode<T>* node, T &data)
{
	LinkedNode<T> * tmp = new LinkedNode<T>();
	tmp->setData(data);
	if(head==tail)
	{
		tail=tmp;
		head->setNext(tail);
		tail->setPrev(head);

	}
	else if(node==tail)
	{
		tail->setNext(tmp);
		tmp->setPrev(tail);	
		tail=tmp;
	}
	else
	{
		tmp->setNext(node->getNext());
		tmp->setPrev(node);
		node->setNext(tmp);
		(tmp->getNext())->setPrev(tmp);
			
	}
}
	

//////////////////////////////////////////////////// 	HAYIRDIR ERROR YOK :)	
/* Deletes _node_ from the linked list*/
template<class T>
void LinkedList<T>::deleteNode(LinkedNode<T>* node)
{
	LinkedNode<T> *tmp=node;
	
	if((head==tail) && (tmp==head))
	{
		head=NULL;
		tail=NULL;
	}	
	else if(tmp==head)
	{
		head=tmp->getNext();
		head->setPrev(NULL);
		tmp->setNext(NULL);
		//head=tmp->next;
		//head->prev=NULL;
		//tmp->next=NULL;
	}
	else if(tmp==tail)
	{	
		tail=tmp->getPrev();
		tail->setNext(NULL);
		tmp->setPrev(NULL);
		//tail=tmp->prev;
		//tail->next=NULL;
		//tmp->prev=NULL;
	}
	else
	{	
		(tmp->getNext())->setPrev(tmp->getPrev());
		(tmp->getPrev())->setNext(tmp->getNext());
		tmp->setNext(NULL);
		tmp->setPrev(NULL);
		//(tmp->next)->prev=tmp->prev;
		//(tmp->prev)->next=tmp->next;
		//tmp->next=NULL;
		//tmp->prev=NULL;		
	}

	delete tmp;
}





#endif

#ifndef _LINKED_NODE_H_
#define _LINKED_NODE_H_

template<class T>
class LinkedNode {
private:
	LinkedNode<T> *prev;
	LinkedNode<T> *next;
	T data;
public:
    /* Default constructor. Initialize member variables if needed. */ 
	LinkedNode();

	LinkedNode<T>* getNext() const;
	LinkedNode<T>* getPrev() const;
	/* returns a pointer pointing to member variable _data_. */
	T* getData();
	
	void setNext(LinkedNode<T> *newNext); 
	void setPrev(LinkedNode<T> *newPrev);
	void setData(T& data);
};


template<class T>
LinkedNode<T>::LinkedNode()
{
	data=T();
	prev=NULL;
	next=NULL;
}


template<class T>
LinkedNode<T>* LinkedNode<T>:: getNext() const
{
	return next;
}
	

template<class T>
LinkedNode<T>* LinkedNode<T>::getPrev() const
{
	return prev;
}



template<class T>
T* LinkedNode<T>::getData()
{
	T* info = &data; 
	return info;
}


template<class T>
void LinkedNode<T>::setNext(LinkedNode<T> *newNext)
{
	next=newNext;	
	/*
	newNext->next=this->next;
	if((this->next) != NULL)
	{
		(this->next)->prev=newNext;	
	}
	this->next=newNext;
	newNext->prev=this;
	*/
}


template<class T>
void LinkedNode<T>::setPrev(LinkedNode<T> *newPrev)
{
	prev=newPrev;

}


template<class T>
void LinkedNode<T>::setData(T& data)
{
	data=data;
}


#endif

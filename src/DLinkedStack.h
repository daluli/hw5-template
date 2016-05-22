#pragma once

#include "StackInterface.h"
#include "Node.h"
#include <vector>
#include <cassert>

using namespace std;


template<class ItemType>
class DLinkedStack : public StackInterface<ItemType> {
private:
    Node<ItemType> *headPtr;    // Pointer to first node in the chain;
    Node<ItemType> *topPtr;    // Pointer to (last) node in the chain that contains the stack's top
public:

    DLinkedStack();

    DLinkedStack(const DLinkedStack<ItemType> &aStack);    // Copy constructor

    virtual ~ DLinkedStack();    // Destructor

    Node<ItemType> *getPointerTo(const ItemType &target) const;

    bool isEmpty() const;

    bool push(const ItemType &newItem);

    bool pop();

    ItemType peek() const;

    vector<ItemType> toVector() const;

    Node<ItemType> *getHeadPTR() const;

    Node<ItemType> *getTopPTR() const;
};

template<class ItemType>
DLinkedStack<ItemType>::DLinkedStack() : headPtr(nullptr), topPtr(nullptr) {
}

template<class ItemType>
DLinkedStack<ItemType>::DLinkedStack(const DLinkedStack<ItemType> &aStack) {
    //TODO - Implement the copy constructor
	for(Node<ItemType>* p=aStack.headPtr; p; p=p->getNext())
	{
		push(p->getItem());
	}
}

template<class ItemType>
DLinkedStack<ItemType>::~DLinkedStack() {
    //TODO - Implement the destructor
	while(!isEmpty()) pop();
}

template<class ItemType>
Node<ItemType> *DLinkedStack<ItemType>::getPointerTo(const ItemType &target) const {
    //TODO - Return the Node pointer that contains the target(return nullptr if not found)
	for(Node<ItemType>* p=topPtr; p; p=p->getPrev())
	{
		if(p->getItem == target)
		{
			return p;
		}
	}
    return nullptr;
}

template<class ItemType>
bool DLinkedStack<ItemType>::isEmpty() const {
    //TODO - Return True if the list is empty
	return topPtr ? true : false;
}

template<class ItemType>
bool DLinkedStack<ItemType>::push(const ItemType &newItem) {
    //TODO - Push an item on the Doubly Linked Stack
	if(!topPtr)
	{
		Node<ItemType>* node = new Node<ItemType>(newItem);
		if(!node) return false;
		
		topPtr = headPtr = node;
	}
	else
	{
		Node<ItemType>* node = new Node<ItemType>(newItem, topPtr, nullptr);
		if(!node) return false;
		
		topPtr->setNext(node);
		topPtr = node;
	}
    return true;
}

template<class ItemType>
bool DLinkedStack<ItemType>::pop() {
    //TODO - Pop an item from the stack - Return true if successful
	if(!topPtr) return false;
	
	if(topPtr==headPtr)
	{
		delete topPtr;
		topPtr = headPtr = nullptr;
		return true;
	}
	
	Node<ItemType>* p = topPtr->getPrev();
	p->setNext(nullptr);
	delete topPtr;
	topPtr = p;
    return true;
}

template<class ItemType>
ItemType DLinkedStack<ItemType>::peek() const {//Assume this never fails.
    //TODO - return the element stored at the top of the stack (topPtr)
	return topPtr ? topPtr->getItem() : ItemType();
}

template<class ItemType>
vector<ItemType> DLinkedStack<ItemType>::toVector() const {
    // DO NOT MODIFY THIS FUNCTION
    vector<ItemType> returnVector;
    // Put stack items into a vector in top to bottom order
    Node<ItemType> *curPtr = topPtr;
    while (curPtr != nullptr) {
        returnVector.push_back(curPtr->getItem());
        curPtr = curPtr->getPrev();
    }
    return returnVector;
}

template<class ItemType>
Node<ItemType> *DLinkedStack<ItemType>::getHeadPTR() const {
    // DO NOT MODIFY THIS FUNCTION
    return headPtr;
}

template<class ItemType>
Node<ItemType> *DLinkedStack<ItemType>::getTopPTR() const {
    // DO NOT MODIFY THIS FUNCTION
    return topPtr;
}

#pragma once

#include "PriorityNode.h"

template <typename T>
class PriorityQueue
{
private:

	PriorityNode<T>* backPtr;
	PriorityNode<T>* frontPtr;
public:

	/*
Function: Queue()
The constructor of the Queue class.
*/

	PriorityQueue()
	{
	   backPtr = nullptr;
	frontPtr = nullptr;
	}


	/*
Function: isEmpty
Sees whether this queue is empty.
Input: None.
Output: True if the queue is empty; otherwise false.
*/
	bool isEmpty() const
	{
		if (frontPtr == nullptr)
		return true;
	else
		return false;
	}


	/*Function:enqueue
Adds newEntry at the back of this queue.
Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
	bool enqueue(const T& newEntry, float& prio)
	{
	PriorityNode<T>* newNodePtr = new PriorityNode<T>(newEntry,prio);
	// Insert the new node
	if (isEmpty())
	{
		frontPtr = newNodePtr; // The queue is empty
		backPtr = newNodePtr;
	}
	else
	{
		// The queue was not empty
		if (newNodePtr->GetPriority() > frontPtr->GetPriority())
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
	
		}
		else
		{
			PriorityNode<T>* prev = frontPtr;
			PriorityNode<T>* curr = prev->getNext();
			while (curr)
			{
				if (newNodePtr->GetPriority() > curr->GetPriority())
				{
					prev->setNext(newNodePtr);
					newNodePtr->setNext(curr);
					break;
				}
				else
				{
					prev = curr;
					curr = curr->getNext();
				}
			}
			if (!curr)
			{
				backPtr->setNext(newNodePtr);
				backPtr = newNodePtr;
			}
		}
		
	}
	
	backPtr->setNext(nullptr);
		return true;
	
	
	
	}

	/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.
Input: None.
Output: True if the operation is successful; otherwise false.
*/
	bool dequeue(T& frntEntry)
	{
	if (isEmpty())
		return false;

	PriorityNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

	
	}

	/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.
Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
	bool peek(T& frntEntry)  const
	{
	  if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
	
	}
	
	~PriorityQueue()
	{}
};

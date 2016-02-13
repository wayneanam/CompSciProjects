#include "DoubleLink.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/******************************************************************************
 * Name    : DoubleLink
 * Purpose : A default constructor that sets the intial values of a linked list
 * Inputs  : None
 * Outputs : None.
 ******************************************************************************/
 
DoubleLink::DoubleLink()
{
	head = nullptr;
	lastAccessed = nullptr;
	size = 0;
}

/******************************************************************************
 * Name    : ~DoubleLink
 * Purpose : A destructor that deletes all the nodes on a list
 * Inputs  : None
 * Outputs : None.
 ******************************************************************************/
 
DoubleLink::~DoubleLink()
{
	Node* traverse;
	traverse = head;
	lastAccessed = head;
	
	while(traverse != nullptr)
	{
		lastAccessed = traverse->next;
		delete traverse;
		traverse = lastAccessed;
	}
}

/******************************************************************************
 * Name    : DoubleLink
 * Purpose : A copy constructor. It copies the values of one object onto another
 * Inputs  : An object of the same type passed by reference
 * Outputs : None.
 ******************************************************************************/
 
DoubleLink::DoubleLink(DoubleLink & d)
{
	head = nullptr;
	lastAccessed = nullptr;
	size = 0;
	
	Node* traverse;
	
	traverse = d.head;
	
	while(traverse != nullptr)
	{
		insert(traverse->data);
		traverse = traverse->next;
	}
}

/******************************************************************************
 * Name    : search
 * Purpose : A private member function that finds a value in a given list.
 * Inputs  : An integer
 * Outputs : If the value is found within the list it returns its address.
						 Otherwise it returns nullptr.
 ******************************************************************************/
 
DoubleLink::Node* DoubleLink::search(int value)
{
	Node* temp = head;
	
	for(int i = 0; i < size; i++)
	{
		if(temp->data == value)
		{
			return temp;
		}
		
		temp = temp->next;
	}
	
	return nullptr;
}

/******************************************************************************
 * Name    : createNode
 * Purpose : A private member functions that creates and connects nodes.
 * Inputs  : An integer.
 * Outputs : Returns the address of the lastAccessed node.
 ******************************************************************************/
 
DoubleLink::Node* DoubleLink::createNode(int value)
{
	Node* temp = nullptr;
	Node* temp1 = nullptr;
	Node* temp2 = nullptr;
	
	if(head == nullptr)
	{
		head = new Node;
		head->data = value;
		head->prev = nullptr;
		head->next = nullptr;
		lastAccessed = head;
	}
	else
	{
		if(lastAccessed == nullptr)
		{
			temp = head;
			head->prev = new Node;
			lastAccessed = head->prev;
			lastAccessed->data = value;
			head = lastAccessed;
			head->prev = nullptr;
			head->next = temp;
			lastAccessed = head;
		}
		else
		{
			if(lastAccessed->next == nullptr)
			{
				temp = lastAccessed;
				lastAccessed->next = new Node;
				lastAccessed = lastAccessed->next;
				lastAccessed->data = value;
				lastAccessed->prev = temp;
				lastAccessed->next = nullptr;
			}
			else
			{
				temp = lastAccessed;
				temp1 = lastAccessed->next;
				lastAccessed->next = new Node;
				lastAccessed = lastAccessed->next;
				lastAccessed->prev = temp;
				lastAccessed->data = value;
				lastAccessed->next = temp1;
				temp2 = lastAccessed;
				lastAccessed = lastAccessed->next;
				lastAccessed->prev = temp2;
			}
		}
	}
	return lastAccessed;
}

/******************************************************************************
 * Name    : insert
 * Purpose : A function that determines if/where a node is to be created.
 * Inputs  : An integer
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void DoubleLink::insert(int value)
{
	if(head == nullptr)
	{
		createNode(value);
		size++;
		return;
	}
	
	if(search(value) != nullptr)
	{
		return;
	}
	
	if(value > (lastAccessed->data))
	{
		while((lastAccessed->data) < value)
		{
			if(lastAccessed->next == nullptr)
			{
				createNode(value);
				size++;
				return;
			}
			else
			{
				lastAccessed = lastAccessed->next;
			}
		}
		
		lastAccessed = lastAccessed->prev;
		
		createNode(value);
		size++;	
	}
	else
	{
		while((lastAccessed->data) > value)
		{
			if((lastAccessed->prev) == nullptr)
			{
				lastAccessed = nullptr;
				break;
			}
			else
			{
				lastAccessed = lastAccessed->prev;
			}
		}

		createNode(value);
		size++;
	}	
}

/******************************************************************************
 * Name    : remove
 * Purpose : A function that removes a given node from a list.
 * Inputs  : An integer
 * Outputs : Returns Nothing.
 ******************************************************************************/
 
void DoubleLink::remove(int value)
{
	Node* traverse = head;
	Node* currNode;
	Node* prevNode;
	Node* nextNode;
	
	while(traverse != nullptr)
	{
		currNode = search(value);
		
		if(currNode != nullptr)
		{
			prevNode = currNode->prev;
			nextNode = currNode->next;
			
			if(prevNode == nullptr)
			{
				head = nextNode;
				nextNode->prev = nullptr;
				delete currNode;
				size--;
				break;
			}
			
			if(nextNode == nullptr)
			{
				prevNode->next = nullptr;
				delete currNode;
				size--;
				break;
			}
			
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
			
			delete currNode;
			
			size--;
			break;
		}
			
		traverse = traverse->next;
	}
}

/******************************************************************************
 * Name    : operator[]
 * Purpose : A member function that overloads the [] operator. Gives us a 
						 "shortcut" when we want to access a nodes value.
 * Inputs  : An address to a constant integer.
 * Outputs : Returns an address to an integer.
 ******************************************************************************/
 
int& DoubleLink::operator[](const int& index)
{
	Node* traverse = head;
	
	static int invalid = -1;
	
	if((index < 0) || (index > size))
	{		
		return invalid;
	}
	else
	{
		for(int i = 0; i < index; i++)
		{
			traverse = traverse->next;
		}
		
		return traverse->data;
	}
}

/******************************************************************************
 * Name    : display
 * Purpose : A function that displays the content of a linked list.
 * Inputs  : None.
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void DoubleLink::display()
{
	DoubleLink tempTransfer = *this;
	
	for(int i = 0; i < size; i++)
	{
		cout<<tempTransfer[i]<<" ";
	}
	cout<<endl;
}
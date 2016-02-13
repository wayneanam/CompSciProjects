#ifndef DOUBLELINK_H
#define DOUBLELINK_H

class DoubleLink
{
	private:
		struct Node
		{
			int data;
			Node* prev;
			Node* next;
		};
		
		int size;
		Node* head;
		Node* lastAccessed;
		Node* search(int value);
		Node* createNode(int value);
		
	public:
		DoubleLink();
		~DoubleLink();
		DoubleLink(DoubleLink & d);
		void insert(int value);
		void remove(int value);
		int& operator[](const int& index);
		void display();
};

#endif
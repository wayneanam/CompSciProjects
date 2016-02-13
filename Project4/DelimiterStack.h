#ifndef DELIMITERSTACK_H
#define DELIMITERSTACK_H

#include <iostream>
#include <string>
#include <new>
#include <cstdlib>

using namespace std;

class DelimiterStack
{
	private:
		struct StackNode
		{
			char delimit;
			int lineString;
			int charString;
			StackNode* next;
		};
		
		int size;
		StackNode* top;

	public:
		DelimiterStack();
		~DelimiterStack();
		void push(char charD, int lineS, int charS);
		void pop(char& charD, int& lineS, int& charS);
		void parseInput(string& input, int stringSize, int lines);
		void displayStack();
};

#endif

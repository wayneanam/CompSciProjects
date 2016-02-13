/******************************************************************************
 * Course       : CS 2250 E01 (Fall 2015)
 * Assignment   : Project 4
 * Summary      : This program parses input from a string and creates a stack.
 * Author       : Wayne Anam
 * Last Modified: November 10, 2015
 ******************************************************************************/
 
#include <iostream>
#include <string>
#include <new>
#include <cstdlib>
#include "DelimiterStack.h"

using namespace std;

int main()
{
	//Variables
	int lines = 0, stringLength = 0;
	string input = "";
	bool doneFound = false;
	DelimiterStack testing;	
	
	//Collects input until the "DONE" keyword is found
	while(doneFound == false)
	{
		try
		{
			cout<<"Please enter a string"<<endl;
			getline(cin, input);
		}
		catch(bad_alloc)
		{
			cout<<"There is not enough memory to run this program"<<endl;
			exit(0);
		}
		
		stringLength = input.length();
		
		//Looks for the string "DONE"
		for(int i = 0; i < stringLength; i++)
		{
			if(input[i] == 'D')
			{
				if((stringLength > i + 1) && (input[i + 1] == 'O'))
				{
					if((stringLength > i + 2) && (input[i + 2] == 'N'))
					{
						if((stringLength > i + 3) && (input[i + 3] == 'E'))
						{
							doneFound = true;
							break;
						}
					}
				}
			}
		}

		testing.parseInput(input, stringLength, lines);

		lines++;
		cout<<endl;
		cout<<endl;
	}

	testing.displayStack();

	return 0;
}
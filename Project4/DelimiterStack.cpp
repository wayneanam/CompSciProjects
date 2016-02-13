#include "DelimiterStack.h"

/******************************************************************************
 * Name    : DelimiterStack
 * Purpose : A default constructor that sets the intial values of the stack
 * Inputs  : None
 * Outputs : None.
 ******************************************************************************/
 
DelimiterStack::DelimiterStack()
{
	top = NULL;
	size = 0;
}

/******************************************************************************
 * Name    : ~DelimiterStack
 * Purpose : A destructor that deletes all the nodes on the stack
 * Inputs  : None
 * Outputs : None.
 ******************************************************************************/
 
DelimiterStack::~DelimiterStack()	
{
	StackNode* temp;
	
	while(size > 0)
	{
		temp = top->next;
		delete top;
		size--;
		top = temp;
	}
}

/******************************************************************************
 * Name    : push
 * Purpose : A function that creates nodes and places them on the stack
 * Inputs  : The character i want to push and its location (line and character)
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void DelimiterStack::push(char charD, int lineS, int charS)
{
	StackNode* traverse = NULL;
	
	try
	{
		if(top == NULL)
		{	
			top = new StackNode;
			top->delimit = charD;
			top->lineString = lineS;
			top->charString = charS;
		}
		else
		{
			traverse = new StackNode;
			traverse->delimit = charD;
			traverse->lineString = lineS;
			traverse->charString = charS;
			
			traverse->next = top;
			top = traverse;
		}
		size++;
	}
	catch(bad_alloc)
	{
		cout<<"There is not enough memory to run this program"<<endl;
		exit(0);
	}
}

/******************************************************************************
 * Name    : pop
 * Purpose : A function that removes a node from the stack.
 * Inputs  : Threee reference variables, A character, and two integers
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void DelimiterStack::pop(char& charD, int& lineS, int& charS)
{
	StackNode* holder = NULL;
	
	if(size < 1)
	{
		size = 0;
		top = NULL;
	}
	
	if(top == NULL)
	{
		cout<<"ERROR: Right delimiter " <<charD<<" at line "<<lineS + 1<<", ";
		cout<<"char "<<charS + 1<<" has no left delimiter."<<endl;
	}
	else
	{
		holder = top->next;
		charD = top->delimit;
		lineS = top->lineString;
		charS = top->charString;
		delete top;
		top = holder;
	}
	size--;
}

/******************************************************************************
 * Name    : parseInput
 * Purpose : This function parses the string and checks for delimeters
 * Inputs  : The string being parsed, its size and the line.
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void DelimiterStack::parseInput(string& input, int stringSize, int lines)
{
	string temp = "";
	char popDel = '\0';
	int popLine = 0, popChar = 0;
	bool match;
	char keyCharLeft[] = {'{', '(', '['};
	char keyCharRight[] = {'}', ')', ']'};
	
	for(int i = 0; i < stringSize; i++)
	{
		match = true;
		
		for(int j = 0; j < 3; j++)
		{
			if(input[i] == keyCharLeft[j])
			{
				push(input[i], lines, i);
				break;
			}
				
			if(input[i] == keyCharRight[j])
			{
				popDel = input[i];
				popLine = lines;
				popChar = i;
				
				pop(popDel, popLine, popChar);
				
				for(int k = 0; k < 3; k++)
				{
					if(popDel == keyCharLeft[k])
					{
						if(k != j)
						{
							match = false;	
						}
					}
				}
			}
			
			if(match == false)
			{
				cout<<"ERROR: Mismatched delimiter " <<popDel;
				cout<<" at line "<<(popLine) + 1<<", char "<<popChar;
				cout<<" (found delimiter "<<input[i];
				cout<<" at line "<<(lines) + 1<<", char "<<i + 1<<")"<<endl;
				break;
			}
		}
	}
}

/******************************************************************************
 * Name    : displayStack
 * Purpose : A function that displays the content of a stack.
 * Inputs  : None.
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void DelimiterStack::displayStack()
{
	StackNode* traverse = top;
	
	for(int i = 0; i < size; i++)
	{		
		cout<<"ERROR: Left delimiter " <<traverse->delimit;
		cout<<" at line "<<(traverse->lineString) + 1<<", ";
		cout<<"char "<<(traverse->charString) + 1;
		cout<<" has no right delimiter."<<endl;
		
		traverse = traverse->next;
	}
}	
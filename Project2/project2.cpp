/******************************************************************************
 * Course       : CS 2250 E01 (Fall 2015)
 * Assignment   : Project 2
 * Summary      : This program will convert an english string to pig latin.
 * Author       : Wayne Anam
 * Last Modified: October 2, 2015
 ******************************************************************************/
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Word
{
	string english;
	string piglatin;
};

Word* splitSentence(const string words, int& size);
void convertToPigLatin(Word wordArr[], int size);
void displayPigLatin(const Word wordArr[], int size);

/******************************************************************************
 * Name    : main
 * Purpose : This functions runs the program and calls other functions.
 * Inputs  : None.
 * Outputs : Returns 0 if ran successfully.
 ******************************************************************************/
int main()
{
	int size = 1;
	string temp;
	Word* sepPtr;

	cout<<"Please enter a string to convert to PigLatin:"<<endl;
	getline(cin, temp);

	sepPtr = splitSentence(temp, size);

	convertToPigLatin(sepPtr, size);

	displayPigLatin(sepPtr, size);

	return 0;
}

/******************************************************************************
 * Name    : splitSentence
 * Purpose : This function splits a string into multiple words
 * Inputs  : A constant string and a variable holding the arrays size
 * Outputs : Returns a pointer of words
 ******************************************************************************/

Word* splitSentence(const string words, int& size)
{
	int index = 0, countWords;
	bool eraseChar, check;
	string transfer;
	Word* wordPtr = NULL;

	//This loop removes all invalid characters and copies all spaces into a new string
	for(int i = 0; i < words.length(); i++)
	{
		if(isalpha(words[i]))
		{
			transfer += words[i];
		}
		else if(isspace(words[i]))
		{
			transfer += words[i];
		}
	}

	//This loop removes all whitespace from the begining of the string only
	do
	{
		eraseChar = false;
		if(isspace(transfer[0]))
		{
			transfer.erase(index, 1);
			eraseChar = true;
		}
	}
	while(eraseChar == true);

	transfer += '*';

	eraseChar = true;

	//This loop removes all invalid whitespace and corrects sentence structure.
	while(eraseChar == true)
	{
		eraseChar = false;
		countWords = transfer.length();

		for(int i = 0; i < countWords; i++)
		{
			transfer[i] = tolower(transfer[i]);
			if(transfer[i] == '*')
			{
				if(isspace(transfer[i - 1]))
				{
					transfer.erase(i - 1, 1);
					eraseChar = true;
					break;
				}

				transfer.erase(i, 1);
				eraseChar = true;
				break;
			}
			if(isspace(transfer[i]))
			{
				if(isspace(transfer[i + 1]))
				{
					transfer.erase(i, 1);
					eraseChar = true;
					break;
				}
			}
		}
	}

	transfer += " ";

	countWords = transfer.length();

	//This loop counts the number of spaces to determine how many words there are
	for(int i = 0; i < countWords; i++)
	{
		if(isspace(transfer[i]))
		{
			size++;
		}
	}

	size--;

	wordPtr = new Word[size];

	//This loop separates all the words in a single sentence
	for(int j = 0; j < size; j++)
	{
		check = false;
		for(int k = index; k < countWords; k++)
		{
			if(isspace(transfer[k]))
			{
				for(int l = index; l < k; l++)
				{
					wordPtr[j].english += transfer[l];
					check = true;
				}
			}

			if(check)
			{
				index  = k + 1;
				break;
			}
		}
	}
	return wordPtr;
}

/******************************************************************************
 * Name    : convertToPigLatin
 * Purpose : This function converts an english word to piglatin.
 * Inputs  : This function takes in an array of Word structures and its size
 * Outputs : Returns nothing.
 ******************************************************************************/

void convertToPigLatin(Word wordArr[], int size)
{
	const int vowelSize = 5;
	int loopsMade = 0;
	bool vowelFound;
	string vowel ="aeiou";

	do
	{
		vowelFound = false;
		for(int i = 0; i < vowelSize; i++)
		{
			if((wordArr[loopsMade]).english[0] == vowel[i])
			{
				vowelFound = true;
				break;
			}
		}

		if(vowelFound == true)
		{
			wordArr[loopsMade].piglatin = wordArr[loopsMade].english;
			wordArr[loopsMade].piglatin += "way";
		}
		else
		{
			wordArr[loopsMade].piglatin = wordArr[loopsMade].english;
			wordArr[loopsMade].piglatin.erase(0, 1);
			wordArr[loopsMade].piglatin += (wordArr[loopsMade].english)[0];
			wordArr[loopsMade].piglatin += "ay";
		}
		loopsMade++;
	}
	while(loopsMade < size);
}

/******************************************************************************
 * Name    : displayPigLatin
 * Purpose : This function outputs the piglatin onto the screen
 * Inputs  : This function takes in an array of Word structures and its size
 * Outputs : Returns nothing.
 ******************************************************************************/

void displayPigLatin(const Word wordArr[], int size)
{
	cout<<"Output:"<<endl;
	for(int i = 0; i < size; i++)
	{
		cout<<wordArr[i].piglatin<<" ";
	}
	cout<<endl;
}

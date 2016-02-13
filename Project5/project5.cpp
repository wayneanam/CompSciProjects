/******************************************************************************
 * Course       : CS 2250 E01 (Fall 2015)
 * Assignment   : Project 5
 * Summary      : This program creates a dictionary using a Trie.
 * Author       : Wayne Anam
 * Last Modified: December 6, 2015
 ******************************************************************************/
 
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <stack>
#include "Dictionary.h"

using namespace std;
 
int main()
{
	//Variables and Constants
	int wordSize;
	char choice;
	bool invalid;
	string fileName, word, format;
	Dictionary test;
	
	
	cout<<"Please enter the name of the input dictionary file: ";
	cin>>fileName;
	invalid = test.loadDictionary(fileName);
	cin.ignore();
	
	while(!invalid)
	{
		cout<<"Invalid file name"<<endl;
		cout<<"Please enter the name of the input dictionary file: ";
		cin>>fileName;
		invalid = test.loadDictionary(fileName);
		cin.ignore();
	}
	
	cout<<endl;
	cout<<"Loading Dictionary..."<<endl;
	cout<<endl;
	
	//This loop repeatedly asks the user if they want to look up the definition of a word
	do
	{
		invalid = true;
		
		cout<<"Would you like to lookup a word (y/n)? ";
		cin>>choice;
		
		choice = tolower(choice);
		
		if((choice == 'y') || (choice == 'n'))
		{
			invalid = false;
		}
		
		while(invalid == true)
		{
			cout<<"Invalid Input"<<endl;
			cout<<"Would you like to lookup a word (y/n)? ";
			cin>>choice;
			
			choice = tolower(choice);
			
			if((choice == 'y') || (choice == 'n'))
			{
				invalid = false;
			}
		}		
		
		if(choice == 'y')
		{
			cout<<"Enter a word: ";
			cin>>word;
			
			format = "";
			wordSize = word.length();
			
			//This loop takes the users input and formats it correctly
			for(int i = 0; i < wordSize; i++)
			{
				format += tolower(word[i]);
			}
			
			format[0] = toupper(word[0]);
			
			word = format;
			
			format = test.lookup(word);
			
			if(format.length() > 2)
			{
				cout<<"Definition: "<<format<<endl;
			}
			else
			{
				cout<<"ERROR: "<<word<<" is not in the dictionary."<<endl;
			}
			
			cout<<endl;
		}
	}
	while(choice == 'y');
	
	cout<<"Would you like to write the dictionary to a file (y/n)?";
	cin>>choice;
	
	invalid = true;
	choice = tolower(choice);
	
	if((choice == 'y') || (choice == 'n'))
	{
		invalid = false;
	}
	
	while(invalid == true)
	{
		cout<<"Invalid Input"<<endl;
		cout<<"Would you like to write the dictionary to a file (y/n)?";
		cin>>choice;
		
		choice = tolower(choice);
		
		if((choice == 'y') || (choice == 'n'))
		{
			invalid = false;
		}
	}
	
	if(choice == 'y')
	{
		cout<<"Please enter the name of the output file: ";
		cin>>fileName;
	
		if(test.writeTrie(fileName))
		{
			cout<<endl;
			cout<<"Writing dictionary..."<<endl;
		}
	}
	
	cout<<endl;
	cout<<"THE END."<<endl;
	
	
	return 0;
}

/******************************************************************************
 * Course       : CS 2250 E01 (Fall 2015)
 * Assignment   : Extra Project 1
 * Summary      : This program creates and modifies a doubly linked list
 * Author       : Wayne Anam
 * Last Modified: November 1, 2015
 ******************************************************************************/
 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DoubleLink.h"

using namespace std;

int main()
{
	//Constants and Variables
	const int SIZE = 20;
	const int HALFSIZE = 10;
	bool duplicate = true;
	int arr[SIZE];
	DoubleLink temp;
	
	//Seeds the random number generator
	srand(time(0));
	
	//Creates an array of 20 unique numbers
	while(duplicate == true)
	{
		duplicate = false;
		for(int i = 0; i < SIZE; i++)
		{
			arr[i] = (rand() % 100) + 1;
		}
		
		for(int j = 0; j < SIZE; j++)
		{
			for(int k = j; k < SIZE; k++)
			{
				if(j != k)
				{
					if(arr[j] == arr[k])
					{
						arr[j] = (rand() % 100) + 1;
						duplicate = true;
						break;
					}
				}
			}
		}
	}

	for(int j = 0; j < HALFSIZE; j++)
	{
		temp.insert(arr[j]);
	}

	//Calls the copy constructor
	DoubleLink a(temp);

	for(int j = HALFSIZE; j < SIZE; j++)
	{
		a.insert(arr[j]);
	}


	//Outputs
	cout<<"First List : ";
	temp.display();
	cout<<"Second List: ";
	a.display();

	for(int j = 0; j < HALFSIZE; j++)
	{
		a.remove(arr[j]);
	}
	
	cout<<"Second List: ";
	a.display();
	
	return 0;
	
}
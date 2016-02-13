/******************************************************************************
 * Course       : CS 2250 E01 (Fall 2015)
 * Assignment   : Project 1
 * Summary      : This program creates dynamically allocated arrays, Fills them
									with content, then sorts and shuffles them.
 * Author       : Wayne Anam
 * Last Modified: September 16, 2015
 ******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

void printArray(const int arr[], int size);
void initializeArray(int arr[], int size);
int* shuffleArray(const int arr[], int size);
int* createOddArray(const int origArr[], int origSize, int &newSize);
int* createEvenArray(const int origArr[], int origSize, int &newSize);
void arrayWar(int* arr1, int size1, int* arr2, int size2);
void sortArray(int* arr, int size);

/******************************************************************************
 * Name    : main
 * Purpose : This functions runs the program and calls other functions.
 * Inputs  : None.
 * Outputs : Returns 0 if ran successfully.
 ******************************************************************************/
int main()
{
	int oddSize, evenSize, maxSize, userInput = 0;
	int* userArr = NULL;
	int* tempPtr = NULL;
	int* oddPtr = NULL;
	int* evenPtr = NULL;

	srand(time(0));

	cout<<"Please enter the size of the array"<<endl;
	cin>>userInput;

	while((userInput < 1 || userInput > 100))
	{
		cout<<"Please enter the size of the array (1 - 100): ";
		cin>>userInput;
	}

	userArr = new int[userInput];

	initializeArray(userArr, userInput);
	cout<<"Original array: ";
	printArray(userArr, userInput);


	tempPtr = shuffleArray(userArr, userInput);
	cout<<"Shuffled array: ";
	printArray(tempPtr, userInput);

	oddPtr = createOddArray(tempPtr, userInput, oddSize);
	cout<<"Odd array: ";
	printArray(oddPtr, oddSize);

	evenPtr = createEvenArray(tempPtr, userInput, evenSize);
	cout<<"Even array: ";
	printArray(evenPtr, evenSize);


	maxSize = evenSize;
	if(oddSize > evenSize)
	{
		maxSize = oddSize;
	}

	arrayWar(oddPtr, oddSize, evenPtr, evenSize);
  
  delete userArr;
  delete tempPtr;
  delete oddPtr;
  delete evenPtr;
  
	return 0;
}

/******************************************************************************
 * Name    : printArray
 * Purpose : This function prints the content of an array onto the screen
 * Inputs  : An integer array and its size.
 * Outputs : Returns nothing
 ******************************************************************************/

void printArray(const int arr[], int size)
{
	cout<<"[";
	for(int i = 0; i < size; i++)
	{
		cout<<arr[i];
		if(i < (size - 1))
		{
			cout<<" ";
		}
	}

	cout<<"]";
	cout<<endl;
	return;
}

/******************************************************************************
 * Name    : initializeArray
 * Purpose : This functions purpose is to initialize an array
 * Inputs  : An integer array and its size.
 * Outputs : Returns nothing
 ******************************************************************************/

void initializeArray(int arr[], int size)
{
	for(int i = 0; i < size; i++)
	{
		arr[i] = i;
	}

	return;
}

/******************************************************************************
 * Name    : shuffleArray
 * Purpose : This functions purpose is to randomly shuffle the array.
 * Inputs  : An integer array and its size.
 * Outputs : Returns a pointer that contains the shuffled array.
 ******************************************************************************/

int* shuffleArray(const int arr[], int size)
{
	int transfer, randomizer = 0;
	int* temp = NULL;
	temp = new int[size];

	for(int i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}

	for(int j = 0; j < size; j++)
	{
		randomizer = rand()% size;

		transfer = temp[randomizer];
		temp[randomizer] = temp[j];
		temp[j] = transfer;
	}

	return temp;
}

/******************************************************************************
 * Name    : createOddArray
 * Purpose : This function creates an array of odd numbers
 * Inputs  : An integer array, its size and a  variable holding the new size.
 * Outputs : Returns a pointer to an array of odd numbers
 ******************************************************************************/

int* createOddArray(const int origArr[], int origSize, int &newSize)
{
	int jHolder = 0;
	newSize = 0;

	for(int i = 0; i < origSize; i++)
	{
		if((origArr[i] % 2) != 0)
		{
			newSize++;
		}
	}

	int* tempOddPtr = NULL;
	tempOddPtr = new int[newSize];

	for(int k = 0; k < origSize; k++)
	{
		for(int j = jHolder; j < origSize; j++)
		{
			if((origArr[j] % 2) != 0)
			{
				tempOddPtr[k] = origArr[j];
				jHolder = j;
				break;
			}
		}
		jHolder++;
	}

	return tempOddPtr;
}

/******************************************************************************
 * Name    : createEvenArray
 * Purpose : This function creates an array of even numbers
 * Inputs  : An integer array, its size and a  variable holding the new size.
 * Outputs : Returns a pointer to an array of even numbers
 ******************************************************************************/

int* createEvenArray(const int origArr[], int origSize, int &newSize)
{
	int jHolder = 0;
	newSize = 0;

	for(int i = 0; i < origSize; i++)
	{
		if((origArr[i] % 2) == 0)
		{
			newSize++;
		}
	}

	int* tempEvenPtr = NULL;
	tempEvenPtr = new int[newSize];

	for(int k = 0; k < origSize; k++)
	{
		for(int j = jHolder; j < origSize; j++)
		{
			if((origArr[j] % 2) == 0)
			{
				tempEvenPtr[k] = origArr[j];
				jHolder = j;
				break;
			}
		}
		jHolder++;
	}

	return tempEvenPtr;
}

/******************************************************************************
 * Name    : arrayWar
 * Purpose : This function compares two arrays. It picks a winner outputs it
						 then sorts the array and outputs that as well.
 * Inputs  : Two integer pointers and their size.
 * Outputs : Returns nothing.
 ******************************************************************************/

void arrayWar(int* arr1, int size1, int* arr2, int size2)
{
	int* lPtr = NULL;
	int largestSize, smallestSize, iHolder = 0;

	if(size1 > size2)
	{
		lPtr = new int[size1];
		largestSize = size1;
		smallestSize = size2;
	}
	else
	{
		lPtr = new int[size2];
		largestSize = size2;
		smallestSize = size1;
	}

	for(int k = 0; k < largestSize; k++)
	{
		if(size1 > size2)
		{
			lPtr[k] = arr1[k];
		}
		else
		{
			lPtr[k] = arr2[k];
		}
	}

	for(int j = 0; j < smallestSize; j++)
	{
		for(int i = iHolder; i < smallestSize; i++)
		{
			if(arr1[i] > arr2[i])
			{
				lPtr[j] = arr1[i];
			}
			iHolder =(i + 1);
			break;
		}
	}
	cout<<"ArrayWar Winners: ";
	printArray(lPtr, largestSize);

	cout<<"Sorted ArrayWar Winners: ";
	sortArray(lPtr, largestSize);
	printArray(lPtr, largestSize);

	return;
}

/******************************************************************************
 * Name    : sortArray
 * Purpose : This function sorts an array using selection sort
 * Inputs  : An integer array and its size.
 * Outputs : Returns nothing
 ******************************************************************************/

void sortArray(int* arr, int size)
{
	int swapper, check = 0;

	do
	{
		check = size;

		for(int i = 0; i < size -1; i++)
		{
			if(arr[i] > arr[i + 1])
			{
				swapper = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = swapper;
				check--;
			}
		}


	}
	while(check < size);


	return;
}



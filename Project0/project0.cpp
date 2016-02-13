#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

bool checkGuess(const int solutions[], int SIZE, int guess);
int distanceToClosest(const int solutions[], int SIZE, int guess);

int main()
{
	//Constants and Variables
	const int SIZE = 5;
	int solutions[SIZE];
	int temp, guess = 0, counter = 1, numHolder1, numHolder2, guessesMade = 0;
	bool trial = false, sortCheck = false;

	//Seeds the random number generator
	srand(time(0));

	//Randomly chooses Numbers and puts them in the array.
	for(int i = 0; i < SIZE; i++)
	{
		solutions[i] = (rand() % 1000) + 1;
	}

	//Sorts the array in ascending order
	do
	{
		counter = 1;
		for(int i = 0; i < SIZE-1; i++)
		{
			if(solutions[i] < solutions[i+1])
			{
				counter++;
			}
		}

		if(counter == SIZE)
		{
			sortCheck = true;
			break;
		}
		else
		{
			for(int j = 0; j < SIZE-1; j++)
			{
				if(solutions[j] > solutions[j+1])
				{
					temp = solutions[j];
					solutions[j] = solutions[j+1];
					solutions[j+1] = temp;
				}
			}
		}
	}
	while(sortCheck == false);



	//Asks the user to play for the first time
	cout<<"Hello, please try and guess one of my numbers between 1 and 1000."<<endl;
	cout<<"Please make a guess: ";
	cin>>guess;

	//Makes sure that the guess is within the ranges 1-1000
	while(guess < 1 || guess > 1000)
	{
		cout<<"Please make a guess that is between 1-1000"<<endl;
		cin>>guess;
	}

	trial = checkGuess(solutions, SIZE, guess);

	if(trial)
	{
		cout<<"Success!"<<endl;
		return 0;
	}
	else if(trial != true && guessesMade == 0)
	{
		cout<<"I am sorry that is incorrect"<<endl;
		numHolder2 = distanceToClosest(solutions, SIZE, guess);
	}

	guessesMade++;

	do
	{
		//Determines the output based on how many guesses have been made.
		if(guessesMade > 0)
		{
			cout<<"Please make a guess: ";
			cin>>guess;
		}

		//Makes sure that the guess is within the ranges 1-1000
		while(guess < 1 || guess > 1000)
		{
			cout<<"Please make a guess that is between 1-1000"<<endl;
			cin>>guess;
		}

		trial = checkGuess(solutions, SIZE, guess);

		if(trial)
		{
			cout<<"Success!"<<endl;
			break;
		}

		if(guessesMade > 0)
		{
			numHolder1 = distanceToClosest(solutions, SIZE, guess);
			if(numHolder2 < numHolder1)
			{
				cout<<"Getting Colder"<<endl;
			}
			else
			{
				cout<<"Getting Warmer"<<endl;
			}

			numHolder2 = numHolder1;
			guessesMade++;
		}
	}
	while(trial == false);

	return 0;
}

//Finds the smallest absolute difference between the guess and any solution
int distanceToClosest(const int solutions[], int SIZE, int guess)
{
	int tempArr[SIZE];
	int t = 0;

	for(int h = 0; h < SIZE; h++)
	{
		tempArr[h] = solutions[h];
	}

	for(int i = 0; i < SIZE; i++)
	{
		tempArr[i] = abs(guess - tempArr[i]);
	}

	for(int j = 0; j < SIZE; j++)
	{
		if(tempArr[j] < tempArr[j+1])
		{
			t = tempArr[j];
		}
	}

	return t;
}

//A function that checks if the guess is correct
bool checkGuess(const int solutions[], int SIZE, int g)
{
	for(int i =0; i < SIZE; i++)
	{
		if(g == solutions[i])
		{
			return true;
			break;
		}
	}
	return false;
}



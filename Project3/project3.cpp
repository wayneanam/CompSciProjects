/******************************************************************************
 * Course       : CS 2250 E01 (Fall 2015)
 * Assignment   : Project 3
 * Summary      : This program simulates a race horse.
 * Author       : Wayne Anam
 * Last Modified: October 18, 2015
 ******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Horse.h"

using namespace std;

int main()
{
	//Variables and Constants
	int numHorses, highestDistance, laps = 1, potentialWinners = 0, counter  = 1;
	double raceDistance;
	char choice, newLap;
	bool check;
	int* logWinner = NULL;
	string* horseHolder = NULL;
	string* riderHolder = NULL;
	Horse** hPtr = NULL;

	//Seeds the random number generator
	srand(time(NULL));

	cout<<"How many horses are in the race: ";
	cin>>numHorses;
	cout<<endl;

	while(numHorses <= 1)
	{
		cout<<"Please enter a value greater than 1 for the horse ";
		cin>>numHorses;
	}

	horseHolder = new string[numHorses];
	riderHolder = new string[numHorses];
	logWinner = new int[numHorses];

	cin.ignore();

	for(int i = 0; i < numHorses; i++)
	{
		cout<<"Please give me the name of horse "<<(i + 1)<<": ";
		getline(cin, horseHolder[i]);

		cout<<"Please give me the name of rider "<<(i + 1)<<": ";
		getline(cin, riderHolder[i]);

		cout<<endl;
	}

	hPtr = new Horse*[numHorses];

	for(int j = 0; j < numHorses; j++)
	{
		hPtr[j] = new Horse(horseHolder[j], riderHolder[j]);
	}

	cout<<"Please enter the distance of the race: ";
	cin>>raceDistance;

	while(raceDistance < 100)
	{
		cout<<"Please enter a distance equal to or greater than 100 ";
		cin>>raceDistance;
	}
	cout<<endl;
	cout<<"Start!"<<endl;


	do
	{
		//This loop conducts the race and checks for the winner.
		do
		{
			int temp1, temp2, mostRange1 = 0;
			for(int k = 0; k < numHorses; k++)
			{
				hPtr[k]->displayHorse(raceDistance);
			}

			cout<<"Are you ready for the next second(y/n)?: ";
			cin>>choice;

			if(choice == 'y' || choice == 'Y')
			{
				for(int l = 0; l < numHorses; l++)
				{
					hPtr[l]->runOneSecond();
				}


				for(int m = 0; m < numHorses; m++)
				{
					check = false;
					check = hPtr[m]->checkWinner(raceDistance);

					if(check)
					{
						logWinner[potentialWinners] = m;
						potentialWinners++;
						choice  = 'n';
					}
				}
			}
		}
		while(choice == 'y' || choice == 'Y');

		for(int k = 0; k < numHorses; k++)
		{
			hPtr[k]->displayHorse(raceDistance);
		}

		if(potentialWinners < 1)
		{
			for(int k = 0; k < numHorses; k++)
			{
				check = false;
				check = hPtr[k]->checkWinner(raceDistance);

				if(check)
				{
					hPtr[logWinner[k]]->setWinner();
					break;
				}
			}
		}
		else
		{
			int t = rand() % potentialWinners;
			hPtr[logWinner[t]]->setWinner();
		}
		
		for(int i = 0; i < numHorses; i++)
		{
			logWinner[i] = 0;
		}
		
		cout<<endl;

		for(int k = 0; k < numHorses; k++)
		{
			check = false;
			check = hPtr[k]->checkWinner(raceDistance);

			hPtr[k]->viewWinner(laps);
		}

		cout<<endl;
		cout<<"Do you want run another race(y/n)?: ";
		cin>>newLap;

		if((newLap == 'y') || (newLap == 'Y'))
		{
			for(int l = 0; l < numHorses; l++)
			{
				hPtr[l]->sendToGate();
			}

			potentialWinners = 0;
			counter = 0;
			laps++;
		}
	}
	while(newLap == 'y');

	delete[] logWinner;
	delete[] horseHolder;
	delete[] riderHolder;
	delete[] hPtr;


  return 0;
}

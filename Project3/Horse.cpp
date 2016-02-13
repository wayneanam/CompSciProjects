#include "Horse.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

/******************************************************************************
 * Name    : Horse
 * Purpose : A constructor that sets the intial values of a horse
 * Inputs  : A string for the horse name and a string for the jockey name
 * Outputs : Returns nothing.
 ******************************************************************************/
 
Horse::Horse(string horseName, string jockeyName)
{
	name = horseName;
	jockey = jockeyName;
	maxSpeed = (rand() % 30) + 1;
	distanceTraveled = 0;
	racesWon = 0;
}

/******************************************************************************
 * Name    : setWinner
 * Purpose : To increment the number of races won
 * Inputs  : Nothing
 * Outputs : Returns nothing.
 ******************************************************************************/

void Horse::setWinner()
{
		racesWon++;
}

/******************************************************************************
 * Name    : getDistance
 * Purpose : This function returns the distance that a horse has traveled
 * Inputs  : Nothing
 * Outputs : Returns distance traveled as an integer.
 ******************************************************************************/
 
int Horse::getDistance()
{
		return distanceTraveled;
}

/******************************************************************************
 * Name    : viewWinner
 * Purpose : This function outputs the win/losses of a single horse
 * Inputs  : Number of laps ran
 * Outputs : Returns nothing
 ******************************************************************************/
 
void Horse::viewWinner(int laps)
{
	cout<<name<<" has won "<<racesWon <<"/"<<laps<<" races."<<endl;
}

/******************************************************************************
 * Name    : viewNames
 * Purpose : This function outputs the horse name and rider name
 * Inputs  : Nothing.
 * Outputs : Returns nothing
 ******************************************************************************/
 
void Horse::viewNames()
{
	cout<<"  "<<name<<", ridden by "<<jockey<<endl;;
}

/******************************************************************************
 * Name    : runOneSecond
 * Purpose : This function calculates the distance that the horse ran. and adds
						 it to the previous value
 * Inputs  : Nothing.
 * Outputs : Returns nothing
 ******************************************************************************/
 
void Horse::runOneSecond()
{
	distanceTraveled += (rand() % maxSpeed) + 1;
}

/******************************************************************************
 * Name    : sendToGate
 * Purpose : This function sets the distance that the horse traveled to 0
 * Inputs  : Nothing.
 * Outputs : Returns nothing
 ******************************************************************************/
 
void Horse::sendToGate()
{
	distanceTraveled = 0;
}

/******************************************************************************
 * Name    : displayHorse
 * Purpose : This function outputs where the horse is at a given second
 * Inputs  : The race distance.
 * Outputs : Returns nothing
 ******************************************************************************/

void Horse::displayHorse(double raceDistance)
{
	float findArrow;
	string viewPath, tempPath = "|";

	if(distanceTraveled == 0)
	{
		tempPath += ">";
		for(int i = 0; i < 49; i++)
		{
			tempPath += " ";
		}
		tempPath += "| ";
	}

	if((distanceTraveled > 0) &&(distanceTraveled <= raceDistance))
	{
		for(int i = 0; i < raceDistance; i++)
		{
			if(i < distanceTraveled)
			{
				viewPath += "-";
			}
			if(i == distanceTraveled)
			{
				viewPath += ">";
			}
			if(i > distanceTraveled)
			{
				viewPath += " ";
			}
		}

		findArrow = ceil((distanceTraveled/raceDistance) * 50);

		for(int j = 0; j < 50; j++)
		{
			if(j < findArrow)
			{
				tempPath += "-";
			}
			if(j == findArrow)
			{
				tempPath += ">";
			}
			if(j > findArrow)
			{
				tempPath += " ";
			}
		}
		tempPath += "| ";
	}


	if(distanceTraveled > raceDistance)
	{
		for(int k = 0; k < 50; k++)
		{
			tempPath += "-";
		}
		tempPath += "|>";
	}

	cout<<tempPath;
	viewNames();
}

/******************************************************************************
 * Name    : checkWinner
 * Purpose : This function checks if a horse has completed the race
 * Inputs  : The race distance.
 * Outputs : Returns nothing
 ******************************************************************************/
 
bool Horse::checkWinner(double raceDistance)
{
	if(distanceTraveled > raceDistance)
	{
		return true;
	}

	return false;
}

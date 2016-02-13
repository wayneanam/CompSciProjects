#ifndef HORSE_H
#define HORSE_H

#include <string>

using namespace std;

class Horse
{
	private:
		string name;
		string jockey;
		int maxSpeed;
		int distanceTraveled;
		int racesWon;

	public:
		Horse(string horseName, string jockeyName);
		void viewWinner(int laps);
		int getDistance();
		void setWinner();
		void viewNames();
		void runOneSecond();
		void sendToGate();
		void displayHorse(double raceDistance);
		bool checkWinner(double raceDistance);
};

#endif

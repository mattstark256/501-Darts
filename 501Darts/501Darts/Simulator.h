#pragma once

#include "SimData.h"
#include "Statistics.h"


// This class runs the simulation. It enforces the rules of a darts championship, telling players when to take turns and checking whether they have won.
class Simulator
{
public:
	Simulator(SimData* _gameData);
	~Simulator();

	void playChampionships();

private:
	SimData* simData;
	Statistics* statistics;
	int firstPlayer = 0; // This is the index that will be used with getPlayer. The value should be 0 or 1.

	void playChampionship();
	void playSet();
	void playGame();
	void randomizeWhoThrowsFirst(); // This isn't needed for task 1, because the task specifies that Sid throws first.
	void switchWhoThrowsFirst();
};


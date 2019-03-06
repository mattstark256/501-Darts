#pragma once

#include "SimData.h"


// This class contains and processes data from the simulation. The Simulator class calls the public functions at appropriate times throughout a simulation.
class Statistics
{
public:
	Statistics();
	~Statistics();

	void resetStatistics();
	void recordChampionshipResult(SimData* simData);
	void printStatistics(SimData* simData);

private:
	int totalChampionships;

	// This stores the occurances of all championship scores, from 7:0 to 7:6 then from 0:7 to 6:7
	int scoreFrequencies[14];

	void printFrequency(int score0, int score1);
};


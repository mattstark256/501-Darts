#pragma once

#include "SimData.h"


class Statistics
{
public:
	Statistics(SimData* _gameData);
	~Statistics();

	void resetStatistics();
	void recordChampionshipResult();
	void printStatistics();

private:
	SimData* simData;
	int totalChampionships;
	int scoreFrequencies[14];

	void printFrequency(int score0, int score1);
};


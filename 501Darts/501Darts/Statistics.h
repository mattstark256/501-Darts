#pragma once

#include "SimData.h"


class Statistics
{
public:
	Statistics();
	~Statistics();

	void setSimData(SimData* _simData) { simData = _simData; }
	void resetStatistics();
	void recordChampionshipResult();
	void printStatistics();

private:
	SimData* simData;
	int totalChampionships;
	int scoreFrequencies[14];

	void printFrequency(int score0, int score1);
};


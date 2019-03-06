#pragma once

#include "SimData.h"
#include "Statistics.h"


// This class runs the simulation. It enforces the rules of a darts championship, telling players when to take turns and checking whether they have won.
class Simulator
{
public:
	Simulator();
	~Simulator();

	void playChampionships(SimData* simData);
	void playChampionship(SimData* simData, int championshipNumber);
	void playSet(SimData* simData, int setNumber);
	void playGame(SimData* simData, int gameNumber);

private:
	Statistics* statistics;
	void showSimulationProgress(int completed, int total);
};


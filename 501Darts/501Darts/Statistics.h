#pragma once

#include "GameData.h"


class Statistics
{
public:
	Statistics(GameData* _gameData);
	~Statistics();

	void resetStatistics();
	void recordChampionshipResult();
	void printStatistics();

private:
	GameData* gameData;
	int totalChampionships;
	int scoreFrequencies[14];

	void printFrequency(int score0, int score1);
};


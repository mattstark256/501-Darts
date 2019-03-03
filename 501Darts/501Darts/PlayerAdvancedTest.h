#pragma once
#include "Player.h"


class PlayerAdvancedTest :
	public Player
{
public:
	PlayerAdvancedTest(std::string _name, int _skillLevel, SimData* _simData, Scoreboard* _scoreBoard);
	~PlayerAdvancedTest();

private:
	int ratingExactScore = 100;
	int ratingRiskSingle = 50;
	int ratingRiskDouble = 25;
	int ratingPowerTwo = 5;

	int finishingScores[20] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
	int powerTwos[20] = { 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2 };

	Target chooseTarget(int throwNumber);
	Target chooseTargetToGetToFinishingScore();
	Target chooseTargetForThrowScore(int desiredScore);
};
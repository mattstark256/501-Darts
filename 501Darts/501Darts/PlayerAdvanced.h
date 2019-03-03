#pragma once
#include "Player.h"


class PlayerAdvanced :
	public Player
{
public:
	PlayerAdvanced(std::string _name, int _skillLevel, SimData* _simData, Scoreboard* _scoreBoard);
	~PlayerAdvanced();

private:
	int ratingExactScore = 100; // Added if the finishing score can be reached in 1 throw
	int ratingRiskSingle = 50; // Added if the throw is a single
	int ratingRiskDouble = 25; // Added if the throw is a double
	int ratingPowerTwo = 5; // Added for each additional power of two the finishing score has

	// The scores a player can finish on
	int finishingScores[20] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
	// The number of additional powers of two each of the above scores has
	int powerTwos[20] = { 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2 };

	Target chooseTarget(int throwNumber);
	Target chooseTargetToGetToFinishingScore();
	Target chooseTargetForThrowScore(int desiredScore);
};


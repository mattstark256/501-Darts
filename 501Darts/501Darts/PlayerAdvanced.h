#pragma once
#include "Player.h"

#define FINISHING_SCORE_COUNT 20


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
	int finishingScores[FINISHING_SCORE_COUNT] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
	// The number of times each finishing score can be divided by two
	int twoFactors[FINISHING_SCORE_COUNT] = { 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3 };

	Target chooseTarget(int throwNumber, int initialScore);
	Target chooseTargetToGetToFinishingScore();
	Target chooseTargetForThrowScore(int desiredScore);
	int rateScore(int score);
};


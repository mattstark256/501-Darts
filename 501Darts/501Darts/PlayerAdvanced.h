#pragma once
#include "Player.h"

#define FINISHING_SCORE_COUNT 21
#define LOWEST_PRECOMPUTED_SCORE 3
#define HIGHEST_PRECOMPUTED_SCORE 107


class PlayerAdvanced :
	public Player
{
public:
	PlayerAdvanced(std::string _name, int _skillLevel, SimData* _simData, Scoreboard* _scoreBoard);
	~PlayerAdvanced();

private:
	// The scores a player can finish on
	int finishingScores[FINISHING_SCORE_COUNT] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 50 };
	// The number of times each finishing score can be divided by two
	int twoFactors[FINISHING_SCORE_COUNT] = { 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 1, 2, 1, 3, 1 };

	// This is a lookup table to decide what target to throw at based on the current score and turn. It gets populated in the player's constructor.
	// [0][0] corresponds to throw 1, score LOWEST_PRECOMPUTED_SCORE. 
	Target precomputedTargets[3][HIGHEST_PRECOMPUTED_SCORE - LOWEST_PRECOMPUTED_SCORE + 1];

	int ratingExactScore = 200; // Added if the finishing score can be reached in 1 throw
	int ratingRiskFinishingDouble = 100; // Added if the finishing score is a double
	int ratingRiskSingle = 50; // Added if the throw is a single
	int ratingRiskDouble = 25; // Added if the throw is a double
	int ratingPowerTwo = 5; // Added for each additional power of two the finishing score has

	Target chooseTarget(int throwNumber, int initialScore);
	Target getPrecomputedTarget(int throwNumber, int currentScore);
	int rateScore(int score);
	void precomputeTargets();
	void displayPrecomputedTargets();
	Target precomputeTarget(int throwNumber, int currentScore);
	Target chooseTargetForThrowScore(int desiredScore);
};
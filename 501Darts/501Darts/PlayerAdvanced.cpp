#include "pch.h"
#include "PlayerAdvanced.h"

#include <iostream>


PlayerAdvanced::PlayerAdvanced(std::string _name, int _skillLevel, SimData* _simData, Scoreboard* _scoreBoard) :
	Player(_name, _skillLevel, _simData, _scoreBoard)
{
}


PlayerAdvanced::~PlayerAdvanced()
{
}


PlayerAdvanced::Target PlayerAdvanced::chooseTarget(int throwNumber)
{
	// If they can win on a bullseye, try it
	if (scoreboard->getGameScore() == 50)
	{
		return Target(50, 1);
	}
	// If they can win on a double, try it
	else if (scoreboard->getGameScore() <= 40 && scoreboard->getGameScore() % 2 == 0)
	{
		return Target(scoreboard->getGameScore() / 2, 2);
	}
	else
	{
		return chooseTargetToGetToFinishingScore();
	}
}


// Choose a target to get closer to a finishing score.
PlayerAdvanced::Target PlayerAdvanced::chooseTargetToGetToFinishingScore()
{
	if (scoreboard->getGameScore() >= 110)
	{
		return Target(20, 3);
	}

	Target bestTarget = Target(0, 0);
	int bestTargetRating = 0;
	for (int i = 0; i < 20; i++)
	{
		int throwScore = scoreboard->getGameScore() - finishingScores[i];
		if (throwScore > 0)
		{
			Target target = chooseTargetForThrowScore(throwScore);

			// Rate the target
			int targetRating = 0;
			if (target.getScore() == throwScore) { targetRating += ratingExactScore; }
			if (target.multiplier == 1) { targetRating += ratingRiskSingle; }
			if (target.multiplier == 2) { targetRating += ratingRiskDouble; }
			targetRating += powerTwos[i] * ratingPowerTwo;

			if (targetRating > bestTargetRating)
			{
				bestTarget = target;
				bestTargetRating = targetRating;
			}
		}
	}
	return bestTarget;
}


// Choose a target to get as close as possible to a desired throw score.
// For example, given 27 it would return double 13.
PlayerAdvanced::Target PlayerAdvanced::chooseTargetForThrowScore(int desiredScore)
{
	if (desiredScore >= 60)
	{
		return Target(20, 3);
	}
	if (desiredScore <= 20)
	{
		return Target(desiredScore, 1);
	}
	else
	{
		Target highestDouble = (desiredScore >= 40) ? Target(20, 2) : Target(desiredScore / 2, 2); // integer division rounds down
		Target highestTreble = Target(desiredScore / 3, 3); // integer division rounds down

		int doubleRemainder = desiredScore - highestDouble.getScore();
		int trebleRemainder = desiredScore - highestTreble.getScore();

		if (doubleRemainder <= trebleRemainder)
		{
			return highestDouble;
		}
		else
		{
			return highestTreble;
		}
	}
}
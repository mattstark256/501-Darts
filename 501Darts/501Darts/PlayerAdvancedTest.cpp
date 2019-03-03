#include "pch.h"
#include "PlayerAdvancedTest.h"

#include <iostream>


PlayerAdvancedTest::PlayerAdvancedTest(std::string _name, int _skillLevel, SimData* _simData, Scoreboard* _scoreBoard) :
	Player(_name, _skillLevel, _simData, _scoreBoard)
{
}


PlayerAdvancedTest::~PlayerAdvancedTest()
{
}


PlayerAdvancedTest::Target PlayerAdvancedTest::chooseTarget(int throwNumber)
{
	// If they can win on a bullseye
	if (scoreboard->getGameScore() == 50)
	{
		return Target(50, 1);
	}
	// If they can win on a double
	else if (scoreboard->getGameScore() <= 40 && scoreboard->getGameScore() % 2 == 0)
	{
		return Target(scoreboard->getGameScore() / 2, 2);
	}
	else
	{
		return chooseTargetToGetToFinishingScore();
	}
}


// Choose a target to get the player score closer to a finishing score.
PlayerAdvancedTest::Target PlayerAdvancedTest::chooseTargetToGetToFinishingScore()
{
	if (scoreboard->getGameScore() >= 110)
	{
		return Target(20, 3);
	}

	Target target = Target(0, 0);
	int targetRating = 0;
	for (int i = 0; i < 20; i++)
	{
		int finishingScore = finishingScores[i];
		int throwScore = scoreboard->getGameScore() - finishingScore;
		if (throwScore > 0)
		{
			Target newTarget = chooseTargetForThrowScore(throwScore);
			int newTargetRating = 0;

			if (newTarget.getScore() == throwScore) { newTargetRating += ratingExactScore; }
			if (newTarget.multiplier == 1) { newTargetRating += ratingRiskSingle; }
			if (newTarget.multiplier == 2) { newTargetRating += ratingRiskDouble; }
			newTargetRating += powerTwos[i] * ratingPowerTwo;

			if (newTargetRating > targetRating)
			{
				target = newTarget;
				targetRating = newTargetRating;
			}
		}
	}
	return target;
}


// Choose a target to get as close as possible to a desired throw score.
PlayerAdvancedTest::Target PlayerAdvancedTest::chooseTargetForThrowScore(int desiredScore)
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
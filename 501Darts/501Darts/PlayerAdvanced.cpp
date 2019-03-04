#include "pch.h"
#include "PlayerAdvanced.h"

#include <iostream>
#include "SimData.h"


PlayerAdvanced::PlayerAdvanced(std::string _name, int _skillLevel, SimData* _simData, Scoreboard* _scoreBoard) :
	Player(_name, _skillLevel, _simData, _scoreBoard)
{
}


PlayerAdvanced::~PlayerAdvanced()
{
}


PlayerAdvanced::Target PlayerAdvanced::chooseTarget(int throwNumber, int initialScore)
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
		// Choose a target that will get them closer to a finishing score
		Target target = chooseTargetToGetToFinishingScore();

		// Decide whether to intentionally bust. Only bust if they can do it using a single (this covers almost all situations while ensuring minimal risk).
		if (throwNumber == 3 && scoreboard->getGameScore() < 20)
		{
			// Compare the scores they would get from busting and playing
			int bustScoreRating = rateScore(initialScore);
			int playScoreRating = rateScore(scoreboard->getGameScore() - target.getScore());
			if (bustScoreRating > playScoreRating)
			{
				// Bust
				target = Target(20, 1);
			}
		}

		return target;
	}
}


// Choose a target to get the player score closer to a finishing score
PlayerAdvanced::Target PlayerAdvanced::chooseTargetToGetToFinishingScore()
{
	// If it's over 100, always aim for T20
	if (scoreboard->getGameScore() >= 100)
	{
		return Target(20, 3);
	}

	Target bestTarget = Target(20, 1); // If the score is 1 this doesn't get overwritten
	int bestTargetRating = 0;
	for (int i = 0; i < FINISHING_SCORE_COUNT; i++)
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
			targetRating += twoFactors[i] * ratingPowerTwo;

			if (targetRating > bestTargetRating)
			{
				bestTarget = target;
				bestTargetRating = targetRating;
			}
		}
	}
	return bestTarget;
}


// Choose a target to get as close as possible to a desired throw score. For example, given 27 it would return D13.
PlayerAdvanced::Target PlayerAdvanced::chooseTargetForThrowScore(int desiredScore)
{
	if (desiredScore >= 60)
	{
		// Checking for this first is more efficient because this will be the most common situation.
		return Target(20, 3);
	}
	else if (desiredScore <= 20)
	{
		// A single is preferable to a double or a treble because it's easier to hit.
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
			// A double is preferable to a treble because it's slightly easier to hit.
			return highestDouble;
		}
		else
		{
			return highestTreble;
		}
	}
}


// Rates a score based on how advantageous it is. For example, 32 gets a high score while 73 gets a low score.
int PlayerAdvanced::rateScore(int score)
{
	int rating = 0;

	for (int i = 0; i < FINISHING_SCORE_COUNT; i++)
	{
		if (finishingScores[i] == score)
		{
			rating += twoFactors[i];
			break;
		}
	}

	return rating;
}
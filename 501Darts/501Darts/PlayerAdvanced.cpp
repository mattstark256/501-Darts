#include "pch.h"
#include "PlayerAdvanced.h"

#include <iostream>


PlayerAdvanced::PlayerAdvanced(std::string _name, int _skillLevel, Scoreboard* _scoreBoard) :
	Player(_name, _skillLevel, _scoreBoard)
{
	playerType = "Advanced";

	precomputeTargets();

	// Uncomment this to view the generated lookup table
	//displayPrecomputedTargets();
}


PlayerAdvanced::~PlayerAdvanced()
{
}


// This is called by Player to decide what to throw at.
PlayerAdvanced::Target PlayerAdvanced::chooseTarget(int throwNumber, int initialScore)
{
	// Choose a target by using the precomputedTargets lookup table
	Target target = getPrecomputedTarget(throwNumber, scoreboard->getGameScore());

	// Decide whether to intentionally bust. Only bust if they can do it using a single (this covers almost all situations while ensuring minimal risk).
	int predictedScore = scoreboard->getGameScore() - target.getScore();
	if (throwNumber == 3 && scoreboard->getGameScore() < 20 && predictedScore != 0)
	{
		// Compare the scores they would get from busting and playing
		int bustScoreRating = rateScore(initialScore);
		int playScoreRating = rateScore(predictedScore);
		if (bustScoreRating > playScoreRating)
		{
			// Bust
			target = Target(20, 1);
		}
	}

	return target;
}


// Choose a target by using the precomputedTargets lookup table.
PlayerAdvanced::Target PlayerAdvanced::getPrecomputedTarget(int throwNumber, int currentScore)
{
	if (scoreboard->getGameScore() >= LOWEST_PRECOMPUTED_SCORE && scoreboard->getGameScore() <= HIGHEST_PRECOMPUTED_SCORE)
	{
		return precomputedTargets[throwNumber - 1][scoreboard->getGameScore() - LOWEST_PRECOMPUTED_SCORE];
	}
	else
	{
		return Target(20, 3);
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
			// 50 is less advantageous than the other finishing scores because it's much harder to hit a bull
			if (score != 50) rating++;
			break;
		}
	}
	return rating;
}


// Populate the precomputedTargets array.
void PlayerAdvanced::precomputeTargets()
{
	for (int throwNumber = 1; throwNumber <= 3; throwNumber++)
	{
		for (int score = LOWEST_PRECOMPUTED_SCORE; score <= HIGHEST_PRECOMPUTED_SCORE; score++)
		{
			precomputedTargets[throwNumber - 1][score - LOWEST_PRECOMPUTED_SCORE] = precomputeTarget(throwNumber, score);
		}
	}
}


// Display the precomputedTargets array. This is useful for debugging.
void PlayerAdvanced::displayPrecomputedTargets()
{
	for (int throwNumber = 1; throwNumber <= 3; throwNumber++)
	{
		for (int score = LOWEST_PRECOMPUTED_SCORE; score <= HIGHEST_PRECOMPUTED_SCORE; score++)
		{
			Target target = precomputedTargets[throwNumber - 1][score - LOWEST_PRECOMPUTED_SCORE];
			std::cout << "Throw: ";
			std::cout << throwNumber;
			std::cout << "  Score: ";
			std::cout << score;
			std::cout << "  Target: ";
			std::cout << target.multiplier;
			std::cout << "x";
			std::cout << target.section;
			std::cout << "  New score: ";
			std::cout << score - target.getScore();
			std::cout << "\n";
		}
	}
}


// Choose a target based on the current throw number and score.
PlayerAdvanced::Target PlayerAdvanced::precomputeTarget(int throwNumber, int currentScore)
{
	// If they can win on a double, try it
	if (currentScore <= 40 && currentScore % 2 == 0)
	{
		return Target(currentScore / 2, 2);
	}
	// If it's their third throw and they can win on a bullseye, try it (if it's their first or second throw it's an unnecessary risk)
	else if (throwNumber == 3 && currentScore == 50)
	{
		return Target(50, 1);
	}

	// If they're not on a finishing score, compare each finishing score to decide which they should try to get to
	Target bestTarget;
	int bestTargetRating = 0;
	for (int i = 0; i < FINISHING_SCORE_COUNT; i++)
	{
		int throwScore = currentScore - finishingScores[i];
		if (throwScore > 0)
		{
			Target target = chooseTargetForThrowScore(throwScore);

			// Rate the target
			int targetRating = 0;
			if (target.getScore() == throwScore) { targetRating += RATING_EXACT_SCORE; }
			if (finishingScores[i] != 50) { targetRating += RATING_RISK_FINISHING_DOUBLE; }
			if (target.multiplier == 1) { targetRating += RATING_RISK_SINGLE; }
			if (target.multiplier == 2) { targetRating += RATING_RISK_DOUBLE; }
			targetRating += twoFactors[i] * RATING_TWO_FACTORS;

			// Never aim for 50 unless it's the only way to win by the end of the turn
			if (throwNumber != 2 && finishingScores[i] == 50) { targetRating = 0; }

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
// Favour singles over doubles and doubles over trebles, because they are easier to hit.
PlayerAdvanced::Target PlayerAdvanced::chooseTargetForThrowScore(int desiredScore)
{
	if (desiredScore >= 60)
	{
		// Scores of 60 and over should always return T20
		return Target(20, 3);
	}
	else if (desiredScore <= 20)
	{
		// Scores of 20 and under should always return a single
		return Target(desiredScore, 1);
	}
	else
	{
		Target highestDouble = (desiredScore >= 40) ? Target(20, 2) : Target(desiredScore / 2, 2); // Integer division rounds down
		Target highestTreble = Target(desiredScore / 3, 3); // Integer division rounds down

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
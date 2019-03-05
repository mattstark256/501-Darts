#include "pch.h"
#include "Player.h"

#include <iostream>
#include "SimData.h"


Player::Player(std::string _name, int _skillLevel, Scoreboard* _scoreBoard) : name(_name), skillLevel(_skillLevel), scoreboard(_scoreBoard)
{
}


Player::~Player()
{
}


void Player::takeTurn(SimData* simData)
{
	bool logEnabled = (simData->getLogDetailLevel() >= 4);

	if (logEnabled)
	{
		if (playerType == "Interactive")
		{
			std::cout << "Your turn\n";
		}
		else
		{
			std::cout << name;
			std::cout << "'s turn\n";
		}
	}

	int throwNumber = 0;
	bool hasWon = false;
	bool hasFailed = false;
	int initialScore = scoreboard->getGameScore();
	while (throwNumber < 3 && !hasWon && !hasFailed)
	{
		throwNumber++;

		Target target = chooseTarget(throwNumber, initialScore);

		if (logEnabled)
		{
			std::cout << "Old score: ";
			std::cout << scoreboard->getGameScore();
			std::cout << "   Target: ";
			std::cout << target.multiplier;
			std::cout << " x ";
			std::cout << target.section;
		}

		ThrowResult throwResult = simData->getDartboard()->throwDart(target.section, target.multiplier, skillLevel);
		scoreboard->decreaseGameScore(throwResult.multipliedScore);

		if (logEnabled)
		{
			std::cout << "   Hit: ";
			std::cout << throwResult.multipliedScore;
			std::cout << "   New score: ";
			std::cout << scoreboard->getGameScore();
			std::cout << "\n";
		}

		if (scoreboard->getGameScore() == 0 && (throwResult.multiplier == 2 || throwResult.multipliedScore == 50))
		{
			hasWon = true;
		}
		else if (scoreboard->getGameScore() < 2)
		{
			hasFailed = true;
			scoreboard->setGameScore(initialScore);

			if (logEnabled)
			{
				std::cout << "The score is too low so the turn is discounted.\n";
			}
		}
	}

	if (logEnabled)
	{
		std::cout << "\n";
	}
}


Player::Target Player::chooseTarget(int throwNumber, int initialScore)
{
	Target target = Target(1, 1);
	Target highestWinningTarget = getHighestWinningTarget(scoreboard->getGameScore());
	// If they can finish in the next throw
	if (scoreboard->getGameScore() == highestWinningTarget.getScore())
	{
		// Throw to win
		target = highestWinningTarget;
	}
	else
	{
		// Throw to get to the highest score they can win from
		int targetScore = scoreboard->getGameScore() - highestWinningTarget.getScore();
		target = getHighestTarget(targetScore);
	}
	return target;
}


// Find the highest target that won't exceed maxScore.
Player::Target Player::getHighestTarget(int maxScore)
{
	// For efficiency, check first for values above 60, because this will often be the case.
	if (maxScore >= 60) { return Target(20, 3); }

	// Only return 50 if maxScore is 50. If it's 51 or over a treble is better.
	if (maxScore == 50) { return Target(50, 1); }

	// Find the highest singles, doubles and trebles that wouldn't exceed maxScore.
	Target highestSingle = Target(0, 1);
	Target highestDouble = Target(0, 2);
	Target highestTreble = Target(0, 3);
	int i = 0;
	while (i < 20)
	{
		i++;
		if (i <= maxScore) { highestSingle.section = i; }
		if (i * 2 <= maxScore) { highestDouble.section = i; }
		if (i * 3 <= maxScore) { highestTreble.section = i; }
	}

	// Return the target with the highest score.
	if (highestTreble.getScore() > highestSingle.getScore() && highestTreble.getScore() > highestDouble.getScore())
	{
		return highestTreble;
	}
	else if (highestDouble.getScore() > highestSingle.getScore())
	{
		return highestDouble;
	}
	else
	{
		return highestSingle;
	}
}


// Find the highest target the player could win with given their current score (eg if their current score was 44 it would be double 20).
Player::Target Player::getHighestWinningTarget(int currentScore)
{
	// For efficiency, check first for values above 50 and 40, because this will often be the case.
	if (currentScore >= 50) { return Target(50, 1); }
	if (currentScore >= 40) { return Target(20, 2); }

	// Find the highest double that wouldn't exceed currentScore.
	Target highestDouble = Target(0, 2);
	int i = 0;
	while (i < 20)
	{
		i++;
		if (i * 2 <= currentScore) { highestDouble.section = i; }
	}

	return highestDouble;
}

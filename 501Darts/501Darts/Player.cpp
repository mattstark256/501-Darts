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


// Take a turn and throw 3 darts. End the turn if they've won or busted.
// All player classes use the same takeTurn function because the rules of a turn are always the same.
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
	bool hasBusted = false;
	int initialScore = scoreboard->getGameScore();
	while (throwNumber < 3 && !hasWon && !hasBusted)
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
			// They've won
			hasWon = true;
		}
		else if (scoreboard->getGameScore() < 2)
		{
			// They've busted
			hasBusted = true;
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


// chooseTarget is a virtual function which is overridden in the other Player classes.
Player::Target Player::chooseTarget(int throwNumber, int initialScore)
{
	return Target(1, 1);
}

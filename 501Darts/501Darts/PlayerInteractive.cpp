#include "pch.h"
#include "PlayerInteractive.h"

#include <iostream>
#include <string>


PlayerInteractive::PlayerInteractive(std::string _name, int _skillLevel, Scoreboard* _scoreBoard) :
	Player(_name, _skillLevel, _scoreBoard)
{
	playerType = "Interactive";
}


PlayerInteractive::~PlayerInteractive()
{
}


// Ask the player what they'd like to aim at and return the response as a Target.
// This is called by Player to decide what to throw at.
PlayerInteractive::Target PlayerInteractive::chooseTarget(int throwNumber, int initialScore)
{
	// Display the throw number and current score
	std::cout << "Throw: ";
	std::cout << throwNumber;
	std::cout << "/3   Score: ";
	std::cout << scoreboard->getGameScore();
	std::cout << "\n";

	Target target = Target();
	bool optionSelected = false;
	while (!optionSelected)
	{
		// Ask the player for an input
		std::cout << "What will you aim at? (eg 9, D14, B)\n";

		std::string input;
		std::getline(std::cin, input);

		// Interpret the input
		target = stringToTarget(input);

		if (target.getScore() != 0)
		{
			optionSelected = true;
		}
	}
	return target;
}


// Interprets the input string and converts it to a Target
PlayerInteractive::Target PlayerInteractive::stringToTarget(std::string string)
{
	// If it's just an int
	int i = stringToInt(string);
	if (i > 0 && i <= 20 || i == 50)
	{
		return Target(i, 1);
	}
	if (i > 20 && i <= 40 && i % 2 == 0)
	{
		return Target(i / 2, 2);
	}
	if (i > 20 && i <= 60 && i % 3 == 0)
	{
		return Target(i / 3, 3);
	}

	// If it's just a char
	char c = string[0];
	if (c == 'B' || c == 'b')
	{
		return Target(50, 1);
	}

	// If it's a combination of a char and an int
	string.erase(0, 1);
	i = stringToInt(string);
	if (i > 0 && i <= 20 || i == 50)
	{
		if (c == 'S' || c == 's')
		{
			return Target(i, 1);
		}
	}
	if (i > 0 && i <= 20)
	{
		if (c == 'D' || c == 'd')
		{
			return Target(i, 2);
		}
		else if (c == 'T' || c == 't')
		{
			return Target(i, 3);
		}
	}

	return Target();
}


// Converts strings to integers. If it can't be converted, return 0.
int PlayerInteractive::stringToInt(std::string string)
{
	// std::stoi throws an exception if it the string isn't valid, it's necessary to use a try-block.
	try
	{
		return std::stoi(string);
	}
	catch (...)
	{
		return 0;
	}
}

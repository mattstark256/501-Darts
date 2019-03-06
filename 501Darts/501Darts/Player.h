#pragma once

class SimData; // Forward declaration is required to prevent circular dependency between Player and SimData.
#include "Scoreboard.h"
#include <string>


// This is the base class for players.
class Player
{
public:
	Player(std::string _name, int _skillLevel, Scoreboard* _scoreBoard);
	~Player();

	// Getters and setters
	std::string getName() { return name; }
	void setName(std::string _name) { name = _name; }
	int getSkillLevel() { return skillLevel; }
	void setSkillLevel(int _skillLevel) { skillLevel = _skillLevel; }
	std::string getPlayerType() { return playerType; }
	Scoreboard* getScoreboard() { return scoreboard; }
	void setScoreboard(Scoreboard* _scoreboard) { scoreboard = _scoreboard; }

	void takeTurn(SimData* simData);

protected:
	std::string name;
	int skillLevel;
	std::string playerType = "Base class"; // Each player class sets this to a different value
	Scoreboard* scoreboard;

	// This is used so that functions in player classes can return both a section and a multiplier (eg double 7)
	struct Target
	{
		Target() { section = 0; multiplier = 0; }
		Target(int _section, int _multiplier) : section(_section), multiplier(_multiplier) {}
		int section;
		int multiplier;
		int getScore() { return section * multiplier; }
	};

	virtual Target chooseTarget(int throwNumber, int initialScore);
};


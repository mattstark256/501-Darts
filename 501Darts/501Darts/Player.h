#pragma once

class SimData; // Forward declaration is required to prevent circular dependency between Player and GameData.
#include "Scoreboard.h"
#include <string>


class Player
{
public:
	Player(std::string _name, int _skillLevel, SimData* _simData, Scoreboard* _scoreBoard);
	~Player();

	std::string getName() { return name; }
	void setName(std::string _name) { name = _name; }
	int getSkillLevel() { return skillLevel; }
	void setSkillLevel(int _skillLevel) { skillLevel = _skillLevel; }
	void setGameData(SimData* _gameData) { simData = _gameData; }
	Scoreboard* getScoreboard() { return scoreboard; }
	void setScoreboard(Scoreboard* _scoreboard) { scoreboard = _scoreboard; }

	void takeTurn();

private:
	std::string name;
	int skillLevel;
	SimData* simData;
	Scoreboard* scoreboard;

	struct Target
	{
		Target(int _section, int _multiplier) : section(_section), multiplier(_multiplier) {}
		int section;
		int multiplier;
		int getScore() { return section * multiplier; }
	};

	Target getHighestTarget(int maxScore);
	Target getHighestWinningTarget(int currentScore);
};


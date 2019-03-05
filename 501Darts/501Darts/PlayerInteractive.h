#pragma once
#include "Player.h"


class PlayerInteractive :
	public Player
{
public:
	PlayerInteractive(std::string _name, int _skillLevel, Scoreboard* _scoreBoard);
	~PlayerInteractive();

private:
	Target chooseTarget(int throwNumber, int initialScore);
	Target stringToTarget(std::string string);
	int stringToInt(std::string string);
};


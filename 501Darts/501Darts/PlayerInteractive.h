#pragma once
#include "Player.h"


// This player ask the user what they should aim at for each throw. 
class PlayerInteractive :
	public Player
{
public:
	PlayerInteractive(std::string _name, int _skillLevel, Scoreboard* _scoreBoard);
	~PlayerInteractive();

protected:
	Target chooseTarget(int throwNumber, int initialScore);

private:
	Target stringToTarget(std::string string);
	int stringToInt(std::string string);
};


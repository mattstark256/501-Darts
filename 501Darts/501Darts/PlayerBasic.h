#pragma once
#include "Player.h"


// This player just tries to get to the nearest finishing score. For example, if their score is 92, they'll try to get to 50. If their score is 27, they'll try to get to 26.
class PlayerBasic :
	public Player
{
public:
	PlayerBasic(std::string _name, int _skillLevel, Scoreboard* _scoreBoard);
	~PlayerBasic();

protected:
	Target chooseTarget(int throwNumber, int initialScore);

private:
	Target getHighestWinningTarget(int currentScore);
	Target getHighestTarget(int maxScore);
};


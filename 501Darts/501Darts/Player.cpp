#include "pch.h"
#include "Player.h"

#include <iostream>
#include "GameData.h"


Player::Player(std::string _name, int _skillLevel, GameData* _gameData, Scoreboard* _scoreBoard) : name(_name), skillLevel(_skillLevel), gameData(_gameData), scoreboard(_scoreBoard)
{
}


Player::~Player()
{
}


void Player::takeTurn()
{
	std::cout << name;
	std::cout << " throws at ";
	int perfectScore = scoreboard->getGameScore();
	if (perfectScore > 50) { perfectScore = 50; }
	std::cout << perfectScore;
	scoreboard->decreaseGameScore(perfectScore);
	std::cout << ". Their new score is ";
	std::cout << scoreboard->getGameScore();
	std::cout << ".";
	std::cout << std::endl;
}

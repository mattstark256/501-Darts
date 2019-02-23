#pragma once

#include "GameData.h"
#include "Game.h"


class UserInterface
{
public:
	UserInterface(GameData* _gameData, Game* _game);
	~UserInterface();

	void startSession();

private:
	GameData* gameData;
	Game* game;
};


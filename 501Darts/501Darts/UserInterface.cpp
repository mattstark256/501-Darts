#include "pch.h"
#include "UserInterface.h"

#include <iostream>


UserInterface::UserInterface(GameData* _gameData, Game* _game) : gameData(_gameData), game(_game)
{
}


UserInterface::~UserInterface()
{
}


void UserInterface::startSession()
{
	std::cout << "Playing 1 championship.";
	std::cout << std::endl;
	game->playChampionship();
}

#pragma once

#include "GameData.h"
#include "Game.h"
#include <string>


class UserInterface
{
public:
	UserInterface(GameData* _gameData, Game* _game);
	~UserInterface();

	void startSession();

private:
	GameData* gameData;
	Game* game;
	bool simulationHasBeenRun = false; // If true, the "re-run last simulation" option will be shown

	void mainMenu();
	void simulationSetup();
	void settingsMenu();
	void playerEditor();
	void changeName(int player);
	void changeSkillLevel(int player);
	int getIntInput();
	std::string getStringInput();
};


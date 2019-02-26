#pragma once

#include "SimData.h"
#include "Simulator.h"
#include <string>


class UserInterface
{
public:
	UserInterface(SimData* _gameData, Simulator* _game);
	~UserInterface();

	void startSession();

private:
	SimData* simData;
	Simulator* simulator;
	bool simulationHasBeenRun = false; // If true, the "re-run last simulation" option will be shown

	void mainMenu();
	void simulationSetup();
	void settingsMenu();
	void playerEditor();
	void changeName(int player);
	void changeSkillLevel(int player);
	void changeDartboardType();
	int getIntInput();
	std::string getStringInput();
};


#pragma once

#include "SimData.h"
#include "Simulator.h"
#include <string>


// This class contains all the application's menus. The menus allow the user to run simulations or modify the simData objects.
class UserInterface
{
public:
	UserInterface(SimData* _simData, SimData* _simDataInteractive, Simulator* _simulator);
	~UserInterface();

	void startSession();

private:
	SimData* simData;
	SimData* simDataInteractive;
	Simulator* simulator;
	bool simulationHasBeenRun = false; // If true, the "re-run last simulation" option will be shown

	void mainMenu();
	void simulationSetup();
	void gameSetup();
	void settingsMenu();
	void playerEditor();
	void changeName(int player);
	void changeSkillLevel(int player);
	void changeAIType(int player);
	void changeDartboardType();
	int getIntInput();
	std::string getStringInput();
};


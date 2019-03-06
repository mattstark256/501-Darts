#include "pch.h"
#include <iostream>

#include "UserInterface.h"
#include "Simulator.h"
#include "SimData.h"
#include "DartboardProvided.h"
#include "PlayerAdvanced.h"
#include "PlayerInteractive.h"

#include <stdlib.h> // srand, rand
#include <time.h> // time


int main()
{
	// Initialize random number generator
	srand(time(0));

	// Create dartboard
	Dartboard* dartboard = new DartboardProvided();
	
	// Create players
	Player* player0 = new PlayerAdvanced("Joe", 70, new Scoreboard());
	Player* player1 = new PlayerAdvanced("Sid", 70, new Scoreboard());
	Player* playerInteractive = new PlayerInteractive("INTERACTIVE PLAYER", 70, new Scoreboard());

	// Create simData for non-interactive simulation
	SimData* simData = new SimData();
	simData->setDartboard(dartboard);
	simData->setPlayer(0, player0);
	simData->setPlayer(1, player1);

	// Create simData for interactive simulation
	SimData* simDataInteractive = new SimData();
	simDataInteractive->setDartboard(dartboard);
	simDataInteractive->setPlayer(0, playerInteractive);

	// Create simulator
	Simulator* simulator = new Simulator();

	// Create user interface
	UserInterface* userInterface = new UserInterface(simData, simDataInteractive, simulator);
	userInterface->startSession();
}

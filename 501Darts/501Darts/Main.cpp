#include "pch.h"
#include <iostream>

#include "UserInterface.h"
#include "Simulator.h"
#include "SimData.h"
#include "DartboardProvided.h"
#include "PlayerAdvanced.h"
#include "PlayerAdvancedTest.h"
#include "PlayerInteractive.h"
#include <stdlib.h> // srand, rand
#include <time.h> // time


int main()
{
	// Initialize random number generator
	srand(time(0));

	SimData* simData = new SimData();
	SimData* simDataInteractive = new SimData();


	Dartboard* dartboard = new DartboardProvided();
	simData->setDartboard(dartboard);
	simDataInteractive->setDartboard(dartboard);
	
	Player* player0 = new PlayerAdvanced("Joe", 70, new Scoreboard());
	Player* player1 = new PlayerAdvanced("Sid", 70, new Scoreboard());
	Player* playerYou = new PlayerInteractive("INTERACTIVE PLAYER", 70, new Scoreboard());

	simData->setPlayer(0, player0);
	simData->setPlayer(1, player1);
	simDataInteractive->setPlayer(0, playerYou);

	Simulator* simulator = new Simulator();

	UserInterface* userInterface = new UserInterface(simData, simDataInteractive, simulator);

	userInterface->startSession();
}

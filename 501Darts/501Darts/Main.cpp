#include "pch.h"
#include <iostream>

#include "UserInterface.h"
#include "Simulator.h"
#include "SimData.h"
#include "DartboardProvided.h"
#include <stdlib.h> // srand, rand
#include <time.h> // time


int main()
{
	// Initialize random number generator
	srand(time(0));

	SimData simData = SimData();
	simData.setDartboard(new DartboardProvided());
	
	simData.setPlayer(0, new Player("Sid", 70, &simData, new Scoreboard()));
	simData.setPlayer(1, new Player("Joe", 70, &simData, new Scoreboard()));
	Simulator game = Simulator(&simData);
	UserInterface userInterface = UserInterface(&simData, &game);

	simData.setLogDetailLevel(0);
	simData.setStartingPlayer(0);

	userInterface.startSession();
}

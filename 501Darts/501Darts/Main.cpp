#include "pch.h"
#include <iostream>

#include "UserInterface.h"
#include "Game.h"
#include "GameData.h"
#include <stdlib.h> // srand, rand
#include <time.h> // time

#include "DartboardProvided.h"


int main()
{
	// Initialize random number generator
	srand(time(0));

	GameData gameData = GameData();
	gameData.setDartboard(new DartboardProvided());
	
	gameData.setPlayer(0, new Player("Sid", 70, &gameData, new Scoreboard()));
	gameData.setPlayer(1, new Player("Joe", 70, &gameData, new Scoreboard()));
	Game game = Game(&gameData);
	UserInterface userInterface = UserInterface(&gameData, &game);

	gameData.setLogDetailLevel(0);
	gameData.setStartingPlayer(0);

	userInterface.startSession();
}

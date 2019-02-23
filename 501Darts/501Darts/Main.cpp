#include "pch.h"
#include <iostream>

#include "UserInterface.h"
#include "Game.h"
#include "GameData.h"
#include <stdlib.h> // srand, rand
#include <time.h> // time


int main()
{
    std::cout << "Matt's Darts Application\n"; 

	// Initialize random number generator
	srand(time(0));

	GameData gameData = GameData();
	gameData.setDartboard(new Dartboard());
	
	gameData.setPlayer(0, new Player("Sid", 70, &gameData, new Scoreboard()));
	gameData.setPlayer(1, new Player("Joe", 70, &gameData, new Scoreboard()));
	Game game = Game(&gameData);
	UserInterface userInterface = UserInterface(&gameData, &game);

	userInterface.startSession();
}

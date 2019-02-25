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
	std::cout << "MATT'S DARTS SIMULATOR\n\n";
	mainMenu();
}


void UserInterface::mainMenu()
{
	bool quitting = false;
	while (!quitting)
	{
		std::cout << "MAIN MENU\n";
		std::cout << "1: Run new simulation\n";
		std::cout << "2: Settings\n";
		if (simulationHasBeenRun)
		{
			std::cout << "3: Re-run last simulation\n";
		}
		std::cout << "0: Quit\n";

		int input = getIntInput();

		if (input == 1) {
			simulationSetup();
		}
		else if (input == 2) {
			settingsMenu();
		}
		else if (input == 3 && simulationHasBeenRun) {
			game->playChampionships();
		}
		else if (input == 0) {
			quitting = true;
		}
	}

}


void UserInterface::simulationSetup()
{
	bool quitting = false;
	bool optionSelected = false;
	int input;

	// The gameData values are not modified until the simulation is ready to be run. This is so if you cancel, you won't overwrite the last simulation's settings.
	int championshipsNumber;
	int startingPlayer;
	int logDetailLevel;

	std::cout << "SIMULATION SETUP\n";

	// Select number of championships to simulate
	while (!optionSelected && !quitting)
	{
		std::cout << "How many championships should be simulated? (0 to cancel)\n";

		input = getIntInput();

		if (input > 0) {
			optionSelected = true;
			championshipsNumber = input;
		}
		else if (input == 0) {
			quitting = true;
		}
	}

	// Select who should throw first
	optionSelected = false;
	while (!optionSelected && !quitting)
	{
		std::cout << "Who should throw first at the start of each championship?\n";
		std::cout << "1: ";
		std::cout << gameData->getPlayer(0)->getName();
		std::cout << "\n";
		std::cout << "2: ";
		std::cout << gameData->getPlayer(1)->getName();
		std::cout << "\n";
		std::cout << "3: Randomize it each time\n";
		std::cout << "0: Cancel\n";

		input = getIntInput();

		if (input == 1) {
			optionSelected = true;
			startingPlayer = 0;
		}
		else if (input == 2) {
			optionSelected = true;
			startingPlayer = 1;
		}
		else if (input == 3) {
			optionSelected = true;
			startingPlayer = 2;
		}
		else if (input == 0) {
			quitting = true;
		}
	}

	// Select how detailed the results should be
	optionSelected = false;
	while (!optionSelected && !quitting)
	{
		std::cout << "How detailed should the results be?\n";
		std::cout << "1: Low\n";
		std::cout << "2: High (This is slower so is not recommended for simulations of 10 or more championships)\n";
		std::cout << "0: Cancel\n";

		input = getIntInput();

		if (input == 1) {
			optionSelected = true;
			logDetailLevel = 0;
		}
		else if (input == 2) {
			optionSelected = true;
			logDetailLevel = 4;
		}
		else if (input == 0) {
			quitting = true;
		}
	}

	if (!quitting)
	{
		gameData->setChampionshipsNumber(championshipsNumber);
		gameData->setStartingPlayer(startingPlayer);
		gameData->setLogDetailLevel(logDetailLevel);
		game->playChampionships();
		simulationHasBeenRun = true;
	}
}


void UserInterface::settingsMenu()
{
	bool quitting = false;
	while (!quitting)
	{
		std::cout << "SETTINGS\n";
		std::cout << "1: Edit player\n";
		std::cout << "2: Edit dartboard\n";
		std::cout << "0: Cancel\n";

		int input = getIntInput();

		if (input == 1) {
			playerEditor();
		}
		else if (input == 2) {
			std::cout << "There's currently only one dartboard type.\n\n";
		}
		else if (input == 0) {
			quitting = true;
		}
	}
}


void UserInterface::playerEditor()
{
	bool quitting = false;
	bool optionSelected = false;
	int editedPlayer;

	while (!quitting && !optionSelected)
	{
		std::cout << "Which player would you like to edit?\n";
		std::cout << "1: ";
		std::cout << gameData->getPlayer(0)->getName();
		std::cout << "\n";
		std::cout << "2: ";
		std::cout << gameData->getPlayer(1)->getName();
		std::cout << "\n";
		std::cout << "0: Cancel\n";

		int input = getIntInput();

		if (input == 1 || input == 2) {
			optionSelected = true;
			editedPlayer = input - 1;
		}
		else if (input == 0) {
			quitting = true;
		}
	}

	while (!quitting)
	{
		std::cout << "EDIT PLAYER (";
		std::cout << gameData->getPlayer(editedPlayer)->getName();
		std::cout << ")\n";
		std::cout << "1: Change name\n";
		std::cout << "2: Change skill level\n";
		std::cout << "0: Cancel\n";

		int input = getIntInput();

		if (input == 1) {
			changeName(editedPlayer);
		}
		else if (input == 2) {
			changeSkillLevel(editedPlayer);
		}
		else if (input == 0) {
			quitting = true;
		}
	}
}


void UserInterface::changeName(int player)
{
	std::cout << "What should ";
	std::cout << gameData->getPlayer(player)->getName();
	std::cout << "'s new name be? (0 to cancel)\n";

	std::string newName = getStringInput();

	if (newName != "0")
	{
		std::cout << gameData->getPlayer(player)->getName();
		std::cout << "'s name has been changed to ";
		std::cout << newName;
		std::cout << ".\n\n";
		gameData->getPlayer(player)->setName(newName);
	}
}


void UserInterface::changeSkillLevel(int player)
{
	bool quitting = false;
	while (!quitting)
	{
		std::cout << "What should ";
		std::cout << gameData->getPlayer(player)->getName();
		std::cout << "'s new skill level be? It's currently ";
		std::cout << gameData->getPlayer(player)->getSkillLevel();
		std::cout << ". (0 to cancel)\n";

		int newSkillLevel = getIntInput();

		if (newSkillLevel > 0 && newSkillLevel <= 100)
		{
			std::cout << gameData->getPlayer(player)->getName();
			std::cout << "'s skill level has been changed to ";
			std::cout << newSkillLevel;
			std::cout << ".\n\n";
			gameData->getPlayer(player)->setSkillLevel(newSkillLevel);
			quitting = true;
		}
		else if (newSkillLevel > 100)
		{
			std::cout << "Skill level can't be greater than 100.\n\n";
		}
		else if (newSkillLevel < 0)
		{
			std::cout << "Skill level can't be less than 0.\n\n";
		}
		else if (newSkillLevel == 0)
		{
			quitting = true;
		}
	}
}


// Gets the users input as an int. Non-int values will return 0.
int UserInterface::getIntInput()
{
	int input;
	std::cin >> input;
	std::cout << "\n";

	// Handle non-int inputs
	std::cin.clear(); // Clear the error flags
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any input waiting in the stream

	return input;
}

// Gets the users input as a string.
std::string UserInterface::getStringInput()
{
	std::string input;
	std::getline(std::cin, input);
	std::cout << "\n";

	return input;
}

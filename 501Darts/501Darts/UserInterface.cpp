#include "pch.h"
#include "UserInterface.h"

#include <iostream>
#include "DartboardProvided.h"
#include "DartboardVector.h"
#include "PlayerBasic.h"
#include "PlayerAdvanced.h"


UserInterface::UserInterface(SimData* _simData, SimData* _simDataInteractive, Simulator* _simulator) : simData(_simData), simDataInteractive(_simDataInteractive), simulator(_simulator)
{
}


UserInterface::~UserInterface()
{
}


// Start a user interface session. Called by main()
void UserInterface::startSession()
{
	// Title
	std::cout << "\n";
	std::cout << "      ___  ___\n";
	std::cout << "    ____  /___\\___.-----.___\n";
	std::cout << "      ___ \\___/   '-----'\n";
	std::cout << "\n";
	std::cout << "   MATT'S 501 DARTS SIMULATOR\n";
	std::cout << "\n\n";

	mainMenu();
}


// Main menu
void UserInterface::mainMenu()
{
	bool quitting = false;
	while (!quitting)
	{
		std::cout << "MAIN MENU\n";
		std::cout << "1: Run new simulation\n";
		std::cout << "2: Play game\n";
		std::cout << "3: Settings\n";
		if (simulationHasBeenRun)
		{
			std::cout << "4: Re-run last simulation\n";
		}
		std::cout << "0: Quit\n";

		int input = getIntInput();

		if (input == 1) {
			simulationSetup();
		}
		else if (input == 2) {
			gameSetup();
		}
		else if (input == 3) {
			settingsMenu();
		}
		else if (input == 4 && simulationHasBeenRun) {
			simulator->playChampionships(simData);
		}
		else if (input == 0) {
			quitting = true;
		}
	}
}


// Input simulation settings then run a simulation
void UserInterface::simulationSetup()
{
	bool quitting = false;
	bool optionSelected = false;
	int input;

	// The simData values are not modified until the simulation is ready to be run. This is so if you cancel, you won't overwrite the previous settings.
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
		std::cout << "1: Randomize it each time (50/50)\n";
		std::cout << "2: ";
		std::cout << simData->getPlayer(0)->getName();
		std::cout << "\n";
		std::cout << "3: ";
		std::cout << simData->getPlayer(1)->getName();
		std::cout << "\n";
		std::cout << "0: Cancel\n";

		input = getIntInput();

		if (input == 1) {
			optionSelected = true;
			startingPlayer = 2;
		}
		else if (input == 2) {
			optionSelected = true;
			startingPlayer = 0;
		}
		else if (input == 3) {
			optionSelected = true;
			startingPlayer = 1;
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

	// Run the simulation
	if (!quitting)
	{
		simData->setChampionshipsNumber(championshipsNumber);
		simData->setStartingPlayerChampionship(startingPlayer);
		simData->setLogDetailLevel(logDetailLevel);
		simulator->playChampionships(simData);
		simulationHasBeenRun = true;
	}
}


// Input game settings then run a game
void UserInterface::gameSetup()
{
	bool quitting = false;
	bool optionSelected = false;
	int input;
	int gameType; // 0 = game, 1 = championship

	// Choose between game and championship
	optionSelected = false;
	while (!optionSelected && !quitting)
	{
		std::cout << "Would you like to play a game or a championship?\n";
		std::cout << "1: Game\n";
		std::cout << "2: Championship (Takes a long time)\n";
		std::cout << "0: Cancel\n";

		input = getIntInput();

		if (input == 1) {
			optionSelected = true;
			gameType = 0;
		}
		else if (input == 2) {
			optionSelected = true;
			gameType = 1;
		}
		else if (input == 0) {
			quitting = true;
		}
	}

	// Select who to play against
	optionSelected = false;
	while (!optionSelected && !quitting)
	{
		std::cout << "Who would you like to play against?\n";
		std::cout << "1: ";
		std::cout << simData->getPlayer(0)->getName();
		std::cout << "\n";
		std::cout << "2: ";
		std::cout << simData->getPlayer(1)->getName();
		std::cout << "\n";
		std::cout << "0: Cancel\n";

		input = getIntInput();

		if (input == 1) {
			optionSelected = true;
			simDataInteractive->setPlayer(1, simData->getPlayer(0));
		}
		else if (input == 2) {
			optionSelected = true;
			simDataInteractive->setPlayer(1, simData->getPlayer(1));
		}
		else if (input == 0) {
			quitting = true;
		}
	}

	// Select a skill level
	optionSelected = false;
	while (!optionSelected && !quitting)
	{
		std::cout << "What should your skill level be? ";
		std::cout << simDataInteractive->getPlayer(1)->getName();
		std::cout << "'s skill level is ";
		std::cout << simDataInteractive->getPlayer(1)->getSkillLevel();
		std::cout << ". (0 to cancel)\n";

		input = getIntInput();

		if (input > 0 && input <= 100)
		{
			optionSelected = true;
			simDataInteractive->getPlayer(0)->setSkillLevel(input);
		}
		else if (input > 100)
		{
			std::cout << "Skill level can't be greater than 100.\n\n";
		}
		else if (input < 0)
		{
			std::cout << "Skill level can't be less than 0.\n\n";
		}
		else if (input == 0)
		{
			quitting = true;
		}
	}

	// Select who should throw first
	optionSelected = false;
	while (!optionSelected && !quitting)
	{
		std::cout << "Who should throw first?\n";
		std::cout << "1: Me\n";
		std::cout << "2: ";
		std::cout << simDataInteractive->getPlayer(1)->getName();
		std::cout << "\n";
		std::cout << "0: Cancel\n";

		input = getIntInput();

		if (input == 1) {
			optionSelected = true;
			simDataInteractive->setStartingPlayerChampionship(0);
			simDataInteractive->setStartingPlayerGame(0);
		}
		else if (input == 2) {
			optionSelected = true;
			simDataInteractive->setStartingPlayerChampionship(1);
			simDataInteractive->setStartingPlayerGame(1);
		}
		else if (input == 0) {
			quitting = true;
		}
	}

	// Start the game
	if (!quitting)
	{
		simDataInteractive->setLogDetailLevel(4);
		if (gameType == 0)
		{
			simulator->playGame(simDataInteractive, 0);
		}
		else
		{
			simulator->playChampionship(simDataInteractive, 0);
		}
	}
}


// Settings menu
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
			changeDartboardType();
		}
		else if (input == 0) {
			quitting = true;
		}
	}
}


// Player modification options
void UserInterface::playerEditor()
{
	bool quitting = false;
	bool optionSelected = false;
	int editedPlayer;

	// Choose which player to edit
	while (!quitting && !optionSelected)
	{
		std::cout << "Which player would you like to edit?\n";
		std::cout << "1: ";
		std::cout << simData->getPlayer(0)->getName();
		std::cout << "\n";
		std::cout << "2: ";
		std::cout << simData->getPlayer(1)->getName();
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
		std::cout << simData->getPlayer(editedPlayer)->getName();
		std::cout << ")\n";
		std::cout << "1: Change name\n";
		std::cout << "2: Change skill level\n";
		std::cout << "3: Change AI type\n";
		std::cout << "0: Cancel\n";

		int input = getIntInput();

		if (input == 1) {
			changeName(editedPlayer);
		}
		else if (input == 2) {
			changeSkillLevel(editedPlayer);
		}
		else if (input == 3) {
			changeAIType(editedPlayer);
		}
		else if (input == 0) {
			quitting = true;
		}
	}
}


// Change a player's name
void UserInterface::changeName(int playerIndex)
{
	std::cout << "What should ";
	std::cout << simData->getPlayer(playerIndex)->getName();
	std::cout << "'s new name be? (0 to cancel)\n";

	std::string newName = getStringInput();

	if (newName != "0")
	{
		std::cout << simData->getPlayer(playerIndex)->getName();
		std::cout << "'s name has been changed to ";
		std::cout << newName;
		std::cout << ".\n\n";
		simData->getPlayer(playerIndex)->setName(newName);
	}
}


// Change a player's skill level
void UserInterface::changeSkillLevel(int playerIndex)
{
	bool quitting = false;
	while (!quitting)
	{
		std::cout << "What should ";
		std::cout << simData->getPlayer(playerIndex)->getName();
		std::cout << "'s new skill level be? It's currently ";
		std::cout << simData->getPlayer(playerIndex)->getSkillLevel();
		std::cout << ". (0 to cancel)\n";

		int newSkillLevel = getIntInput();

		if (newSkillLevel > 0 && newSkillLevel <= 100)
		{
			std::cout << simData->getPlayer(playerIndex)->getName();
			std::cout << "'s skill level has been changed to ";
			std::cout << newSkillLevel;
			std::cout << ".\n\n";
			simData->getPlayer(playerIndex)->setSkillLevel(newSkillLevel);
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


// Change a player's AI type (switch between different Player classes)
void UserInterface::changeAIType(int playerIndex)
{
	bool quitting = false;
	while (!quitting)
	{
		Player* player = simData->getPlayer(playerIndex);

		std::cout << "What AI type should ";
		std::cout << player->getName();
		std::cout << " use? Currently using the ";
		std::cout << player->getPlayerType();
		std::cout << " AI.\n";
		std::cout << "1: Basic\n";
		std::cout << "2: Advanced\n";
		std::cout << "0: Cancel\n";

		int input = getIntInput();

		if (input == 1) {
			std::cout << "AI type has been set to Basic.\n\n";
			if (player->getPlayerType() != "Basic")
			{
				simData->setPlayer(playerIndex, new PlayerBasic(player->getName(), player->getSkillLevel(), player->getScoreboard()));
			}
			quitting = true;
		}
		else if (input == 2) {
			std::cout << "AI type has been set to Advanced.\n\n";
			if (player->getPlayerType() != "Advanced")
			{
				simData->setPlayer(playerIndex, new PlayerAdvanced(player->getName(), player->getSkillLevel(), player->getScoreboard()));
			}
			quitting = true;
		}
		else if (input == 0) {
			quitting = true;
		}
	}
}


// Change the dartboard type (switch between different Dartboard classes)
void UserInterface::changeDartboardType()
{
	bool quitting = false;
	while (!quitting)
	{
		std::cout << "What dartboard type should be used? Currently using the ";
		std::cout << simData->getDartboard()->getDartboardType();
		std::cout << " dartboard.\n";
		std::cout << "1: Default - Uses the functions provided in the brief\n";
		std::cout << "2: Vector - Uses vectors to simulate accuracy based on skill level (slower because it uses trigonometry)\n";
		std::cout << "0: Cancel\n";

		int input = getIntInput();

		if (input == 1) {
			std::cout << "Dartboard type has been set to Default.\n\n";
			if (simData->getDartboard()->getDartboardType() != "Default")
			{
				Dartboard* dartboard = new DartboardProvided();
				simData->setDartboard(dartboard);
				simDataInteractive->setDartboard(dartboard);
			}
			quitting = true;
		}
		else if (input == 2) {
			std::cout << "Dartboard type has been set to Vector.\n\n";
			if (simData->getDartboard()->getDartboardType() != "Vector")
			{
				Dartboard* dartboard = new DartboardVector();
				simData->setDartboard(dartboard);
				simDataInteractive->setDartboard(dartboard);
			}
			quitting = true;
		}
		else if (input == 0) {
			quitting = true;
		}
	}
}


// Gets the users input as an int. Non-int values return 0.
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

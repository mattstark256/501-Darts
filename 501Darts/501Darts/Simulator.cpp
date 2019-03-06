#include "pch.h"
#include "Simulator.h"

#include <iostream>


Simulator::Simulator()
{
	statistics = new Statistics();
}


Simulator::~Simulator()
{
}


// Simulate a series of championships and print the results. The number of championships to be simulated is determined by the championshipsNumber variable in simData.
void Simulator::playChampionships(SimData* simData)
{
	std::cout << "Starting simulation\n\n";

	statistics->resetStatistics();
	simData->getPlayer(0)->getScoreboard()->resetChampionshipsWon();
	simData->getPlayer(1)->getScoreboard()->resetChampionshipsWon();

	for (int championshipNumber = 1; championshipNumber <= simData->getChampionshipsNumber(); championshipNumber++)
	{
		playChampionship(simData, championshipNumber);
		statistics->recordChampionshipResult(simData);

		if (simData->getLogDetailLevel() == 0)
		{
			// Show a loading bar and log progress every 1000 championships
			showSimulationProgress(championshipNumber, simData->getChampionshipsNumber());
		}
	}

	std::cout << "Simulation complete\n\n";
	statistics->printStatistics(simData);
}


// Simulate a championship
void Simulator::playChampionship(SimData* simData, int championshipNumber)
{
	bool logEnabled = (simData->getLogDetailLevel() >= 1);

	if (logEnabled)
	{
		std::cout << "Starting championship ";
		if (championshipNumber != 0) { std::cout << championshipNumber; }
		std::cout << "\n\n";
	}

	// Decide who should throw first
	if (simData->getStartingPlayerChampionship() == 2)
	{
		simData->setStartingPlayerGame(rand() % 2);
	}
	else
	{
		simData->setStartingPlayerGame(simData->getStartingPlayerChampionship());
	}

	simData->getPlayer(0)->getScoreboard()->resetSetsWon();
	simData->getPlayer(1)->getScoreboard()->resetSetsWon();

	// Play sets until a player has won 7
	int setNumber = 0;
	bool championshipHasBeenWon = false;
	while (!championshipHasBeenWon)
	{
		setNumber++;
		playSet(simData, setNumber);

		// Check if a player has won
		for (int i : {0, 1})
		{
			if (simData->getPlayer(i)->getScoreboard()->getSetsWon() == 7)
			{
				championshipHasBeenWon = true;
				simData->getPlayer(i)->getScoreboard()->incrementChampionshipsWon();

				if (logEnabled)
				{
					if (simData->getPlayer(i)->getPlayerType() == "Interactive")
					{
						std::cout << "You won the championship! (7 : ";
					}
					else
					{
						std::cout << simData->getPlayer(i)->getName();
						std::cout << " won the championship! (7 : ";
					}
					std::cout << simData->getPlayer(1 - i)->getScoreboard()->getSetsWon();
					std::cout << ")\n\n";
				}
			}
		}
	}
}


// Simulate a set
void Simulator::playSet(SimData* simData, int setNumber)
{
	bool logEnabled = (simData->getLogDetailLevel() >= 2);

	if (logEnabled)
	{
		std::cout << "Starting set ";
		if (setNumber != 0) { std::cout << setNumber; }
		std::cout << "\n\n";
	}

	simData->getPlayer(0)->getScoreboard()->resetGamesWon();
	simData->getPlayer(1)->getScoreboard()->resetGamesWon();

	// Play games until a player has won 3
	int gameNumber = 0;
	bool setHasBeenWon = false;
	while (!setHasBeenWon)
	{
		gameNumber++;
		playGame(simData, gameNumber);

		// Switch who starts the next game
		simData->setStartingPlayerGame(1 - simData->getStartingPlayerGame());

		// Check if a player has won
		for (int i : {0, 1})
		{
			if (simData->getPlayer(i)->getScoreboard()->getGamesWon() == 3)
			{
				setHasBeenWon = true;
				simData->getPlayer(i)->getScoreboard()->incrementSetsWon();

				if (logEnabled)
				{
					if (simData->getPlayer(i)->getPlayerType() == "Interactive")
					{
						std::cout << "You won the set!\n\n";
					}
					else
					{
						std::cout << simData->getPlayer(i)->getName();
						std::cout << " won the set!\n\n";
					}
				}
			}
		}
	}
}


// Simulate a game
void Simulator::playGame(SimData* simData, int gameNumber)
{
	bool logEnabled = (simData->getLogDetailLevel() >= 3);

	if (logEnabled)
	{
		std::cout << "Starting game ";
		if (gameNumber != 0) { std::cout << gameNumber; }
		std::cout << "\n\n";
	}

	simData->getPlayer(0)->getScoreboard()->resetGameScore();
	simData->getPlayer(1)->getScoreboard()->resetGameScore();

	// Take turns until a player has won
	bool gameHasBeenWon = false;
	while (!gameHasBeenWon)
	{
		for (int i : {simData->getStartingPlayerGame(), 1 - simData->getStartingPlayerGame()})
		{
			if (!gameHasBeenWon)
			{
				simData->getPlayer(i)->takeTurn(simData);

				// Check if a player has won
				if (simData->getPlayer(i)->getScoreboard()->getGameScore() == 0)
				{
					gameHasBeenWon = true;
					simData->getPlayer(i)->getScoreboard()->incrementGamesWon();

					if (logEnabled)
					{
						if (simData->getPlayer(i)->getPlayerType() == "Interactive")
						{
							std::cout << "You won the game!\n\n";
						}
						else
						{
							std::cout << simData->getPlayer(i)->getName();
							std::cout << " won the game!\n\n";
						}
					}
				}
			}
		}
	}
}


// Show a loading bar and log progress every 1000 championships
void Simulator::showSimulationProgress(int completed, int total)
{
	if (total >= 1000)
	{
		if (completed % 100 == 0)
		{
			std::cout << "-";
		}
		if (completed % 1000 == 0 || completed == total)
		{
			std::cout << " ";
			std::cout << completed;
			std::cout << " championships complete";
			std::cout << "\n";
		}
		if (completed == total)
		{
			std::cout << "\n";
		}
	}
}

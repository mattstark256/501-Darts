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


void Simulator::playChampionships(SimData* simData)
{
	statistics->setSimData(simData);

	std::cout << "Starting simulation\n\n";

	statistics->resetStatistics();
	simData->getPlayer(0)->getScoreboard()->resetChampionshipsWon();
	simData->getPlayer(1)->getScoreboard()->resetChampionshipsWon();
	for (int i = 0; i < simData->getChampionshipsNumber(); i++)
	{
		playChampionship(simData, i + 1);
		statistics->recordChampionshipResult();

		// Show a loading bar and log progress every 1000 championships
		int j = i + 1;
		if (simData->getLogDetailLevel() == 0 && simData->getChampionshipsNumber() >= 1000)
		{
			if (j % 100 == 0)
			{
				std::cout << "-";
			}
			if (j % 1000 == 0)
			{
				std::cout << " ";
				std::cout << j;
				std::cout << " championships complete\n\n";
			}
		}
	}

	std::cout << "Simulation complete\n\n";
	statistics->printStatistics();
}


void Simulator::playChampionship(SimData* simData, int championshipNumber)
{
	bool logEnabled = (simData->getLogDetailLevel() >= 1);

	if (logEnabled)
	{
		std::cout << "Starting championship ";
		if (championshipNumber != 0) { std::cout << championshipNumber; }
		std::cout << "\n\n";
	}

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
	int setNumber = 0;
	bool championshipHasBeenWon = false;
	while (!championshipHasBeenWon)
	{
		setNumber++;
		playSet(simData, setNumber);

		for (int i : {0, 1})
		{
			if (simData->getPlayer(i)->getScoreboard()->getSetsWon() == 7)
			{
				championshipHasBeenWon = true;
				simData->getPlayer(i)->getScoreboard()->incrementChampionshipsWon();

				if (logEnabled)
				{
					std::cout << simData->getPlayer(i)->getName();
					std::cout << " won the championship! (7 : ";
					std::cout << simData->getPlayer(1 - i)->getScoreboard()->getSetsWon();
					std::cout << ")\n\n";
				}
			}
		}
	}
}


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
	int gameNumber = 0;
	bool setHasBeenWon = false;
	while (!setHasBeenWon)
	{
		gameNumber++;
		playGame(simData, gameNumber);

		for (int i : {0, 1})
		{
			if (simData->getPlayer(i)->getScoreboard()->getGamesWon() == 3)
			{
				setHasBeenWon = true;
				simData->getPlayer(i)->getScoreboard()->incrementSetsWon();

				if (logEnabled)
				{
					std::cout << simData->getPlayer(i)->getName();
					std::cout << " won the set! (3 : ";
					std::cout << simData->getPlayer(1 - i)->getScoreboard()->getGamesWon();
					std::cout << ")\n\n";
				}
			}
		}
	}
}


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
	bool gameHasBeenWon = false;
	while (!gameHasBeenWon)
	{
		for (int i : {simData->getStartingPlayerGame(), 1 - simData->getStartingPlayerGame()})
		{
			if (!gameHasBeenWon)
			{
				simData->getPlayer(i)->takeTurn(simData);

				if (simData->getPlayer(i)->getScoreboard()->getGameScore() == 0)
				{
					gameHasBeenWon = true;
					simData->getPlayer(i)->getScoreboard()->incrementGamesWon();

					// Switch who starts the next game
					simData->setStartingPlayerGame(1 - simData->getStartingPlayerGame());

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
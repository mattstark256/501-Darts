#include "pch.h"
#include "Simulator.h"

#include <iostream>


Simulator::Simulator(SimData* _simData) : simData(_simData)
{
	statistics = new Statistics(simData);
}


Simulator::~Simulator()
{
}


void Simulator::playChampionships()
{
	std::cout << "Starting simulation\n\n";

	statistics->resetStatistics();
	simData->getPlayer(0)->getScoreboard()->resetChampionshipsWon();
	simData->getPlayer(1)->getScoreboard()->resetChampionshipsWon();
	for (int i = 0; i < simData->getChampionshipsNumber(); i++)
	{
		playChampionship();
		statistics->recordChampionshipResult();

		int j = i + 1;
		// If no other information is being logged, just show a loading bar
		if (simData->getLogDetailLevel() == 0)
		{
			if (j % 100 == 0)
			{
				std::cout << "-";
			}
			if (j % 1000 == 0)
			{
				std::cout << " ";
			}
		}
		// Log progress every 1000 championships
		if (j % 1000 == 0)
		{
			std::cout << j;
			std::cout << " championships complete\n";
		}
	}
	std::cout << "\n";

	std::cout << "Simulation complete\n\n";
	statistics->printStatistics();
}


void Simulator::playChampionship()
{
	bool logEnabled = (simData->getLogDetailLevel() >= 1);

	if (logEnabled)
	{
		std::cout << "Starting championship\n\n";
	}

	if (simData->getStartingPlayer() == 2)
	{
		randomizeWhoThrowsFirst();
	}
	else
	{
		firstPlayer = simData->getStartingPlayer();
	}

	simData->getPlayer(0)->getScoreboard()->resetSetsWon();
	simData->getPlayer(1)->getScoreboard()->resetSetsWon();
	bool championshipHasBeenWon = false;
	while (!championshipHasBeenWon)
	{
		playSet();

		for (int i : {0, 1})
		{
			if (simData->getPlayer(i)->getScoreboard()->getSetsWon() == 7)
			{
				championshipHasBeenWon = true;
				simData->getPlayer(i)->getScoreboard()->incrementChampionshipsWon();

				if (logEnabled)
				{
					std::cout << simData->getPlayer(i)->getName();
					std::cout << " won the championship (7 : ";
					std::cout << simData->getPlayer(1 - i)->getScoreboard()->getSetsWon();
					std::cout << ")\n\n";
				}
			}
		}
	}
}


void Simulator::playSet()
{
	bool logEnabled = (simData->getLogDetailLevel() >= 2);

	if (logEnabled)
	{
		std::cout << "Starting set\n\n";
	}

	simData->getPlayer(0)->getScoreboard()->resetGamesWon();
	simData->getPlayer(1)->getScoreboard()->resetGamesWon();
	bool setHasBeenWon = false;
	while (!setHasBeenWon)
	{
		playGame();

		for (int i : {0, 1})
		{
			if (simData->getPlayer(i)->getScoreboard()->getGamesWon() == 3)
			{
				setHasBeenWon = true;
				simData->getPlayer(i)->getScoreboard()->incrementSetsWon();

				if (logEnabled)
				{
					std::cout << simData->getPlayer(i)->getName();
					std::cout << " won the set (3 : ";
					std::cout << simData->getPlayer(1 - i)->getScoreboard()->getGamesWon();
					std::cout << ")\n\n";
				}
			}
		}
	}
}


void Simulator::playGame()
{
	bool logEnabled = (simData->getLogDetailLevel() >= 3);

	if (logEnabled)
	{
		std::cout << "Starting game\n\n";
	}

	simData->getPlayer(0)->getScoreboard()->resetGameScore();
	simData->getPlayer(1)->getScoreboard()->resetGameScore();
	bool gameHasBeenWon = false;
	while (!gameHasBeenWon)
	{
		for (int i : {firstPlayer, 1 - firstPlayer})
		{
			if (!gameHasBeenWon)
			{
				simData->getPlayer(i)->takeTurn();

				if (simData->getPlayer(i)->getScoreboard()->getGameScore() == 0)
				{
					gameHasBeenWon = true;
					simData->getPlayer(i)->getScoreboard()->incrementGamesWon();
					switchWhoThrowsFirst();

					if (logEnabled)
					{
						std::cout << simData->getPlayer(i)->getName();
						std::cout << " won the game\n\n";
					}
				}
			}
		}
	}
}


void Simulator::randomizeWhoThrowsFirst()
{
	firstPlayer = rand() % 2;
}


void Simulator::switchWhoThrowsFirst()
{
	firstPlayer = 1 - firstPlayer;
}

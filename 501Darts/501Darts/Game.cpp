#include "pch.h"
#include "Game.h"

#include <iostream>


Game::Game(GameData* _gameData) : gameData(_gameData)
{
	statistics = new Statistics(gameData);
}


Game::~Game()
{
}


void Game::playChampionships()
{
	std::cout << "Starting simulation\n\n";

	statistics->resetStatistics();
	gameData->getPlayer(0)->getScoreboard()->resetChampionshipsWon();
	gameData->getPlayer(1)->getScoreboard()->resetChampionshipsWon();
	for (int i = 0; i < gameData->getChampionshipsNumber(); i++)
	{
		playChampionship();
		statistics->recordChampionshipResult();
	}

	std::cout << "Simulation complete\n\n";
	statistics->printStatistics();
}


void Game::playChampionship()
{
	bool logEnabled = (gameData->getLogDetailLevel() >= 1);

	if (logEnabled)
	{
		std::cout << "Starting championship\n\n";
	}

	if (gameData->getStartingPlayer() == 2)
	{
		randomizeWhoThrowsFirst();
	}
	else
	{
		firstPlayer = gameData->getStartingPlayer();
	}

	gameData->getPlayer(0)->getScoreboard()->resetSetsWon();
	gameData->getPlayer(1)->getScoreboard()->resetSetsWon();
	bool championshipHasBeenWon = false;
	while (!championshipHasBeenWon)
	{
		playSet();

		for (int i : {0, 1})
		{
			if (gameData->getPlayer(i)->getScoreboard()->getSetsWon() == 7)
			{
				championshipHasBeenWon = true;
				gameData->getPlayer(i)->getScoreboard()->incrementChampionshipsWon();

				if (logEnabled)
				{
					std::cout << gameData->getPlayer(i)->getName();
					std::cout << " won the championship (7 : ";
					std::cout << gameData->getPlayer(1 - i)->getScoreboard()->getSetsWon();
					std::cout << ")\n\n";
				}
			}
		}
	}
}


void Game::playSet()
{
	bool logEnabled = (gameData->getLogDetailLevel() >= 2);

	if (logEnabled)
	{
		std::cout << "Starting set\n\n";
	}

	gameData->getPlayer(0)->getScoreboard()->resetGamesWon();
	gameData->getPlayer(1)->getScoreboard()->resetGamesWon();
	bool setHasBeenWon = false;
	while (!setHasBeenWon)
	{
		playGame();

		for (int i : {0, 1})
		{
			if (gameData->getPlayer(i)->getScoreboard()->getGamesWon() == 3)
			{
				setHasBeenWon = true;
				gameData->getPlayer(i)->getScoreboard()->incrementSetsWon();

				if (logEnabled)
				{
					std::cout << gameData->getPlayer(i)->getName();
					std::cout << " won the set (3 : ";
					std::cout << gameData->getPlayer(1 - i)->getScoreboard()->getGamesWon();
					std::cout << ")\n\n";
				}
			}
		}
	}
}


void Game::playGame()
{
	bool logEnabled = (gameData->getLogDetailLevel() >= 3);

	if (logEnabled)
	{
		std::cout << "Starting game\n\n";
	}

	gameData->getPlayer(0)->getScoreboard()->resetGameScore();
	gameData->getPlayer(1)->getScoreboard()->resetGameScore();
	bool gameHasBeenWon = false;
	while (!gameHasBeenWon)
	{
		for (int i : {firstPlayer, 1 - firstPlayer})
		{
			if (!gameHasBeenWon)
			{
				gameData->getPlayer(i)->takeTurn();

				if (gameData->getPlayer(i)->getScoreboard()->getGameScore() == 0)
				{
					gameHasBeenWon = true;
					gameData->getPlayer(i)->getScoreboard()->incrementGamesWon();
					switchWhoThrowsFirst();

					if (logEnabled)
					{
						std::cout << gameData->getPlayer(i)->getName();
						std::cout << " won the game\n\n";
					}
				}
			}
		}
	}
}


void Game::randomizeWhoThrowsFirst()
{
	firstPlayer = rand() % 2;
}


void Game::switchWhoThrowsFirst()
{
	firstPlayer = 1 - firstPlayer;
}

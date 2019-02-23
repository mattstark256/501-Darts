#include "pch.h"
#include "Game.h"

#include <iostream>


Game::Game(GameData* _gameData) : gameData(_gameData)
{
}


Game::~Game()
{
}


void Game::playChampionship()
{
	gameData->getPlayer(0)->getScoreboard()->resetSetsWon();
	gameData->getPlayer(1)->getScoreboard()->resetSetsWon();
	bool championshipHasBeenWon = false;
	while (!championshipHasBeenWon)
	{
		playSet();

		for (int i : {0, 1})
		{
			if (gameData->getPlayer(i)->getScoreboard()->getSetsWon() == SETS_TO_WIN_CHAMPIONSHIP)
			{
				championshipHasBeenWon = true;
				gameData->getPlayer(i)->getScoreboard()->incrementSetsWon();
				std::cout << gameData->getPlayer(i)->getName();
				std::cout << " won the championship.\n";
			}
		}
	}
}


void Game::playSet()
{
	gameData->getPlayer(0)->getScoreboard()->resetGamesWon();
	gameData->getPlayer(1)->getScoreboard()->resetGamesWon();
	bool setHasBeenWon = false;
	while (!setHasBeenWon)
	{
		playGame();

		for (int i : {0, 1})
		{
			if (gameData->getPlayer(i)->getScoreboard()->getGamesWon() == GAMES_TO_WIN_SET)
			{
				setHasBeenWon = true;
				gameData->getPlayer(i)->getScoreboard()->incrementSetsWon();
				std::cout << gameData->getPlayer(i)->getName();
				std::cout << " won the set.\n";
			}
		}
	}
}


void Game::playGame()
{
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
					std::cout << gameData->getPlayer(i)->getName();
					std::cout << " won the game.\n";
					switchWhoThrowsFirst();
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

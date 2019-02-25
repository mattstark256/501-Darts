#include "pch.h"
#include "Statistics.h"

#include <iostream>
#include <iomanip>


Statistics::Statistics(GameData* _gameData) : gameData(_gameData)
{
}


Statistics::~Statistics()
{
}


void Statistics::resetStatistics()
{
	totalChampionships = 0;
	for (int i = 0; i < 14; i++)
	{
		scoreFrequencies[i] = 0;
	}
}

void Statistics::recordChampionshipResult()
{
	totalChampionships++;

	int player0Score = gameData->getPlayer(0)->getScoreboard()->getSetsWon();
	int player1Score = gameData->getPlayer(1)->getScoreboard()->getSetsWon();

	int arrayIndex = (player0Score == 7) ? player1Score : player0Score + 7;
	scoreFrequencies[arrayIndex]++;
}


void Statistics::printStatistics()
{
	std::cout << "STATISTICS\n\n";


	std::cout << "Total championships played: ";
	std::cout << totalChampionships;
	std::cout << std::endl;

	std::cout << "First throw at start of each championship: ";
	if (gameData->getStartingPlayer() == 2)
	{
		std::cout << "randomized";
	}
	else
	{
		std::cout << gameData->getPlayer(gameData->getStartingPlayer())->getName();
	}
	std::cout << "\n";


	for (int i : {0, 1})
	{
		std::cout << gameData->getPlayer(i)->getName();
		std::cout << " won: ";
		std::cout << gameData->getPlayer(i)->getScoreboard()->getChampionshipsWon();
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "Score frequencies";
	std::cout << std::endl;
	std::cout << gameData->getPlayer(0)->getName();
	std::cout << " : ";
	std::cout << gameData->getPlayer(1)->getName();
	std::cout << "\n";

	for (int i = 0; i < 7; i++)
	{
		printFrequency(i, 7);
	}
	for (int i = 0; i < 7; i++)
	{
		printFrequency(7, i);
	}
	std::cout << "\n";
}


void Statistics::printFrequency(int score0, int score1)
{
	std::cout << score0;
	std::cout << " : ";
	std::cout << score1;
	std::cout << "   ";
	int frequency = (score0 == 7) ? scoreFrequencies[score1] : scoreFrequencies[score0 + 7];
	float percentage = ((float)frequency / totalChampionships) * 100;
	std::cout << std::fixed;
	std::cout << std::setprecision(1);
	std::cout << percentage;
	std::cout << "%";
	std::cout << "\n";
}

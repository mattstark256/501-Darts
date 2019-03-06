#include "pch.h"
#include "Statistics.h"

#include <iostream>
#include <iomanip> // setprecision


Statistics::Statistics()
{
}


Statistics::~Statistics()
{
}


// Reset all the recorded data. This is called at the start of a simulation.
void Statistics::resetStatistics()
{
	totalChampionships = 0;
	for (int i = 0; i < 14; i++)
	{
		scoreFrequencies[i] = 0;
	}
}


// Record data from the current championship. This is called once at the end of each championship.
void Statistics::recordChampionshipResult(SimData* simData)
{
	totalChampionships++;

	int player0Score = simData->getPlayer(0)->getScoreboard()->getSetsWon();
	int player1Score = simData->getPlayer(1)->getScoreboard()->getSetsWon();

	int arrayIndex = (player0Score == 7) ? player1Score : player0Score + 7;
	scoreFrequencies[arrayIndex]++;
}


// Display all the recorded data. This is called at the end of a simulation.
void Statistics::printStatistics(SimData* simData)
{
	std::cout << "STATISTICS\n";

	std::cout << "Championships played: ";
	std::cout << totalChampionships;
	std::cout << std::endl;

	std::cout << "First throw at start of each championship: ";
	if (simData->getStartingPlayerChampionship() == 2)
	{
		std::cout << "randomized";
	}
	else
	{
		std::cout << simData->getPlayer(simData->getStartingPlayerChampionship())->getName();
	}
	std::cout << "\n";

	for (int i : {0, 1})
	{
		std::cout << simData->getPlayer(i)->getName();
		std::cout << " won: ";
		std::cout << simData->getPlayer(i)->getScoreboard()->getChampionshipsWon();
		std::cout << "\n";
	}
	std::cout << "\n";


	std::cout << "Score frequencies";
	std::cout << std::endl;
	std::cout << simData->getPlayer(0)->getName();
	std::cout << " : ";
	std::cout << simData->getPlayer(1)->getName();
	std::cout << "\n";

	for (int i = 0; i < 7; i++)
	{
		printFrequency(7, i);
	}
	for (int i = 0; i < 7; i++)
	{
		printFrequency(i, 7);
	}
	std::cout << "\n";
}


// Display one line of the frequency data. (eg "7 : 4   10.9%")
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
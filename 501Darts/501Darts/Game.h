#pragma once

#include "GameData.h"
#include "Statistics.h"


class Game
{
public:
	Game(GameData* _gameData);
	~Game();

	void playChampionships();

private:
	GameData* gameData;
	Statistics* statistics;
	int firstPlayer = 0; // This is the index that will be used with getPlayer. The value should be 0 or 1.

	void playChampionship();
	void playSet();
	void playGame();
	void randomizeWhoThrowsFirst(); // This isn't needed for task 1, because the task specifies that Sid throws first.
	void switchWhoThrowsFirst();
};


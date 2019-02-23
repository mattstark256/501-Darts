#pragma once

#include "GameData.h"
#define SETS_TO_WIN_CHAMPIONSHIP 7
#define GAMES_TO_WIN_SET 3


class Game
{
public:
	Game(GameData* _gameData);
	~Game();

	void playChampionship();

private:
	GameData* gameData;
	int firstPlayer = 0; // This is the index that will be used with getPlayer. The value should be 0 or 1.

	void playSet();
	void playGame();
	void randomizeWhoThrowsFirst(); // This isn't needed for task 1, because the task specifies that Sid throws first.
	void switchWhoThrowsFirst();
};


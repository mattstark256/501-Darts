#pragma once

#define INITIAL_GAME_SCORE 501


class Scoreboard
{
public:
	Scoreboard();
	~Scoreboard();

	int getChampionshipsWon() { return championshipsWon; }
	void resetChampionshipsWon() { championshipsWon = 0; }
	void incrementChampionshipsWon() { championshipsWon++; }
	int getSetsWon() { return setsWon; }
	void resetSetsWon() { setsWon = 0; }
	void incrementSetsWon() { setsWon++; }
	int getGamesWon() { return gamesWon; }
	void resetGamesWon() { gamesWon = 0; }
	void incrementGamesWon() { gamesWon++; }
	int getGameScore() { return gameScore; }
	void resetGameScore() { gameScore = INITIAL_GAME_SCORE; }
	void decreaseGameScore(int amount) { gameScore -= amount; }

private:
	int championshipsWon = 0;
	int setsWon = 0;
	int gamesWon = 0;
	int	gameScore = INITIAL_GAME_SCORE;
};


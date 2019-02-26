#pragma once

#include "Dartboard.h"
#include "Scoreboard.h"
#include "Player.h"


// This class contains the main properties of the simulation, such as who is playing and what dartboard they are using.
// Keeping it all in one object makes it easy for other objects to access necessary information. For example, a player can find out who their opponent is.
class SimData
{
public:
	SimData();
	~SimData();

	Dartboard* getDartboard() { return dartboard; }
	void setDartboard(Dartboard* _dartboard) { dartboard = _dartboard; }

	Player* getPlayer(int index) { return players[index]; }
	void setPlayer(int index, Player* player) { players[index] = player; }
	int getPlayerIndex(Player* player) { return (player == players[0]) ? 0 : 1; }
	Player* getOtherPlayer(Player* player) { return (player == players[0]) ? players[1] : players[0]; }

	int getChampionshipsNumber() { return championshipsNumber; }
	void setChampionshipsNumber(int _championshipsNumber) { championshipsNumber = _championshipsNumber; }

	int getLogDetailLevel() { return logDetailLevel; }
	void setLogDetailLevel(int _logDetailLevel) { logDetailLevel = _logDetailLevel; }

	int getStartingPlayer() { return startingPlayer; }
	void setStartingPlayer(int _startingPlayer) { startingPlayer = _startingPlayer; }

private:
	Dartboard *dartboard;
	Player* players[2];
	int championshipsNumber = 1;

	// Log Detail Level
	// 0 - per simulation
	// 1 - per championship
	// 2 - per set
	// 3 - per game
	// 4 - per turn
	int logDetailLevel = 1;

	// 0 or 1 - one player always starts championships first
	// 2 - it's randomized
	int startingPlayer = 0;
};


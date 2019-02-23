#pragma once

#include "Dartboard.h"
#include "Scoreboard.h"
#include "Player.h"


class GameData
{
public:
	GameData();
	~GameData();

	Dartboard* getDartboard() { return dartboard; }
	void setDartboard(Dartboard* _dartboard) { dartboard = _dartboard; }
	Player* getPlayer(int index) { return players[index]; }
	void setPlayer(int index, Player* player) { players[index] = player; }
	int getPlayerIndex(Player* player) { return (player == players[0]) ? 0 : 1; }
	Player* getOtherPlayer(Player* player) { return (player == players[0]) ? players[1] : players[0]; }

private:
	Dartboard *dartboard;
	Player* players[2];
};


#pragma once
#include "Dartboard.h"

#define SECTOR_COUNT 20


// This is used for positions on the board
struct Vector2
{
	float x, y;
	Vector2() {}
	Vector2(float newX, float newY) : x(newX), y(newY) {}
	Vector2 addVector(Vector2 v) { return Vector2(x + v.x, y + v.y); }
};


// This dartboard uses vectors to simulate accuracy based on skill level.
class DartboardVector :
	public Dartboard
{
public:
	DartboardVector();
	~DartboardVector();

	ThrowResult throwDart(int section, int multiplier, int skillLevel);

private:
	int sectorValues[SECTOR_COUNT]{ 20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5 };

	// Rather than calculating where to aim every time the player throws a dart, I calculate all target positions at the start and store them.
	// This reduces the amount of trigonometry per throw.
	// Array indexes start from 0 but dartboard multipliers and sections start from 1, so I convert between them.
	Vector2 aimPositions[3][20]; 

	Vector2 getAimPosition(int section, int multiplier);
	Vector2 getOffsetPosition(int skill);
	ThrowResult getThrowResult(Vector2 position);
	void generateAimPositions();
};


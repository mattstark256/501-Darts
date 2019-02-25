#pragma once


struct ThrowResult
{
	ThrowResult(int _score, int _multiplier) : multipliedScore(_score), multiplier(_multiplier) {}
	int multipliedScore; // This is the score AFTER multiplication.
	int multiplier; // This is used for checking whether a player ended on a double.
};

class Dartboard
{
public:
	Dartboard();
	~Dartboard();

	virtual ThrowResult throwDart(int section, int multiplier, int skillLevel);
};


#pragma once

#include <string>


// This struct is used because the dartboard functions need to return both a score and a multiplier.
struct ThrowResult
{
	ThrowResult(int _score, int _multiplier) : multipliedScore(_score), multiplier(_multiplier) {}
	int multipliedScore; // This is the score AFTER multiplication.
	int multiplier; // This is used for checking whether a player ended on a double.
};


// This is the base class for dartboards.
class Dartboard
{
public:
	Dartboard();
	~Dartboard();

	virtual ThrowResult throwDart(int section, int multiplier, int skillLevel);
	std::string getDartboardType() { return dartboardType; }

protected:
	std::string dartboardType = "Base class"; // Each dartboard class sets this to a different value
};


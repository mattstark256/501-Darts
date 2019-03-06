#include "pch.h"
#include "Dartboard.h"


Dartboard::Dartboard()
{
}


Dartboard::~Dartboard()
{
}


// throwDart is a virtual function which is overridden in the other Dartboard classes.
ThrowResult Dartboard::throwDart(int section, int multiplier, int skillLevel)
{
	return ThrowResult(section * multiplier, multiplier);
}
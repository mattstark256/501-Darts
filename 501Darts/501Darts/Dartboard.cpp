#include "pch.h"
#include "Dartboard.h"

#include <stdlib.h> // rand


Dartboard::Dartboard()
{
}


Dartboard::~Dartboard()
{
}


ThrowResult Dartboard::throwDart(int section, int multiplier, int skillLevel) {
	return ThrowResult(section * multiplier, multiplier);
}
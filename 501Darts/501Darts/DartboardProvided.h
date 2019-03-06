#pragma once
#include "Dartboard.h"


// This dartboard uses the functions that were provided as part of the brief.
class DartboardProvided :
	public Dartboard
{
public:
	DartboardProvided();
	~DartboardProvided();

	ThrowResult throwDart(int section, int multiplier, int skillLevel);

private:
	int throw_bull(int p);
	int throw_treble(int d, int p);
	int throw_double(int d);
	int throw_single(int d);
};


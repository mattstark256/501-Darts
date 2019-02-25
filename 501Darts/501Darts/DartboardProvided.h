#pragma once
#include "Dartboard.h"
class DartboardProvided :
	public Dartboard
{
public:
	DartboardProvided();
	~DartboardProvided();

	ThrowResult throwDart(int section, int multiplier, int skillLevel);

	int throw_bull(int p);
	int throw_treble(int d, int p);
	int throw_double(int d);
	int throw_single(int d);
};


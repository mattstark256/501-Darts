#include "pch.h"
#include "DartboardProvided.h"

#include <stdlib.h> // rand


DartboardProvided::DartboardProvided()
{
	dartboardType = "Default";
}


DartboardProvided::~DartboardProvided()
{
}


// I chose to leave the provided functions unmodified and to use throwDart as an interface for them. The provided functions don't return a multiplier, so it guesses based on the returned score.
ThrowResult DartboardProvided::throwDart(int section, int multiplier, int skillLevel)
{
	if (section == 50)
	{
		return ThrowResult(throw_bull(skillLevel), 1);
	}
	else if (multiplier == 3)
	{
		int score = throw_treble(section, skillLevel);
		int multiplier = (score == section * 3) ? 3 : 1;
		return ThrowResult(score, multiplier);
	}
	else if (multiplier == 2)
	{
		int score = throw_double(section);
		int multiplier = (score == section * 2) ? 2 : 1;
		return ThrowResult(score, multiplier);
	}
	else
	{
		return ThrowResult(throw_single(section), 1);
	}
}



// ------------------
// PROVIDED FUNCTIONS
// ------------------

int DartboardProvided::throw_bull(int p) {

	//  Throw for the bull with accuracy p%  (20<p<85)

	int r = rand() % 100;

	if (r < (p - 20))
		return 50;
	else if (r < 85)
		return 25;
	else
		return 1 + rand() % 20;
}


int DartboardProvided::throw_treble(int d, int p) {

	//  return result of throwing for treble d with accuracy p%  (o<90)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

	int r = rand() % 100;

	if (r < p)
		return 3 * d;
	else if (r < 90)
		return d;
	else if (r < 93)
		return 3 * bd[0][d];
	else if (r < 96)
		return 3 * bd[1][d];
	else if (r < 98)
		return bd[0][d];
	else
		return bd[1][d];
}


int DartboardProvided::throw_double(int d) {

	//  return result of throwing for double d with accuracy 80%

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100;

	if (r < 80)
		return 2 * d;
	else if (r < 85)
		return 0;
	else if (r < 90)
		return d;
	else if (r < 93)
		return 2 * bd[0][d];
	else if (r < 96)
		return 2 * bd[1][d];
	else if (r < 98)
		return bd[0][d];
	else
		return bd[1][d];
}



int DartboardProvided::throw_single(int d) {

	//  return result of throwing for single d with accuracy 88% (or 80% for the outer)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100;

	if (d == 25) {		// outer  80%
		if (r < 80)
			return 25;
		else if (r < 90)
			return 50;
		else
			return 1 + rand() % 20;
	}
	else			// 1 to 20 single
		if (r < 88)
			return d;
		else if (r < 92)
			return bd[0][d];
		else if (r < 96)
			return bd[1][d];
		else if (r < 98)
			return 3 * d;
		else
			return 2 * d;
}
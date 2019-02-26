#include "pch.h"
#include "DartboardVector.h"

#include <cmath>
#include <cstdlib>  // rand
#include <iostream>
using namespace std;

// Measurements are in mm, using specifications from https://www.reddragondarts.com/info/dartboard-specification/
#define BOARD_RADIUS 170.f
#define DOUBLE_INNER_RADIUS 160.f
#define TRIPLE_OUTER_RADIUS 107.4f
#define TRIPLE_INNER_RADIUS 97.4f
#define BULL_OUTER_RADIUS 15.875f
#define BULL_INNER_RADIUS 6.35f

// The players aim at the centre of their target
#define SINGLE_AIM_RADIUS 135.f
#define DOUBLE_AIM_RADIUS 165.f
#define TRIPLE_AIM_RADIUS 102.4f

#define SECTOR_INDEX_TO_RADIANS 0.314159265f
#define TWO_PI 6.283185307f


DartboardVector::DartboardVector()
{
	dartboardType = "Vector";

	generateAimPositions();
}


DartboardVector::~DartboardVector()
{
}


ThrowResult DartboardVector::throwDart(int section, int multiplier, int skillLevel)
{
	return getThrowResult(getAimPosition(section, multiplier).addVector(getOffsetPosition(skillLevel)));
}


// Get the ideal position to aim at for a particular score
Vector2 DartboardVector::getAimPosition(int section, int multiplier)
{
	if (section == 50)
	{
		// It's a bullseye
		return Vector2(0, 0);
	}
	else
	{
		// It's a 1-20 section
		return aimPositions[multiplier - 1][section - 1];
	}
}


// Return a random vector that is used to offset the hit position
// This simulates accuracy being affected by skill level
Vector2 DartboardVector::getOffsetPosition(int skill)
{
	// The distribution is such that aiming at the bull has a (skill)% chance of hitting.
	float bullHitChance = (float)skill / 100;
	float maxOffsetRadius = BULL_INNER_RADIUS / bullHitChance;

	// Generate a random number between 0 and 1
	float random01 = (double)rand() / RAND_MAX;
	// Pick a radius from 0 to maxOffsetRadius
	float offsetRadius = maxOffsetRadius * random01;

	// Generate a random number between 0 and 1
	random01 = (double)rand() / RAND_MAX;
	// Pick an angle from 0 to two pi
	float offsetAngle = TWO_PI * random01;

	return Vector2(offsetRadius * sin(offsetAngle), offsetRadius * cos(offsetAngle));
}


// Get the result of a dart hitting a position
ThrowResult DartboardVector::getThrowResult(Vector2 position)
{
	// Find the radius of the hit position
	float radius = pow(pow(position.x, 2) + pow(position.y, 2), 0.5);

	if (radius < BULL_INNER_RADIUS)
	{
		// The player hit the bullseye
		return ThrowResult(50, 1);
	}
	else if (radius < BULL_OUTER_RADIUS)
	{
		// The player hit the outer bullseye
		return ThrowResult(25, 1);
	}
	else if (radius > BOARD_RADIUS)
	{
		// The player missed the board
		return ThrowResult(0, 1);
	}
	else
	{
		// The player hit one of the 1-20 sections

		// Find the angle of the hit position
		float angle = atan2(position.x, position.y);
		int sectorIndex = round(angle / SECTOR_INDEX_TO_RADIANS);
		sectorIndex = (sectorIndex + 20) % 20;
		int sectorValue = sectorValues[sectorIndex];

		if (radius > TRIPLE_INNER_RADIUS && radius < TRIPLE_OUTER_RADIUS)
		{
			return ThrowResult(sectorValue * 3, 3);
		}
		else if (radius > DOUBLE_INNER_RADIUS)
		{
			return ThrowResult(sectorValue * 2, 2);
		}
		else
		{
			return ThrowResult(sectorValue, 1);
		}
	}
}


// Store the position to aim at for each multiplier and sector
void DartboardVector::generateAimPositions()
{
	for (int multiplier = 1; multiplier < 4; multiplier++)
	{
		for (int sector = 1; sector < 21; sector++)
		{
			// Find the sector's index (0-19 clockwise with 0 at the top)
			int sectorIndex = 0;
			for (int i = 0; i < SECTOR_COUNT; i++)
			{
				if (sectorValues[i] == sector) { sectorIndex = i; }
			}

			// Find the angle of the sector in radians
			float sectorAngle = sectorIndex * SECTOR_INDEX_TO_RADIANS;

			// Find the radius from the multiplier
			float radius = 0;
			switch (multiplier)
			{
			case 1: radius = SINGLE_AIM_RADIUS; break;
			case 2: radius = DOUBLE_AIM_RADIUS; break;
			case 3: radius = TRIPLE_AIM_RADIUS; break;
			}

			// Use the radius and angle to find the position they should aim at
			Vector2 aimPosition = Vector2(radius * sin(sectorAngle), radius * cos(sectorAngle));

			aimPositions[multiplier - 1][sector - 1] = aimPosition;
		}
	}
}

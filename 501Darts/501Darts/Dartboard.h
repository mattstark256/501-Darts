#pragma once


class Dartboard
{
public:
	Dartboard();
	~Dartboard();

	int throw_bull(int p);
	int throw_treble(int d, int p);
	int throw_double(int d);
	int throw_single(int d);
};


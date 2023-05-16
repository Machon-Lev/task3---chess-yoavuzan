#pragma once
#include "Peice.h"
class Queen: public Peice
{
public:
	Queen(Color color) :Peice(color) {};
	char GetPeice();
};


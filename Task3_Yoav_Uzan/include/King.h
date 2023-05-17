#pragma once
#include "Peice.h"

class King : public Peice
{
public:
	King(Color color) :Peice(color) {};
	char GetPeice();
};
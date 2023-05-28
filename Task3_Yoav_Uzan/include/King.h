#pragma once
#include "Peice.h"

class King : public Peice
{
public:
	King(Color color,Board* board) :Peice(color, board) {};
	bool checkMoveForKing(Loction place, Loction destination);
	char GetPeice();
};
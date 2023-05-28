#pragma once
#include "Peice.h"

class Pawn: public Peice
{
public:
	Pawn(Color color,Board* board) :Peice(color,board) {};
	bool checkMoveForPawn(Loction place, Loction destination);
	// check if the position is legal for pawn
	char GetPeice() override;
};


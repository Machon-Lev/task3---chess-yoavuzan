#pragma once
#include "Peice.h"

class Pawn: public Peice
{
public:
	Pawn(Color color,Board* board) :Peice(color,board) {};
	bool checkMoveForPawn(int placex, int placey, int destinationx, int destinationy);
	// check if the position is legal for pawn
	char GetPeice() override;
};


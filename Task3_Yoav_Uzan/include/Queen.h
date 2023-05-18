#pragma once
#include "Peice.h"
#include "Rook.h"
#include "Bishop.h"

class Queen: public Peice
{
public:
	Queen(Color color,Board* board ) :Peice(color, board) {};
	bool checkMoveForQueen(int placex, int placey,int destinationx, int destinationy);
	char GetPeice();
};


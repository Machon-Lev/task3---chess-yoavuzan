#pragma once
#include "Peice.h"

class King : public Peice
{
public:
	King(Color color,Board* board) :Peice(color, board) {};
	bool checkMoveForKing(int placex, int placey, int destinationx, int destinationy);
	char GetPeice();
};
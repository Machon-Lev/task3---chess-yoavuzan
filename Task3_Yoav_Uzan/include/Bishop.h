#pragma once
#include "Peice.h"
class Bishop: public Peice 
{
public:
	Bishop(Color color,Board* board) :Peice(color, board) {};
	char GetPeice();
	bool checkMoveForBishop(int placex, int placey, int destinationx, int destinationy);
	
};
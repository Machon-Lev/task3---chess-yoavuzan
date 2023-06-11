#pragma once
#include "Peice.h"
#include<vector>
using std::vector;

class Rook : public Peice
{
public:
	bool checkMoveForRook(int placex, int placey, int destinationx, int destinationy);
	// check if the position is legal for rook
	Rook(Color type,Board* board1):Peice(type, board1){}
	 char  GetPeice() override;

};
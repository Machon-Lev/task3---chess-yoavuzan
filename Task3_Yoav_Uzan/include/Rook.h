#pragma once
#include "Peice.h"
#include<vector>
using std::vector;

class Rook : public Peice
{
public:
	bool checkMoveForRook(Loction place, Loction destination);
	// check if the position is legal for rook
	Rook(Color type,Board* board1):Peice(type, board1){}
	 char  GetPeice() override;

};
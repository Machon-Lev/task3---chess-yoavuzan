#pragma once
#include "Loction.h"
#include "Color.h"
#include "Board.h"
class Board;
class Peice
{
private:
	Color color;
public:
	Board* p_board = nullptr;
	Peice(Color col,Board* board1);
	Color GetColor(){ return color;}
	virtual char GetPeice() { return 'E';};

};

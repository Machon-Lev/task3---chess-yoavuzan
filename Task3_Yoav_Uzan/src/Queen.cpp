#include "Queen.h"
char Queen::GetPeice()
{
	if (GetColor() == Color::White)
		return 'Q';
	else
		return 'q';
}

bool Queen::checkMoveForQueen(Loction place, Loction destination)
{
	Rook r(GetColor(), p_board);
	if (!r.checkMoveForRook(place, destination))
		return false;
	Bishop b(GetColor(), p_board);
	if(!b.checkMoveForBishop(place, destination))
		return false;
	return true;
}
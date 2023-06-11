#include "Queen.h"
char Queen::GetPeice()
{
	if (GetColor() == Color::White)
		return 'Q';
	else
		return 'q';
}

bool Queen::checkMoveForQueen(int placex, int placey, int destinationx, int destinationy)
{
	Rook r(GetColor(), p_board);
	if (!r.checkMoveForRook(placex, placey, destinationx, destinationy))
		return false;
	Bishop b(GetColor(), p_board);
	if(!b.checkMoveForBishop(placex, placey, destinationx, destinationy))
		return false;
	return true;
}
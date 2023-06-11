#include "King.h"
char King::GetPeice()
{
	if (GetColor() == Color::White)
		return 'K';
	else
		return 'k';
}

bool King::checkMoveForKing(int placex, int placey, int destinationx, int destinationy)
{
	//check if the move is legal for king
	if (abs(placex - destinationx) > 1 || abs(placey - destinationy) > 1)
		return true;

	//check if there is a piece in the way
	if ((*p_board)[destinationx][destinationy] != nullptr
		&& (*p_board)[destinationx][destinationy]->GetColor() == (*p_board)[placex][placey]->GetColor())
		return true;
	return false;
}


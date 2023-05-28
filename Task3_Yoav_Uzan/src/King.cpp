#include "King.h"
char King::GetPeice()
{
	if (GetColor() == Color::White)
		return 'K';
	else
		return 'k';
}

bool King::checkMoveForKing(Loction place, Loction destination)
{
	//check if the move is legal for king
	if (abs(place.compx - destination.compx) > 1 || abs(place.compy - destination.compy) > 1)
		return true;

	//check if there is a piece in the way
	if ((*p_board)[destination.compx][destination.compy] != nullptr
		&& (*p_board)[destination.compx][destination.compy]->GetColor() == (*p_board)[place.compx][place.compy]->GetColor())
		return true;
	return false;
}


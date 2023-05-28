#include "Pawn.h"
char Pawn::GetPeice()
{
	if (GetColor() == Color::White)
		return 'P';
	else
		return 'p';
}
bool Pawn::checkMoveForPawn(Loction place,Loction destination) {
	//check if the move is legal for pawn
	if ((*p_board)[place.compx][place.compy]->GetColor() == Color::White)
	{
		if (place.compx == 1)
		{
			if (destination.compx - place.compx > 2 || destination.compx - place.compx < 1)
				return true;
		}
		else
		{
			if (destination.compx - place.compx > 1 || destination.compx - place.compx < 1)
				return true;
		}
	}
	else
	{
		if (place.compx == 6)
		{
			if (place.compx - destination.compx > 2 || place.compx - destination.compx < 1)
				return true;
		}
		else
		{
			if (place.compx - destination.compx > 1 || place.compx - destination.compx < 1)
				return true;
		}
	}
	if (abs(place.compy - destination.compy) > 1)
		return true;
	
	//check if there is a piece in the way
	if ((*p_board)[destination.compx][destination.compy] != nullptr)
	{
		if (place.compy == destination.compy)
			return true;
	}
	if ((*p_board)[destination.compx][destination.compy] == nullptr)
		if (abs(place.compy - destination.compy) == 1)
			return true;
	return false;
}
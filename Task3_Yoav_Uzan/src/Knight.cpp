#include "Knight.h"

char Knight::GetPeice() {
	if (GetColor() == Color::White)
		return 'N';
	else
		return 'n';
}

bool Knight::checkMoveForKnight(Loction place, Loction destination)
{
	//check if the move is legal for knight
	if (abs(place.compx - destination.compx) == 2 && abs(place.compy - destination.compy) == 1)
		return false;
	if (abs(place.compx - destination.compx) == 1 && abs(place.compy - destination.compy) == 2)
		return false;
	return true;
}

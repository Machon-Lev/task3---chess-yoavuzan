#include "Knight.h"

char Knight::GetPeice() {
	if (GetColor() == Color::White)
		return 'N';
	else
		return 'n';
}

bool Knight::checkMoveForKnight(int placex, int placey, int destinationx, int destinationy)
{
	//check if the move is legal for knight
	if (abs(placex - destinationx) == 2 && abs(placey - destinationy) == 1)
		return false;
	if (abs(placex - destinationx) == 1 && abs(placey - destinationy) == 2)
		return false;
	return true;
}

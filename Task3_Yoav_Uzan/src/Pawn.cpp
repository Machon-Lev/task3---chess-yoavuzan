#include "Pawn.h"
char Pawn::GetPeice()
{
	if (GetColor() == Color::White)
		return 'P';
	else
		return 'p';
}
bool Pawn::checkMoveForPawn(int placex, int placey, int destinationx, int destinationy) {
	//check if the move is legal for pawn
	if ((*p_board)[placex][placey]->GetColor() == Color::White)
	{
		if (placex == 1)
		{
			if (destinationx - placex > 2 || destinationx - placex < 1)
				return true;
		}
		else
		{
			if (destinationx - placex > 1 || destinationx - placex < 1)
				return true;
		}
	}
	else
	{
		if (placex == 6)
		{
			if (placex - destinationx > 2 || placex - destinationx < 1)
				return true;
		}
		else
		{
			if (placex - destinationx > 1 || placex - destinationx < 1)
				return true;
		}
	}
	if (abs(placey - destinationy) > 1)
		return true;
	
	//check if there is a piece in the way
	if ((*p_board)[destinationx][destinationy] != nullptr)
	{
		if (placey == destinationy)
			return true;
	}
	if ((*p_board)[destinationx][destinationy] == nullptr)
		if (abs(placey - destinationy) == 1)
			return true;
	return false;
}
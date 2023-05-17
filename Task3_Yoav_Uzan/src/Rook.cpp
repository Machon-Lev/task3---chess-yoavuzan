#include "Rook.h"

 char Rook:: GetPeice() 
{
	if (GetColor() == Color::White)
		return 'R';
	else
		return 'r';
}
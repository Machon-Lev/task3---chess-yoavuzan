#include "King.h"
char King::GetPeice()
{
	if (GetColor() == Color::White)
		return 'K';
	else
		return 'k';
}


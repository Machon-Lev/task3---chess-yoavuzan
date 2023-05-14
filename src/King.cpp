#include "King.h"
int King::Move(Loction loc)
{
	return 0;
}

char King::GetPeice()
{
	if (GetColor() == Color::White)
		return 'K';
	else
		return 'k';
}
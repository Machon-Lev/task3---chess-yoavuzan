#include "Bishop.h"
char Bishop::GetPeice()
{
	if (GetColor() == Color::White)
		return 'B';
	else
		return 'b';
}
#include "Queen.h"
char Queen::GetPeice()
{
	if (GetColor() == Color::White)
		return 'Q';
	else
		return 'q';
}
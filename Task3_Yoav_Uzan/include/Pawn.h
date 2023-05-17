#pragma once
#include "Peice.h"

class Pawn: public Peice
{
public:
	Pawn(Color color) :Peice(color) {};
	char GetPeice() override;
};

char Pawn::GetPeice()
{
	if (GetColor() == Color::White)
		return 'P';
	else
		return 'p';
}
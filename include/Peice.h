#pragma once
#include "Loction.h"
#include "Color.h"

class Peice
{
private:
	Color color;
public:
	Peice(Color color);
	Color GetColor(){ return color;}
	virtual char GetPeice() = 0;

};

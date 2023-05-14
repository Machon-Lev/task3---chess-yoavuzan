#pragma once
#include "Peice.h"
#include <vector>
using std::vector;

class King : public Peice
{
	private:
	vector <Loction> aviableMoves;
public:
	King(Color color) : Peice(color) {};
	int Move(Loction loc);
	char GetPeice();

};
#pragma once
#include "Peice.h"
#include<vector>
using std::vector;

class Rook : public Peice
{
private:
	bool isAlive = true;
public:
	Rook(Color type):Peice(type){}
	 char  GetPeice() override;

};
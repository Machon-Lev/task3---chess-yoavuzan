#pragma once
#include "Peice.h"
class Bishop: public Peice 
{
public:
	Bishop(Color color) :Peice(color) {};
	char GetPeice();
};
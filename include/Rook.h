
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

=======
#include Peices.h
class Rook : public Peices
{
private:
	bool isAlive = true;
public:
	Rook(Color type):Peices(type);
	bool move(int x, int y);
};
#include "Peice.h"
class Knight: public Peice
{
public:
	Knight(Color color,Board* board) :Peice(color, board) {};
	char GetPeice();
	bool checkMoveForKnight(Loction place, Loction destination);
	// check if the position is legal for knight

};


#include "Peice.h"
class Knight: public Peice
{
public:
	Knight(Color color,Board* board) :Peice(color, board) {};
	char GetPeice();
	bool checkMoveForKnight(int placex, int placey, int destinationx, int destinationy);
	// check if the position is legal for knight

};


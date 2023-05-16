#include "Peice.h"
class Knight: public Peice
{
public:
	Knight(Color color) :Peice(color) {};
	char GetPeice();

};

char Knight::GetPeice() {
	if (GetColor() == Color::White)
		return 'N';
	else
		return 'n';
}
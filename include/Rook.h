#include "Peice.h"
class Rook : public Peice
{
private:
	bool isAlive = true;
	vector<Loction> aviableMoves;
	
public:
	Rook(Color type):Peice(type){}
	bool move(int x, int y);

};
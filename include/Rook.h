#include Peices.h
class Rook : public Peices
{
private:
	bool isAlive = true;
public:
	Rook(Color type):Peices(type);
	bool move(int x, int y);

};
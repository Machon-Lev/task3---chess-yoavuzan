#pragma once
class Board;
class Peice
{
public:
	Board board();
	enum class Color { White = 1, Black };
	Peice(Color color);
	Color GetColor(){ return color;}
	char GetPeice()=0;
	void move(int x, int y) = 0;
	getAviableMoves() = 0;
private:
		Color color;

};

Peices::Peices(Color col)
{
	color=col
}

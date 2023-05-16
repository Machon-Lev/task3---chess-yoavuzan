#pragma once

class Peices
{
public:
	enum class Color { White = 1, Black };
	Peices(Color color);
	
	GetPeice()=0;
	
private:
		Color color;

};

Peices::Peices(Color col)
{
	color=col
}

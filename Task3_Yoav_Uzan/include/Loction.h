#pragma once
#include <iostream>
struct Loction
{
	char x = ' ';//uemen loction
	int y = -1; //uemen loction
	int compx= -1;//computer position x
	int compy=-1;//computer position y
	Loction(char x= ' ', int y= -1)
	{
		if (checkLoction(x, y))
		{
		this->x = x;
		this->y = y;
		this->compx = static_cast<int>(x - 'a');
		this->compy = y - 1;
		}
		else
			throw std::invalid_argument("Invalid location");
	}

	bool checkLoction(char x, int y)
	{
		return (x >= 'a' && x <= 'h' && y >= 1 && y <= 8) || (x==' ' && y==-1);
	}

	bool isEmpty()
	{
		return x == ' ' && y == -1 ;
	}

	bool operator == (const Loction& other) const
	{
		return x == other.x && y == other.y;
	}	
	bool operator !=(const Loction& other) const
	{
		return !(*this == other);
	}	
	bool operator >(const Loction& other) const
	{
		return x > other.x && y > other.y;
	}
	bool operator <(const Loction& other) const
	{
		return x < other.x && y < other.y;
	}
	bool operator >=(const Loction& other) const
	{
		return !(*this < other);
	}
	bool operator <=(const Loction& other) const
	{
		return !(*this > other);
	}
	Loction operator +(const Loction& other) const
	{
		return Loction(x + other.x, y + other.y);
	}
	Loction operator -(const Loction& other) const
	{
		return Loction(x - other.x, y - other.y);
	}

};
struct Loction
{
	char x = ' ';
	int y = -1;
	Loction(char x, int y) : 
	{
		if (checkLoction(x, y))
		{
		this->x = x;
		this->y = y;
		}
	}

	bool checkLoction(char x, int y)
	{
		return x >= 'A' && x <= 'H' && y >= 1 && y <= 8;
	}

	bool isEmpty()
	{
		return x == ' ' && y == -1;
	}

	operator ==(const Loction& other) const
	{
		return x == other.x && y == other.y;
	}	
	operator !=(const Loction& other) const
	{
		return !(*this == other);
	}	
	operator >(const Loction& other) const
	{
		return x > other.x && y > other.y;
	}
	operator <(const Loction& other) const
	{
		return x < other.x && y < other.y;
	}
	operator >=(const Loction& other) const
	{
		return !(*this < other);
	}
	operator <=(const Loction& other) const
	{
		return !(*this > other);
	}
	operator +(const Loction& other) const
	{
		return Loction(x + other.x, y + other.y);
	}
	operator -(const Loction& other) const
	{
		return Loction(x - other.x, y - other.y);
	}
	operator +=(const Loction& other) const
	{
		return *this = *this + other;
	}
};
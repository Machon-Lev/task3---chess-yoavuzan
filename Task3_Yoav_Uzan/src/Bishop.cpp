#include "Bishop.h"
char Bishop::GetPeice()
{
	if (GetColor() == Color::White)
		return 'B';
	else
		return 'b';
}
bool Bishop::checkMoveForBishop(Loction place, Loction destination)
{
	//check if the move is legal for bishop
	if (abs(place.compx - destination.compx) != abs(place.compy - destination.compy))
		return true;
	//check if there is a piece in the way
	if (place.compx > destination.compx)
	{
		if (place.compy > destination.compy)
		{
			int startx = place.compx - 1;
			int starty = place.compy - 1;
			for (int i = startx, j = starty; i > destination.compx && j > destination.compy; i--, j--)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
		else
		{
			int startx = place.compx - 1;
			int starty = place.compy + 1;
			for (int i = startx, j = starty; i > destination.compx && j < destination.compy; i--, j++)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
	}
	else
	{
		if (place.compy > destination.compy)
		{
			int startx = place.compx + 1;
			int starty = place.compy - 1;
			for (int i = startx, j = starty; i < destination.compx && j > destination.compy; i++, j--)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
		else
		{
			int startx = place.compx + 1;
			int starty = place.compy + 1;
			for (int i = startx, j = starty; i < destination.compx && j < destination.compy; i++, j++)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
	}
	return false;
}

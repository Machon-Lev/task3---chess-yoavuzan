#include "Bishop.h"
char Bishop::GetPeice()
{
	if (GetColor() == Color::White)
		return 'B';
	else
		return 'b';
}
bool Bishop::checkMoveForBishop(int placex, int placey, int destinationx, int destinationy)
{
	//check if the move is legal for bishop
	if (abs(placex - destinationx) != abs(placey - destinationy))
		return true;
	//check if there is a piece in the way
	if (placex > destinationx)
	{
		if (placey > destinationy)
		{
			int startx = placex - 1;
			int starty = placey - 1;
			for (int i = startx, j = starty; i > destinationx && j > destinationy; i--, j--)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
		else
		{
			int startx = placex - 1;
			int starty = placey + 1;
			for (int i = startx, j = starty; i > destinationx && j < destinationy; i--, j++)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
	}
	else
	{
		if (placey > destinationy)
		{
			int startx = placex + 1;
			int starty = placey - 1;
			for (int i = startx, j = starty; i < destinationx && j > destinationy; i++, j--)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
		else
		{
			int startx = placex + 1;
			int starty = placey + 1;
			for (int i = startx, j = starty; i < destinationx && j < destinationy; i++, j++)
			{
				if ((*p_board)[i][j] != nullptr)
					return true;
			}
		}
	}
	return false;
}

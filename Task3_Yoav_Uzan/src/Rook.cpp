#include "Rook.h"

 char Rook:: GetPeice() 
{
	if (GetColor() == Color::White)
		return 'R';
	else
		return 'r';
}
 bool Rook::checkMoveForRook(int placex, int placey, int destinationx, int destinationy)
 {
	 //check if the move is legal for rook
	 if (placex != destinationx && placey != destinationy)
		 return true;
	 //check if there is a piece in the way
	 if (placex == destinationx)
	 {
		 //check if there is a piece in the way for the y axis
		 if (placey > destinationy)
		 {
			 int start = placey - 1;
			 for (int i = start; i > destinationy; i--)
			 {
				 if ((*p_board)[placex][i] != nullptr)
					 return true;
			 }
		 }
		 else
		 {
			 int start = placey + 1;
			 for (int i = start; i < destinationy; i++)
			 {
				 if ((*p_board)[placex][i] != nullptr)
					 return true;
			 }
		 }
	 }
	 else
	 {
		 //check if there is a piece in the way for the x axis
		 if (placex > destinationx)
		 {
			 int start = placex - 1;
			 for (int i = start; i > destinationx; i--)
			 {
				 if ((*p_board)[i][placey] != nullptr)
					 return true;
			 }
		 }
		 else
		 {
			 int start = placex + 1;
			 for (int i = start; i < destinationx; i++)
			 {
				 if ((*p_board)[i][placey] != nullptr)
					 return true;
			 }
		 }
	 }
	 return false;
 }
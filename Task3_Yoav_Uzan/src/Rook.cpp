#include "Rook.h"

 char Rook:: GetPeice() 
{
	if (GetColor() == Color::White)
		return 'R';
	else
		return 'r';
}
 bool Rook::checkMoveForRook(Loction place, Loction destination)
 {
	 //check if the move is legal for rook
	 if (place.compx  != destination.compx && place.compy != destination.compy)
		 return true;
	 //check if there is a piece in the way
	 if (place.compx == destination.compx)
	 {
		 //check if there is a piece in the way for the y axis
		 if (place.compy > destination.compy)
		 {
			 int start = place.compy - 1;
			 for (int i = start; i > destination.compy; i--)
			 {
				 if ((*p_board)[place.compx][i] != nullptr)
					 return true;
			 }
		 }
		 else
		 {
			 int start = place.compy + 1;
			 for (int i = start; i < destination.compy; i++)
			 {
				 if ((*p_board)[place.compx][i] != nullptr)
					 return true;
			 }
		 }
	 }
	 else
	 {
		 //check if there is a piece in the way for the x axis
		 if (place.compx > destination.compx)
		 {
			 int start = place.compx - 1;
			 for (int i = start; i > destination.compx; i--)
			 {
				 if ((*p_board)[i][place.compy] != nullptr)
					 return true;
			 }
		 }
		 else
		 {
			 int start = place.compx + 1;
			 for (int i = start; i < destination.compx; i++)
			 {
				 if ((*p_board)[i][place.compy] != nullptr)
					 return true;
			 }
		 }
	 }
	 return false;
 }
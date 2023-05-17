#include "Board.h"
#include "Peice.h"
#include "Rook.h"
#include "King.h"
#include"Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
#include "Loction.h"
#include "Color.h"
#include <iostream>
#include <string>
#include <vector>
using std::vector;

//get responce to the order
int Board::getResponse(string order)
{	
	try
	{
		Loction loc(order[0], (static_cast<int>(order[1]) - 48) );
		if (!checkPos(loc))
		{
			int res = createRes11or12(loc);
			return res;
		}
		Loction sourceLoc(order[2], static_cast<int>(order[3]) - 48);
		if (checkPosForRes13(sourceLoc))
			return 13;//there one of your pieces at the destination
		if(checkIllegelMoveRes21(loc, sourceLoc))
			return 21;//illegal movement of that piece
		if(checkChess(loc, sourceLoc))
			return 31;//this movement will cause you checkmate
		DoMove(loc, sourceLoc);
		replaceTurn();
		return 42;//the last movement was legal, next turn
	}
	catch (const std::exception& e)
	{
		throw e;
	}

}
//check if the move is legal
bool Board:: checkMoveForPawn(int placex, int placey, int destinationx, int destinationy){
	//check if the move is legal for pawn
		if (board[placex][placey]->GetColor() == Color::White)
		{
			if (placex == 1)
			{
				if (destinationx - placex > 2 ||   destinationx -placex < 1)
					return true;
			}
			else
			{
				if (destinationx - placex   > 1 || destinationx - placex  < 1)
					return true;
			}
		}
		else
		{
			if (placex == 6)
			{
						if (placex - destinationx  > 2 || placex-destinationx < 1)
							return true;
			}
			else
			{
						if (placex - destinationx  > 1 || placex - destinationx  < 1)
							return true;
			}
		}
		if(abs(placey-destinationy)>1)
			return true;
		//check if there is a piece in the way
		if (board[destinationx][destinationy] != nullptr)
		{
			if (placey == destinationy)
				return true;
		}
		if(board[destinationx][destinationy] == nullptr)
			if (abs(placey- destinationy) == 1)
				return true;
	return false;
}
bool Board::checkMoveForKing(int placex,int placey, int destinationx, int destinationy)
{
	//check if the move is legal for king
	if (abs(placex - destinationx) > 1 || abs(placey - destinationy) > 1)
		return true;
	//check if there is a piece in the way
	if (board[destinationx][destinationy] != nullptr 
		&& board[destinationx][destinationy]->GetColor() == board[placex][placey]->GetColor())
		return true;
	return false;
}
bool Board::checkMoveForRook(int placex, int placey, int destinationx,int destinationy)
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
					if (board[placex][i] != nullptr)
						return true;
				}
			}
			else
			{
				int start = placey + 1;
				for (int i = start; i < destinationy; i++)
				{
					if (board[placex][i] != nullptr)
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
					if (board[i][placey] != nullptr)
						return true;
				}
			}
			else
			{
				int start = placex + 1;
				for (int i = start; i < destinationx; i++)
				{
					if (board[i][placey] != nullptr)
						return true;
				}
			}
		}
		return false;
}
bool Board::checkMoveForBishop(int placex, int placey, int destinationx, int destinationy)
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
				if (board[i][j] != nullptr )
					return true;
			}
		}
		else
		{
			int startx = placex - 1;
			int starty = placey + 1;
			for (int i = startx, j = starty; i > destinationx && j < destinationy; i--, j++)
			{
				if (board[i][j] != nullptr)
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
				if (board[i][j] != nullptr)
					return true;
			}
		}
		else
		{
			int startx = placex + 1;
			int starty = placey + 1;
			for (int i = startx, j = starty; i < destinationx && j < destinationy; i++, j++)
			{
				if (board[i][j] != nullptr)
					return true;
			}
		}
	}
	return false;	
}
bool Board::checkMoveForKnight(int placex, int placey, int destinationx, int destinationy)
{
	//check if the move is legal for knight
	if (abs(placex - destinationx) == 2 && abs(placey - destinationy) == 1)
		return false;
	if (abs(placex - destinationx) == 1 && abs(placey - destinationy) == 2)
		return false;
	return true;
}
bool Board::checkChess(Loction loc,Loction sourceLoc)
{ 
	vector<vector<Peice*>> tempBoard = board;
	tempBoard[static_cast<int>(loc.x - 'a')][loc.y - 1] = nullptr;
	tempBoard[static_cast<int>(sourceLoc.x - 'a')][sourceLoc.y - 1] = board[static_cast<int>(loc.x - 'a')][loc.y - 1];
	Loction kingLocation;
	//find the king location
	if (board[static_cast<int>(loc.x - 'a')][loc.y - 1]->GetPeice() != 'k'
		&& board[static_cast<int>(loc.x - 'a')][loc.y - 1]->GetPeice() != 'K')
	{
		for (int i = 0; i < locOfKings.size(); i++)
		{
			int x = static_cast<int>(locOfKings[i].x - 'a');
			int y = locOfKings[i].y - 1;
			if (board[x][y]->GetColor() == turn)
			{
				kingLocation = Loction(locOfKings[i].x, locOfKings[i].y);
				break;
			}
		}
	}
	else
	{
		kingLocation = Loction(sourceLoc.x, sourceLoc.y);
	}
	////check if the king is in danger
	bool kingindanger = checkIfKingInDanger(kingLocation, turn, tempBoard);
	if (kingindanger)
		return true;
	else
		return false;
 }
// check if is illegal movement of that piece
bool Board::checkIllegelMoveRes21(Loction place, Loction destination)
{
	//this function check if the move is legal or not
	// if it is illegal it return true else it return false
	int placex = static_cast<int>(place.x - 'a');
	int placey = place.y - 1;
	int destinationx = static_cast<int>(destination.x - 'a');
	int destinationy = destination.y - 1;
	Peice* peice = board[placex][placey];
	char peiceName = peice->GetPeice();
	switch (peiceName)
	{
		case 'R' :
		{
			bool ans = checkMoveForRook(placex, placey, destinationx, destinationy);
			return ans;
			break; 
		}
		case 'r':
		{
			bool ans = checkMoveForRook(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'B':
		{
			bool ans = checkMoveForBishop(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'b':
		{
			bool ans = checkMoveForBishop(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'Q':
		{
			bool ans = checkMoveForBishop(placex, placey, destinationx, destinationy);
			if (!ans)
				return ans;
			else
			{
				ans = checkMoveForRook(placex, placey, destinationx, destinationy);
				return ans;
			}
			break;
		}
		case 'q':
		{
			bool ans = checkMoveForBishop(placex, placey, destinationx, destinationy);
			if (!ans)
				return ans;
			else
			{
				ans = checkMoveForRook(placex, placey, destinationx, destinationy);
				return ans;
			}
			break;
		}
		case 'N':
		{
			bool ans = checkMoveForKnight(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'n':
		{
			bool ans = checkMoveForKnight(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'P':
		{
			bool ans = checkMoveForPawn(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'p':
		{
			bool ans = checkMoveForPawn(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'K':
		{
			bool ans = checkMoveForKing(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}	
		case 'k': 
		{
			bool ans = checkMoveForKing(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}	
		default:
		{
			return true;
			break; 
		}
    }
	
}
//check there one of your pieces at the destination
bool Board::checkPosForRes13(Loction loc)
{
	//this function check if there is a piece in the given location
	if (turn == Color::White)
	{
		for (int i = 0; i < whitePiceLoc.size(); i++)
		{
			if (whitePiceLoc[i] == loc)
				return true;
		}
		return false;
	}
	else
	{
		for (int i = 0; i < blackPiceLoc.size(); i++)
		{
			if (blackPiceLoc[i] == loc)
				return true;
		}
		return false;
	}
}
// create response 11 or 12
int Board::createRes11or12(Loction loc)
{
	if (turn == Color::White)
	{
		for (int i = 0; i < blackPiceLoc.size(); i++)
		{
			if (blackPiceLoc[i] == loc)
				return 12;//there is a worng pice in the given location
		}
		return 11;//there is no pice in the given location
	}
	else
	{
		for (int i = 0; i < whitePiceLoc.size(); i++)
		{
			if (whitePiceLoc[i] == loc)
				return 12;
		}
		return 11;
	}
}
//check if there is a worng pice in the given location
bool Board::checkPos(Loction loc)
{
	//check the board if there is a pice in the given location
	if (turn == Color::White)
	{
		for (int i = 0; i < whitePiceLoc.size(); i++)
		{
			if (whitePiceLoc[i] == loc)
				return true;
		}
		return false;
	}
	else
	{
		for (int i = 0; i < blackPiceLoc.size(); i++)
		{
			if (blackPiceLoc[i] == loc)
				return true;
		}
		return false;
	}
}
//build the board
Board::Board(string boardString)
{
	vector<vector<Peice*>> matrix(8, vector<Peice*>(8));
	board = matrix;
	//create the board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (boardString[i * 8 + j])
			{
			case 'R':
			{
				board[i][j] =  new Rook(Color::White);
				whitePiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break; 
			}
			case 'B':
			{
				board[i][j] = new Bishop(Color::White);
				whitePiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break;
			}
			case 'Q':
			{
				board[i][j] = new Queen(Color::White);
				whitePiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break;
			}
			case 'N':
			{
					board[i][j] = new Knight(Color::White);
					whitePiceLoc.push_back(Loction((char)('a' + i), j + 1));
					break;
			}
			case 'K':
			{
			board[i][j] = new King(Color::White);
			auto locKing = Loction((char)('a' + i), j + 1);
			whitePiceLoc.push_back(locKing);
			locOfKings.push_back(locKing);
			break; 
			}
			case 'P':
			{
				board[i][j] = new Pawn(Color::White);
				whitePiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break;
			}
			case 'r':
			{
			board[i][j] = new Rook(Color::Black);
			blackPiceLoc.push_back(Loction(static_cast<char>('a' + i), j + 1));
			break; 
			}
			case 'b':
			{	
			board[i][j] = new Bishop(Color::Black);
			blackPiceLoc.push_back(Loction(static_cast<char>('a' + i), j + 1));
			break; 
			}
			case 'q':
			{
				board[i][j] = new Queen(Color::Black);
				blackPiceLoc.push_back(Loction(static_cast<char>('a' + i), j + 1));
				break; 
			}
			case 'n':
			{
					board[i][j] = new Knight(Color::Black);
					blackPiceLoc.push_back(Loction(static_cast<char>('a' + i), j + 1));
					break;
			}
			case 'k':
			{
			board[i][j] = new King(Color::Black);
			auto locKing = Loction(static_cast<char>('a' + i), j + 1);
			blackPiceLoc.push_back(locKing);
			locOfKings.push_back(locKing);
			break; 
			}
			case 'p':
			{
				board[i][j] = new Pawn(Color::Black);
				blackPiceLoc.push_back(Loction(static_cast<char>('a' + i), j + 1));
				break;
			}
			default:
				board[i][j] = nullptr;
				break;
			}
		}
	}
}
// replace the turn
void Board::replaceTurn()
{
	turn = (turn == Color::White) ? Color::Black : Color::White;
}
//check if the king is in danger
bool Board::checkIfKingInDanger(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard)
{
	
	int KingLocx=KingLoc.x - 'a';
	int KingLocy=KingLoc.y - 1;
	if(dangerFromRookAndQueen(KingLocx,KingLocy,kingColor,tempBoard))
		return true;
	if (dangerFromBishopAndQueen(KingLocx, KingLocy, kingColor, tempBoard))
		return true;
	if (dangerFromPawn(KingLocx, KingLocy, kingColor, tempBoard))
		return true;
	if(dangerFromKing(KingLocx, KingLocy, kingColor, tempBoard))
		return true;
	//check if the king is in check by knight
	return false;
}
// check if the king is in danger from the rook and queen
bool Board::dangerFromRookAndQueen(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard)
{

	//check for chess from rook or queen
	//check down
	for (int i = KingLocx + 1; i < 8; i++)
	{
		if (tempBoard[i][KingLocy] != nullptr)
		{
			if (tempBoard[i][KingLocy]->GetColor() != kingColor)
			{
				if (tempBoard[i][KingLocy]->GetPeice() == 'R' ||
					tempBoard[i][KingLocy]->GetPeice() == 'r' ||
					tempBoard[i][KingLocy]->GetPeice() == 'Q' ||
					tempBoard[i][KingLocy]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	//check up
	for (int i = KingLocx - 1; i >= 0; i--)
	{
		if (tempBoard[i][KingLocy] != nullptr)
		{
			if (tempBoard[i][KingLocy]->GetColor() != kingColor)
			{
				if (tempBoard[i][KingLocy]->GetPeice() == 'R' ||
					tempBoard[i][KingLocy]->GetPeice() == 'r' ||
					tempBoard[i][KingLocy]->GetPeice() == 'Q' ||
					tempBoard[i][KingLocy]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	//check left
	for (int i = KingLocy + 1; i < 8; i++)
	{
		if (tempBoard[KingLocx][i] != nullptr)
		{
			if (tempBoard[KingLocx][i]->GetColor() != kingColor)
			{
				if (tempBoard[KingLocx][i]->GetPeice() == 'R' ||
					tempBoard[KingLocx][i]->GetPeice() == 'r' ||
					tempBoard[KingLocx][i]->GetPeice() == 'Q' ||
					tempBoard[KingLocx][i]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	//check right
	for (int i = KingLocy - 1; i >= 0; i--)
	{
		if (tempBoard[KingLocx][i] != nullptr)
		{
			if (tempBoard[KingLocx][i]->GetColor() != kingColor)
			{
				if (tempBoard[KingLocx][i]->GetPeice() == 'R' ||
					tempBoard[KingLocx][i]->GetPeice() == 'r' ||
					tempBoard[KingLocx][i]->GetPeice() == 'Q' ||
					tempBoard[KingLocx][i]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
}
// check if the king is in danger from the bishop and queen
bool Board:: dangerFromBishopAndQueen(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard)
{
	//check for chess from bishop or queen
	//check up right
	for (int i = KingLocx + 1, j = KingLocy + 1; i < 8 && j < 8; i++, j++)
	{
		if (tempBoard[i][j] != nullptr)
		{
			if (tempBoard[i][j]->GetColor() != kingColor)
			{
				if (tempBoard[i][j]->GetPeice() == 'B' ||
					tempBoard[i][j]->GetPeice() == 'b' ||
					tempBoard[i][j]->GetPeice() == 'Q' ||
					tempBoard[i][j]->GetPeice() == 'q')
					return true;
				else break;
			}
			else
				break;
		}
	}
	//check up left
	for (int i = KingLocx + 1, j = KingLocy - 1; i < 8 && j >= 0; i++, j--)
	{
		if (tempBoard[i][j] != nullptr)
		{
			if (tempBoard[i][j]->GetColor() != kingColor)
			{
				if (tempBoard[i][j]->GetPeice() == 'B' ||
					tempBoard[i][j]->GetPeice() == 'b' ||
					tempBoard[i][j]->GetPeice() == 'Q' ||
					tempBoard[i][j]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	// check down right
	for (int i = KingLocx - 1, j = KingLocy + 1; i >= 0 && j < 8; i--, j++)
	{
		if (tempBoard[i][j] != nullptr)
		{
			if (tempBoard[i][j]->GetColor() != kingColor)
			{
				if (tempBoard[i][j]->GetPeice() == 'B' ||
					tempBoard[i][j]->GetPeice() == 'b' ||
					tempBoard[i][j]->GetPeice() == 'Q' ||
					tempBoard[i][j]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	// check down left
	for (int i = KingLocx - 1, j = KingLocy - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (tempBoard[i][j] != nullptr)
		{
			if (tempBoard[i][j]->GetColor() != kingColor)
			{
				if (tempBoard[i][j]->GetPeice() == 'B' ||
					tempBoard[i][j]->GetPeice() == 'b' ||
					tempBoard[i][j]->GetPeice() == 'Q' ||
					tempBoard[i][j]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
}
// check if the king is in danger from the pawn
bool Board:: dangerFromPawn(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard)
{
	//check for chess from pawn
	//the king is in the middle of the board
	if (KingLocx != 0 && KingLocx != 7)
	{
		if (tempBoard[KingLocx][KingLocy]->GetColor() == Color::White)
		{
			if (KingLocy != 7)//check if is not in the last row
			{
				if (tempBoard[KingLocx + 1][KingLocy + 1] != nullptr)
					if (tempBoard[KingLocx + 1][KingLocy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx + 1][KingLocy + 1]->GetPeice() == 'p')
							return true;
				if (tempBoard[KingLocx + 1][KingLocy - 1] != nullptr)
					if (tempBoard[KingLocx + 1][KingLocy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx + 1][KingLocy - 1]->GetPeice() == 'p')
							return true;
			}
		}
		else
		{
			if (KingLocy != 0)
			{
				if (tempBoard[KingLocx - 1][KingLocy - 1] != nullptr)
					if (tempBoard[KingLocx - 1][KingLocy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx - 1][KingLocy - 1]->GetPeice() == 'P')
							return true;
				if (tempBoard[KingLocx - 1][KingLocy + 1] != nullptr)
					if (tempBoard[KingLocx - 1][KingLocy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx - 1][KingLocy + 1]->GetPeice() == 'p')
							return true;
			}
		}
	}
}
// check if the king is in danger from the king
bool Board::dangerFromKing(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard)
{
	//the king is in the first row
	if (KingLocx == 0)
	{
		if (tempBoard[KingLocx][KingLocy]->GetColor() == Color::White)
		{
			if (KingLocy != 7)//check if is not in the last row
			{
				if (tempBoard[KingLocx + 1][KingLocy + 1] != nullptr)
					if (tempBoard[KingLocx + 1][KingLocy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx + 1][KingLocy + 1]->GetPeice() == 'p')
							return true;
			}
		}
		else
		{
			if (KingLocy != 0)
			{
				if (tempBoard[KingLocx - 1][KingLocy - 1] != nullptr)
					if (tempBoard[KingLocx - 1][KingLocy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx - 1][KingLocy - 1]->GetPeice() == 'P')
							return true;
			}
		}
	}
	// the king is in the lust row
	if (KingLocx == 7)
	{
		if (tempBoard[KingLocx][KingLocy]->GetColor() == Color::White)
		{
			if (KingLocx != 7)//check if is not in the last row
			{
				if (tempBoard[KingLocx + 1][KingLocy - 1] != nullptr)
					if (tempBoard[KingLocx + 1][KingLocy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx + 1][KingLocy - 1]->GetPeice() == 'p')
							return true;
			}
		}
		else
		{
			if (KingLocx != 0)
			{
				if (tempBoard[KingLocx - 1][KingLocy + 1] != nullptr)
					if (tempBoard[KingLocx - 1][KingLocy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLocx - 1][KingLocy + 1]->GetPeice() == 'P')
							return true;
			}
		}
	}
}
//update the board
void Board:: DoMove(Loction loc, Loction sourceLoc)
{
	
	int locx = static_cast<int>(loc.x - 'a');
	int locy = loc.y - 1;
	int sourceLocx = static_cast<int>(sourceLoc.x - 'a');
	int sourceLocy = sourceLoc.y - 1;
	// if the pice eat another pice
	if (board[sourceLocx][sourceLocy] != nullptr)
		{
			for (int i = 0; i < whitePiceLoc.size(); i++)
				if (whitePiceLoc[i] == sourceLoc)
					whitePiceLoc.erase(whitePiceLoc.begin() + i);
			for (int i = 0; i < blackPiceLoc.size(); i++)
				if (blackPiceLoc[i] == sourceLoc)
					blackPiceLoc.erase(blackPiceLoc.begin() + i);
		}
	// update the pice location
	if (GetTurn() == Color::White)
		{
			for (int i = 0; i < whitePiceLoc.size(); i++)
			{
				if (whitePiceLoc[i] == loc)
					whitePiceLoc.erase(whitePiceLoc.begin() + i);
			}
			whitePiceLoc.push_back(sourceLoc);
		}
	else
		{
			for (int i = 0; i < blackPiceLoc.size(); i++)
			{
				if (blackPiceLoc[i] == loc)
					blackPiceLoc.erase(blackPiceLoc.begin() + i);
			}
			blackPiceLoc.push_back(sourceLoc);
		}
	// if the pice is a king update the king location
	if (board[locx][locy]->GetPeice() == 'k' && board[locx][locy]->GetPeice() == 'K')
		{
			for (int i=0;i<locOfKings.size();i++)
				if (locOfKings[i]==loc)
					locOfKings.erase(locOfKings.begin() + i);
			locOfKings.push_back(sourceLoc);
		}
	// update the board
	board[sourceLocx][sourceLocy] = board[locx][locy];
	board[locx][locy] = nullptr;
	
}
// delete the pice from the board
Board::~Board()
{
	// clean up the memory
	for (auto row : board) {
		for (auto obj : row) {
			delete obj;
		}
	}
}
#include "Board.h"
#include "Peice.h"
#include "Rook.h"
#include "King.h"
#include "Loction.h"
#include "Color.h"
#include <iostream>
#include <string>
#include <vector>
using std::vector;

bool Board::checkPosForRes13(Loction loc)
{
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

int Board::getResponse(string order)
{	
	try{
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
	if(checkChess(loc))
		return 31;//this movement will cause you checkmate
	replaceTurn();
	return 42;//the last movement was legal, next turn
}
catch (const std::exception& e)
{
	throw e;
}

}
bool Board::checkChess(Loction loc) 
{ 
	//copy the bord
	//move the piece
	////check if the king is in danger
	//bool kingindanger = checkifkingindanger(kinglocation, kingcolor);
	//if (kingindanger)
	//{
	//	//move the piece back
	//	return true;
	//}
	//else
	//{
	//	//move the piece back
	//	return false;
	//}
 }
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
	if (peiceName == 'R' || peiceName == 'r')
	{
		if(placex != destinationx && placey != destinationy)
			return true;
		else
		{
			if (placex == destinationx)
			{
				if (placey > destinationy )
				{
					int start = placey - 1;
					for (int i = start; i >= destinationy; i--)
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
				return false;
			}
		else
		{
			
			if (placex > destinationx)
			{
				int start = placex - 1;
				for (int i = start;i >= destinationx;i--)
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
			return false;
		}
		
		}
	}
}

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
				board[i][j] =  new Rook(Color::White);
				whitePiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break;
				/*
				case 'N':
					board[i][j] = new Knight(Peice::Color::White);
					break;
				case 'B':
					board[i][j] = new Bishop(Peice::Color::White);
					break;
				case 'Q':
					board[i][j] = new Queen(Peice::Color::White);
					break;
				*/
			case 'K':
				board[i][j] = new King(Color::White);
				whitePiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break;
				/*
			case 'P':
				board[i][j] = new Pawn(Peice::Color::White);
				break;
				*/
			case 'r':
				board[i][j] = new Rook(Color::Black);
				blackPiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break;
				/*
				case 'n':
					board[i][j] = new Knight(Peice::Color::Black);
					break;
				case 'b':
					board[i][j] = new Bishop(Peice::Color::Black);
					break;
				case 'q':
					board[i][j] = new Queen(Peice::Color::Black);
					break;
				*/
			case 'k':
				board[i][j] = new King(Color::Black);
				blackPiceLoc.push_back(Loction((char)('a' + i), j + 1));
				break;
				/*
			case 'p':
				board[i][j] = new Pawn(Peice::Color::Black);
				break;
				*/
			default:
				board[i][j] = nullptr;
				break;
			}
		}
	}
}

void Board::replaceTurn()
{
	turn = (turn == Color::White) ? Color::Black : Color::White;
}
//x is between a to h and y is between 1 to 8
//return true if king is in danger
bool Board::checkIfKingInDanger(Loction KingLoc, Color kingColor)
{
	//check down
	for (int i = KingLoc.x + 1; i < 8; i++)
	{
		if (board[i][KingLoc.y] != nullptr)
		{
			if (board[i][KingLoc.y]->GetColor() != kingColor)
			{
				if (board[i][KingLoc.y]->GetPeice() == 'R' || 
					board[i][KingLoc.y]->GetPeice() == 'r' ||
					board[i][KingLoc.y]->GetPeice() == 'Q' ||
					board[i][KingLoc.y]->GetPeice() == 'q')
					return true;
			}
			else break;
		}
	}
	//check up
	for (int i = KingLoc.x -1 ; i >=0; i--)
	{
		if (board[i][KingLoc.y] != nullptr)
		{
			if (board[i][KingLoc.y]->GetColor() != kingColor)
			{
				if (board[i][KingLoc.y]->GetPeice() == 'R' ||
					board[i][KingLoc.y]->GetPeice() == 'r' ||
					board[i][KingLoc.y]->GetPeice() == 'Q' ||
					board[i][KingLoc.y]->GetPeice() == 'q')
					return true;
			}
			else break;
		}
	}
	//check left
	for (int i = KingLoc.y + 1; i < 8; i++)
	{
		if (board[KingLoc.x][i] != nullptr)
		{
			if (board[KingLoc.x][i]->GetColor() != kingColor)
			{
				if (board[KingLoc.x][i]->GetPeice() == 'R' ||
					board[KingLoc.x][i]->GetPeice() == 'r' ||
					board[KingLoc.x][i]->GetPeice() == 'Q' ||
					board[KingLoc.x][i]->GetPeice() == 'q')
					return true;
			}
			else break;
		}
	}
	//check right
	for (int i = KingLoc.y - 1; i >= 0; i--)
	{
		if (board[KingLoc.x][i] != nullptr)
		{
			if (board[KingLoc.x][i]->GetColor() != kingColor)
			{
				if (board[KingLoc.x][i]->GetPeice() == 'R' ||
					board[KingLoc.x][i]->GetPeice() == 'r' ||
					board[KingLoc.x][i]->GetPeice() == 'Q' ||
					board[KingLoc.x][i]->GetPeice() == 'q')
					return true;
			}
			else break;
		}
	}

	
	//check down left
	//check down right
	//check up left
	//check up right
	return false;
}
Board::~Board()
{
	// clean up the memory
	for (auto row : board) {
		for (auto obj : row) {
			delete obj;
		}
	}
}


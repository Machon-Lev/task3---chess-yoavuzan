#include <iostream>
#include <string>
#include <vector>
#include "Peice.h"
#include "Rook.h"
#include "King.h"
#include "Loction.h"
#pragma once
using std::string;

class Board
{
private:
	Peice* board[8][8]{ nullptr };
	bool chess = false;
	Color turn = Color::White;
	vector <Loction>blackPiceLoc;
	vector <Loction>whitePiceLoc;
	bool checkPos((Loction loc);
	int createRes11or12();
	bool checkPosForRes13(Loction loc);
public:
	Board(string boardString);
	void replaceTurn() 
	{ turn = (turn == Color::White) ? Color::Black : Color::White; }
	void isChess() { chess = true; }
	int getResponse(string order) ;
	
};
Board::checkPosForRes13(Loction loc)
{
	if (turn == Color::White)
	{
		for (int i = 0; i < balckPiceLoc.size(); i++)
		{
			if (balckPiceLoc[i] == loc)
				return true;
		}
		return false;
	}
	else
	{
		for (int i = 0; i < whitePiceLoc.size(); i++)
		{
			if (whitePiceLoc[i] == loc)
				return true;
		}
		return false;
	}
}
Board::getResponse(string order)
{
	Loction loc(order[0], order[1]);
	if(!checkPos(loc))
	{
		int res = createRes11or12();
		return res;
	}
	Loction newLoc(order[3], order[4]);
	if (checkPosForRes13(newLoc))
		return 13;
	
		
}
Board::createRes11or12() 
{
	if (turn == Color::White)
	{
		for (int i = 0; i < balckPiceLoc.size(); i++)
		{
			if (balckPiceLoc[i] == loc)
				return 12;
		}
		return 11;
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

Board::checkPos(Loction loc)
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
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (boardString[i*8+j])
			{
		case 'R':
			board[i][j] = new Rook(Peices::Color::White);
			whitePiceLoc.push_back(Loction((char)('A'+i), j+1));
			break;
		/*
		case 'N':
			board[i][j] = new Knight(Peices::Color::White);
			break;
		case 'B':
			board[i][j] = new Bishop(Peices::Color::White);
			break;
		case 'Q':
			board[i][j] = new Queen(Peices::Color::White);
			break;
		*/
		case 'K':
			board[i][j] = new King(Peices::Color::White);
			whitePiceLoc.push_back(Loction((char)('A' + i), j+1));
			break;
			/*
		case 'P':
			board[i][j] = new Pawn(Peices::Color::White);
			break;
			*/
		case 'r':
			board[i][j] = new Rook(Peices::Color::Black);
			blackPiceLoc.push_back(Loction((char)('A' + i), j+1));
			break;
		/*
		case 'n':
			board[i][j] = new Knight(Peices::Color::Black);
			break;
		case 'b':
			board[i][j] = new Bishop(Peices::Color::Black);
			break;
		case 'q':
			board[i][j] = new Queen(Peices::Color::Black);
			break;
		*/
		case 'k':
			board[i][j] = new King(Peices::Color::Black);
			blackPiceLoc.push_back(Loction((char)('A' + i), j+1));
			break;
			/*
		case 'p':
			board[i][j] = new Pawn(Peices::Color::Black);
			break;
			*/
		default:
			board[i][j] = nullptr;
			break;
		}
	}
}
}
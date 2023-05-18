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

bool Board::checkRes11(Loction loc) {
	if (board[static_cast<int>(loc.x - 'a')][loc.y - 1] == nullptr)
		return true;
	return false;
}
bool Board::checkRes12(Loction loc) {
	if (board[static_cast<int>(loc.x - 'a')][loc.y - 1]->GetColor() != turn)
		return true;
	return false;
}

//get responce to the order
int Board::getResponse(string order)
{	
	try
	{
		Loction loc(order[0], (static_cast<int>(order[1]) - 48) );
		if(checkRes11(loc))
			return 11;//there is no piece at the destination
		if (checkRes12(loc))
			return 12; //the piece in the source is piece of your opponent
		Loction sourceLoc(order[2], static_cast<int>(order[3]) - 48);
		if (checkPosForRes13(sourceLoc))
			return 13;//there one of your pieces at the destination
		if(checkIllegelMoveRes21(loc, sourceLoc))
			return 21;//illegal movement of that piece
		int res= checkChess(loc, sourceLoc);
		if(res==31)
			return 31;//this movement will cause you checkmate
		if(res==41)
		{
			DoMove(loc, sourceLoc);
			replaceTurn();
			return 41;//the last movement was legal and cause check
		}
		DoMove(loc, sourceLoc);
		replaceTurn();
		return 42;//the last movement was legal, next turn
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}
int Board::checkChess(Loction loc,Loction sourceLoc)
{ 
	vector<vector<Peice*>> tempBoard = board;
	tempBoard[static_cast<int>(loc.x - 'a')][loc.y - 1] = nullptr;
	tempBoard[static_cast<int>(sourceLoc.x - 'a')][sourceLoc.y - 1] = board[static_cast<int>(loc.x - 'a')][loc.y - 1];
	Loction kingLocation;
	bool flag = false;
	//find the king location
	if (board[static_cast<int>(loc.x - 'a')][loc.y - 1]->GetPeice() != 'k'
		&& board[static_cast<int>(loc.x - 'a')][loc.y - 1]->GetPeice() != 'K')
	{
	int x = static_cast<int>(locOfKings[0].x - 'a');
	int y = locOfKings[0].y - 1;
	if(tempBoard[x][y]->GetColor() == turn)
		kingLocation = Loction(locOfKings[0].x, locOfKings[0].y);
	else
		kingLocation = Loction(locOfKings[1].x, locOfKings[1].y);
	}
	else
	{
		kingLocation = Loction(sourceLoc.x, sourceLoc.y);//check the move.
	}
	////check if the king is in danger
	bool kingindanger = checkIfKingInDanger(kingLocation, turn, tempBoard);
	if (kingindanger)
		return 31;//this movement will cause you checkmate
	if (kingLocation == sourceLoc)
		kingLocation = loc;
	kingLocation= kingLocation == locOfKings[0]? locOfKings[1] : locOfKings[0];
	Color tempturn= turn== Color::White? Color::Black : Color::White;
	kingindanger = checkIfKingInDanger(kingLocation, tempturn, tempBoard);
	if (kingindanger)
		return 41;//the last movement was legal and cause check
	return 0;//the last movement was legal, next turn
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
			bool ans = dynamic_cast<Rook*>(peice)->checkMoveForRook(placex, placey, destinationx, destinationy);
			return ans;
			break; 
		}
		case 'r':
		{
			bool ans = dynamic_cast<Rook*>(peice)->checkMoveForRook(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'B':
		{
			bool ans = dynamic_cast<Bishop*>(peice)->checkMoveForBishop(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'b':
		{
			bool ans = dynamic_cast<Bishop*>(peice)->checkMoveForBishop(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'Q':
		{
			bool ans = dynamic_cast<Queen*>(peice)->checkMoveForQueen(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'q':
		{
			bool ans = dynamic_cast<Queen*>(peice)->checkMoveForQueen(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'N':
		{
			bool ans = dynamic_cast<Knight*>(peice)->checkMoveForKnight(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'n':
		{
			bool ans = dynamic_cast<Knight*>(peice)->checkMoveForKnight(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'P':
		{
			bool ans = dynamic_cast<Pawn*>(peice)->checkMoveForPawn(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'p':
		{
			bool ans = dynamic_cast<Pawn*>(peice)->checkMoveForPawn(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}
		case 'K':
		{
			bool ans = dynamic_cast<King*>(peice)->checkMoveForKing(placex, placey, destinationx, destinationy);
			return ans;
			break;
		}	
		case 'k': 
		{
			bool ans = dynamic_cast<King*>(peice)->checkMoveForKing(placex, placey, destinationx, destinationy);
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
{	//this function check if there is a piece in the given location
	if (board[static_cast<int>(loc.x - 'a')][loc.y - 1] != nullptr)
		if (board[static_cast<int>(loc.x - 'a')][loc.y - 1]->GetColor() == turn)
			return true;
	return false;
}
//check if there is a worng pice in the given location
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
				board[i][j] =  new Rook(Color::White,this);
				break; 
			}
			case 'B':
			{
				board[i][j] = new Bishop(Color::White,this);
				break;
			}
			case 'Q':
			{
				board[i][j] = new Queen(Color::White,this);
				break;
			}
			case 'N':
			{
					board[i][j] = new Knight(Color::White, this);
					break;
			}
			case 'K':
			{
			board[i][j] = new King(Color::White, this);
			locOfKings.push_back(Loction((char)('a' + i), j + 1));
			break; 
			}
			case 'P':
			{
				board[i][j] = new Pawn(Color::White, this);
				break;
			}
			case 'r':
			{
			board[i][j] = new Rook(Color::Black, this);
			break; 
			}
			case 'b':
			{	
			board[i][j] = new Bishop(Color::Black,this);
			break; 
			}
			case 'q':
			{
				board[i][j] = new Queen(Color::Black,this);
				break; 
			}
			case 'n':
			{
					board[i][j] = new Knight(Color::Black, this);
					break;
			}
			case 'k':
			{
			board[i][j] = new King(Color::Black, this);
			locOfKings.push_back(Loction(static_cast<char>('a' + i), j + 1));
			break; 
			}
			case 'p':
			{
				board[i][j] = new Pawn(Color::Black, this);
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
	return false;
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
	return false;
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
	return false;
}

bool isExist(int x, int y) {
	if(x < 0 || x > 7 || y < 0 || y > 7)
		return false;
	return true;
}

// check if the king is in danger from the king
bool Board::dangerFromKing(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard)
{	
	//check the row below the king
	for (int i= KingLocy-1;i <KingLocy+2;i++)
	{
		if(isExist(KingLocx-1,i))
			if (tempBoard[KingLocx - 1][i] != nullptr)
				if (tempBoard[KingLocx - 1][i]->GetColor() != kingColor)
					if (tempBoard[KingLocx - 1][i]->GetPeice() != 'k'||
						tempBoard[KingLocx - 1][i]->GetPeice() != 'K')
						return true;
	}
	//check the row above the king
	for (int i = KingLocy - 1; i < KingLocy + 2; i++)
	{
		if (isExist(KingLocx + 1, i))
			if (tempBoard[KingLocx + 1][i] != nullptr)
				if (tempBoard[KingLocx + 1][i]->GetColor() != kingColor)
					if (tempBoard[KingLocx + 1][i]->GetPeice() != 'k' ||
						tempBoard[KingLocx + 1][i]->GetPeice() != 'K')
						return true;
	}
	//check the row of the king
	for (int i = KingLocy - 1; i < KingLocy + 2; i+=2)
	{
		if (isExist(KingLocx, i))
			if (tempBoard[KingLocx][i] != nullptr)
				if (tempBoard[KingLocx][i]->GetColor() != kingColor)
					if (tempBoard[KingLocx][i]->GetPeice() != 'k' ||
												tempBoard[KingLocx][i]->GetPeice() != 'K')
						return true;
	}
	return false;
}
//update the board
void Board:: DoMove(Loction loc, Loction sourceLoc)
{
	
	int locx = static_cast<int>(loc.x - 'a');
	int locy = loc.y - 1;
	int sourceLocx = static_cast<int>(sourceLoc.x - 'a');
	int sourceLocy = sourceLoc.y - 1;
	// if the pice is a king update the king location
	if (board[locx][locy]->GetPeice() == 'k' || board[locx][locy]->GetPeice() == 'K')
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
			obj= nullptr;
		}
	}
}
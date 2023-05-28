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
	if (board[loc.compx][loc.compy] == nullptr)
		return true;
	return false;
}
bool Board::checkRes12(Loction loc) {
	if (board[loc.compx][loc.compy]->GetColor() != turn)
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
	tempBoard[loc.compx][loc.compy] = nullptr;
	tempBoard[sourceLoc.compx][sourceLoc.compy] = board[loc.compx][loc.compy];
	Loction kingLocation;
	//find the king location
	if (board[loc.compx][loc.compy]->GetPeice() != 'k'
		&& board[loc.compx][loc.compy]->GetPeice() != 'K')
	{
	int x =locOfKings[0].compx;
	int y = locOfKings[0].compy ;
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
	
	Peice* peice = board[place.compx][place.compy];
	char peiceName = peice->GetPeice();
	switch (peiceName)
	{
		case 'R' :
		{
			bool ans = dynamic_cast<Rook*>(peice)->checkMoveForRook(place, destination);
			return ans;
			break; 
		}
		case 'r':
		{
			bool ans = dynamic_cast<Rook*>(peice)->checkMoveForRook(place, destination);
			return ans;
			break;
		}
		case 'B':
		{
			bool ans = dynamic_cast<Bishop*>(peice)->checkMoveForBishop(place, destination);
			return ans;
			break;
		}
		case 'b':
		{
			bool ans = dynamic_cast<Bishop*>(peice)->checkMoveForBishop(place, destination);
			return ans;
			break;
		}
		case 'Q':
		{
			bool ans = dynamic_cast<Queen*>(peice)->checkMoveForQueen(place, destination);
			return ans;
			break;
		}
		case 'q':
		{
			bool ans = dynamic_cast<Queen*>(peice)->checkMoveForQueen(place, destination);
			return ans;
			break;
		}
		case 'N':
		{
			bool ans = dynamic_cast<Knight*>(peice)->checkMoveForKnight(place ,destination);
			return ans;
			break;
		}
		case 'n':
		{
			bool ans = dynamic_cast<Knight*>(peice)->checkMoveForKnight(place, destination);
			return ans;
			break;
		}
		case 'P':
		{
			bool ans = dynamic_cast<Pawn*>(peice)->checkMoveForPawn(place, destination);
			return ans;
			break;
		}
		case 'p':
		{
			bool ans = dynamic_cast<Pawn*>(peice)->checkMoveForPawn(place, destination);
			return ans;
			break;
		}
		case 'K':
		{
			bool ans = dynamic_cast<King*>(peice)->checkMoveForKing(place, destination);
			return ans;
			break;
		}	
		case 'k': 
		{
			bool ans = dynamic_cast<King*>(peice)->checkMoveForKing(place, destination);
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
	if (board[loc.compx][loc.compy] != nullptr)
		if (board[loc.compx][loc.compy]->GetColor() == turn)
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
	if(dangerFromRookAndQueen(KingLoc,kingColor,tempBoard))
		return true;
	if (dangerFromBishopAndQueen(KingLoc, kingColor, tempBoard))
		return true;
	if (dangerFromPawn(KingLoc, kingColor, tempBoard))
		return true;
	if(dangerFromKing(KingLoc, kingColor, tempBoard))
		return true;
	//check if the king is in check by knight
	if(dangerFromKnight(KingLoc, kingColor, tempBoard))
	return false;
}

//check if the king is in danger from the knight
bool Board::dangerFromKnight(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard)
{
	int* arr = new int[2] {-1, 1};
	int* widghandlen= new int [2]{2,-2};
	for(int k=0;k<2;k++)
		for (int i=0;i<2;i++)
			for (int j = 0; j < 2; j++)
				if (k == 0)// check the first option
				{
					int x = KingLoc.compx + arr[i];
					int y = KingLoc.compy + widghandlen[j];
					if (isExist(x,y))
						if (tempBoard[x][y] != nullptr)
							if (tempBoard[KingLoc.compx + arr[i]][KingLoc.compy + widghandlen[j]]->GetColor() != kingColor)
								if (tempBoard[KingLoc.compx + arr[i]][KingLoc.compy + widghandlen[j]]->GetPeice() == 'N' ||
									tempBoard[KingLoc.compx + arr[i]][KingLoc.compy + widghandlen[j]]->GetPeice() == 'n')
									return true;
				}
				else// check the second option
				{
					int x = KingLoc.compx + widghandlen[i];
					int y = KingLoc.compy + arr[j];
					if (isExist(x,y))
						if (tempBoard[KingLoc.compx + widghandlen[i]][KingLoc.compy + arr[j]] != nullptr)
							if (tempBoard[KingLoc.compx + widghandlen[i]][KingLoc.compy + arr[j]]->GetColor() != kingColor)
								if (tempBoard[KingLoc.compx + widghandlen[i]][KingLoc.compy + arr[j]]->GetPeice() == 'N' ||
									tempBoard[KingLoc.compx + widghandlen[i]][KingLoc.compy + arr[j]]->GetPeice() == 'n')
									return true;
				}
}



// check if the king is in danger from the rook and queen
bool Board::dangerFromRookAndQueen(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard)
{

	//check for chess from rook or queen
	//check down
	for (int i = KingLoc.compx + 1; i < 8; i++)
	{
		if (tempBoard[i][KingLoc.compy] != nullptr)
		{
			if (tempBoard[i][KingLoc.compy]->GetColor() != kingColor)
			{
				if (tempBoard[i][KingLoc.compy]->GetPeice() == 'R' ||
					tempBoard[i][KingLoc.compy]->GetPeice() == 'r' ||
					tempBoard[i][KingLoc.compy]->GetPeice() == 'Q' ||
					tempBoard[i][KingLoc.compy]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	//check up
	for (int i = KingLoc.compx - 1; i >= 0; i--)
	{
		if (tempBoard[i][KingLoc.compy] != nullptr)
		{
			if (tempBoard[i][KingLoc.compy]->GetColor() != kingColor)
			{
				if (tempBoard[i][KingLoc.compy]->GetPeice() == 'R' ||
					tempBoard[i][KingLoc.compy]->GetPeice() == 'r' ||
					tempBoard[i][KingLoc.compy]->GetPeice() == 'Q' ||
					tempBoard[i][KingLoc.compy]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	//check left
	for (int i = KingLoc.compy + 1; i < 8; i++)
	{
		if (tempBoard[KingLoc.compx][i] != nullptr)
		{
			if (tempBoard[KingLoc.compx][i]->GetColor() != kingColor)
			{
				if (tempBoard[KingLoc.compx][i]->GetPeice() == 'R' ||
					tempBoard[KingLoc.compx][i]->GetPeice() == 'r' ||
					tempBoard[KingLoc.compx][i]->GetPeice() == 'Q' ||
					tempBoard[KingLoc.compx][i]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	//check right
	for (int i = KingLoc.compy - 1; i >= 0; i--)
	{
		if (tempBoard[KingLoc.compx][i] != nullptr)
		{
			if (tempBoard[KingLoc.compx][i]->GetColor() != kingColor)
			{
				if (tempBoard[KingLoc.compx][i]->GetPeice() == 'R' ||
					tempBoard[KingLoc.compx][i]->GetPeice() == 'r' ||
					tempBoard[KingLoc.compx][i]->GetPeice() == 'Q' ||
					tempBoard[KingLoc.compx][i]->GetPeice() == 'q')
					return true;
				else break;
			}
			else break;
		}
	}
	return false;
}
// check if the king is in danger from the bishop and queen
bool Board:: dangerFromBishopAndQueen(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard)
{
	//check for chess from bishop or queen
	//check up right
	for (int i = KingLoc.compx + 1, j = KingLoc.compy + 1; i < 8 && j < 8; i++, j++)
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
	for (int i = KingLoc.compx + 1, j = KingLoc.compy - 1; i < 8 && j >= 0; i++, j--)
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
	for (int i = KingLoc.compx - 1, j = KingLoc.compy + 1; i >= 0 && j < 8; i--, j++)
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
	for (int i = KingLoc.compx - 1, j = KingLoc.compy - 1; i >= 0 && j >= 0; i--, j--)
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
bool Board:: dangerFromPawn(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard)
{
	//check for chess from pawn
	//the king is in the middle of the board
	if (KingLoc.compx != 0 && KingLoc.compx != 7)
	{
		if (tempBoard[KingLoc.compx][KingLoc.compy]->GetColor() == Color::White)
		{
			if (KingLoc.compy != 7)//check if is not in the last row
			{
				if (tempBoard[KingLoc.compx + 1][KingLoc.compy + 1] != nullptr)
					if (tempBoard[KingLoc.compx + 1][KingLoc.compy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx + 1][KingLoc.compy + 1]->GetPeice() == 'p')
							return true;
				if (tempBoard[KingLoc.compx + 1][KingLoc.compy - 1] != nullptr)
					if (tempBoard[KingLoc.compx + 1][KingLoc.compy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx + 1][KingLoc.compy - 1]->GetPeice() == 'p')
							return true;
			}
		}
		else
		{
			if (KingLoc.compy != 0)
			{
				if (tempBoard[KingLoc.compx - 1][KingLoc.compy - 1] != nullptr)
					if (tempBoard[KingLoc.compx - 1][KingLoc.compy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx - 1][KingLoc.compy - 1]->GetPeice() == 'P')
							return true;
				if (tempBoard[KingLoc.compx - 1][KingLoc.compy + 1] != nullptr)
					if (tempBoard[KingLoc.compx - 1][KingLoc.compy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx - 1][KingLoc.compy + 1]->GetPeice() == 'p')
							return true;
			}
		}
	}
	//the king is in the first row
	if (KingLoc.compx == 0)
	{
		if (tempBoard[KingLoc.compx][KingLoc.compy]->GetColor() == Color::White)
		{
			if (KingLoc.compy != 7)//check if is not in the last row
			{
				if (tempBoard[KingLoc.compx + 1][KingLoc.compy + 1] != nullptr)
					if (tempBoard[KingLoc.compx + 1][KingLoc.compy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx + 1][KingLoc.compy + 1]->GetPeice() == 'p')
							return true;
			}
		}
		else
		{
			if (KingLoc.compy != 0)
			{
				if (tempBoard[KingLoc.compx - 1][KingLoc.compy - 1] != nullptr)
					if (tempBoard[KingLoc.compx - 1][KingLoc.compy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx - 1][KingLoc.compy - 1]->GetPeice() == 'P')
							return true;
			}
		}
	}
	// the king is in the lust row
	if (KingLoc.compx == 7)
	{
		if (tempBoard[KingLoc.compx][KingLoc.compy]->GetColor() == Color::White)
		{
			if (KingLoc.compx != 7)//check if is not in the last row
			{
				if (tempBoard[KingLoc.compx + 1][KingLoc.compy - 1] != nullptr)
					if (tempBoard[KingLoc.compx + 1][KingLoc.compy - 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx + 1][KingLoc.compy - 1]->GetPeice() == 'p')
							return true;
			}
		}
		else
		{
			if (KingLoc.compx != 0)
			{
				if (tempBoard[KingLoc.compx - 1][KingLoc.compy + 1] != nullptr)
					if (tempBoard[KingLoc.compx - 1][KingLoc.compy + 1]->GetColor() != kingColor)
						if (tempBoard[KingLoc.compx - 1][KingLoc.compy + 1]->GetPeice() == 'P')
							return true;
			}
		}
	}
	return false;
}
// check if the king is in danger from the king
bool Board::dangerFromKing(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard)
{	
	//check the row below the king
	for (int i= KingLoc.compy-1;i <KingLoc.compy+2;i++)
	{
		if(isExist(KingLoc.compx-1,i))
			if (tempBoard[KingLoc.compx - 1][i] != nullptr)
				if (tempBoard[KingLoc.compx - 1][i]->GetColor() != kingColor)
					if (tempBoard[KingLoc.compx - 1][i]->GetPeice() != 'k'||
						tempBoard[KingLoc.compx - 1][i]->GetPeice() != 'K')
						return true;
	}
	//check the row above the king
	for (int i = KingLoc.compy - 1; i < KingLoc.compy + 2; i++)
	{
		if (isExist(KingLoc.compx + 1, i))
			if (tempBoard[KingLoc.compx + 1][i] != nullptr)
				if (tempBoard[KingLoc.compx + 1][i]->GetColor() != kingColor)
					if (tempBoard[KingLoc.compx + 1][i]->GetPeice() != 'k' ||
						tempBoard[KingLoc.compx + 1][i]->GetPeice() != 'K')
						return true;
	}
	//check the row of the king
	for (int i = KingLoc.compy - 1; i < KingLoc.compy + 2; i+=2)
	{
		if (isExist(KingLoc.compx, i))
			if (tempBoard[KingLoc.compx][i] != nullptr)
				if (tempBoard[KingLoc.compx][i]->GetColor() != kingColor)
					if (tempBoard[KingLoc.compx][i]->GetPeice() != 'k' ||
												tempBoard[KingLoc.compx][i]->GetPeice() != 'K')
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
bool Board::isExist(int x, int y) {
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return false;
	return true;
}
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Peice.h"
#include "Loction.h"
class Peice;

using std::string;
using std::vector;
class Board
{
private:
	vector<Loction>locOfKings;// the location of the kings
	vector<vector<Peice*>> board;//all the board with the pieces
	Color turn = Color::White;// the turn of the player
	bool checkRes11(Loction loc);// check if the position is legal for response 11
	bool checkRes12(Loction loc);// check if the position is legal for response 12
	void replaceTurn();// replace the turn
	bool checkPosForRes13(Loction loc);// check if the position is legal for response 13
	bool checkIllegelMoveRes21(Loction loc, Loction sourceLoc);// check if the position is legal for response 21
	int checkChess(Loction loc, Loction sourceLoc);// check if the position is legal for response 31
	bool checkIfKingInDanger(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger
	bool dangerFromRookAndQueen(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger from rook or queen
	bool dangerFromBishopAndQueen(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger from bishop or queen
	bool dangerFromPawn(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger from pawn
	bool dangerFromKing(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);//check if the king is in danger from king
	bool dangerFromKnight(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger from knight
	void DoMove(Loction loc, Loction sourceLoc);// do the move
	Color GetTurn() { return turn; }// get the turn
	bool isExist(int x, int y);
public:
	auto operator[](int index) {return board[index].data();}// operator [][]
	Board(string boardString);// constructor
	int getResponse(string order);// get the response
	~Board();// destructor
};

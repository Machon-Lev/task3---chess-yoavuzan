#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Peice.h"
#include "Loction.h"
using std::string;
using std::vector;
class Board
{
private:
	vector<Loction>locOfKings;// the location of the kings
	vector<vector<Peice*>> board;//all the board with the pieces
	Color turn = Color::White;// the turn of the player
	vector <Loction>blackPiceLoc;// all the black pieces location
	vector <Loction>whitePiceLoc;// all the white pieces location
	bool checkPos(Loction loc);//check if the position is legal
	void replaceTurn();// replace the turn
	int createRes11or12(Loction loc);// create the response 11 or 12
	bool checkPosForRes13(Loction loc);// check if the position is legal for response 13
	bool checkIllegelMoveRes21(Loction loc, Loction sourceLoc);// check if the position is legal for response 21
	bool checkChess(Loction loc, Loction sourceLoc);// check if the position is legal for response 31
	bool checkMoveForPawn(int placex, int placey, int destinationx, int destinationy);// check if the position is legal for pawn
	bool checkMoveForKnight(int placex, int placey, int destinationx, int destinationy);// check if the position is legal for knight
	bool checkMoveForRook(int placex, int placey, int destinationx, int destinationy);// check if the position is legal for rook
	bool checkMoveForBishop(int placex, int placey, int destinationx, int destinationy);// check if the position is legal for bishop
	bool checkMoveForKing(int placex, int placey, int destinationx, int destinationy);// check if the position is legal for king
	bool checkIfKingInDanger(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger
	bool dangerFromRookAndQueen(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger from rook or queen
	bool dangerFromBishopAndQueen(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger from bishop or queen
	bool dangerFromPawn(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard);// check if the king is in danger from pawn
	bool dangerFromKing(int KingLocx, int KingLocy, Color kingColor, vector<vector<Peice*>> tempBoard);//check if the king is in danger from king
	void DoMove(Loction loc, Loction sourceLoc);// do the move
	Color GetTurn() { return turn; }// get the turn
public:
	Board(string boardString);// constructor
	int getResponse(string order);// get the response
	~Board();// destructor
};

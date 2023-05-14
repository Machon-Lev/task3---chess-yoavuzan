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
	vector<Loction>locOfKings;
	vector<vector<Peice*>> board;
	bool chess = false;
	Color turn = Color::White;
	vector <Loction>blackPiceLoc;
	vector <Loction>whitePiceLoc;
	bool checkPos(Loction loc);
	void replaceTurn();
	int createRes11or12(Loction loc);
	bool checkPosForRes13(Loction loc);
	bool checkIllegelMoveRes21(Loction loc, Loction sourceLoc);
	bool checkChess(Loction loc, Loction sourceLoc);
	bool checkMoveForRook(int placex, int placey, int destinationx, int destinationy);
	bool checkMoveForKing(int placex, int placey, int destinationx, int destinationy);
	bool checkIfKingInDanger(Loction KingLoc, Color kingColor, vector<vector<Peice*>> tempBoard);
	void DoMove(Loction loc, Loction sourceLoc);
public:
	Color GetTurn() { return turn; }
	Board(string boardString);
	bool isChess() { return chess; }
	int getResponse(string order);
	~Board();
};

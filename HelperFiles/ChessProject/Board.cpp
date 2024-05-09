#include "Board.h"

#include <iostream>
#include <string>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "NullPiece.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"


Board::Board(Player* white, Player* black) :
	_lastSrcRow(-1), _lastSrcCol(-1), _lastDstRow(-1), _lastDstCol(-1)
{
	_lastPiece = nullptr;

	_brd[0][0] = new Rook(white, 0, 0, this);
	_brd[0][7] = new Rook(white, 0, 7, this);
	_brd[7][7] = new Rook(black, 7, 7, this);
	_brd[7][0] = new Rook(black, 7, 0, this);

	_brd[0][1] = new Knight(white, 0, 1, this);
	_brd[0][6] = new Knight(white, 0, 6, this);
	_brd[7][1] = new Knight(black, 7, 1, this);
	_brd[7][6] = new Knight(black, 7, 6, this);

	_brd[0][2] = new Bishop(white, 0, 2, this);
	_brd[0][5] = new Bishop(white, 0, 5, this);
	_brd[7][2] = new Bishop(black, 7, 2, this);
	_brd[7][5] = new Bishop(black, 7, 5, this);

	_brd[0][4] = new Queen(white, 0, 4, this);
	_brd[7][4] = new Queen(black, 7, 4, this);

	_brd[0][3] = new King(white, 0, 3, this);
	_brd[7][3] = new King(black, 7, 3, this);

	for (int col = 0; col < BOARD_SIZE; col++)
	{
		_brd[1][col] = new Pawn(white, 1, col, this);
	}

	for (int col = 0; col < BOARD_SIZE; col++)
	{
		_brd[6][col] = new Pawn(black, 6, col, this);
	}

	for(int row = 2; row < 6; row++)
	{
		for(int col = 0; col < BOARD_SIZE; col++)
		{
			_brd[row][col] = new NullPiece(row, col);
		}
	}
}

Board::~Board()
{
	delete _lastPiece;
	_lastPiece = nullptr;

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			delete _brd[row][col];
			_brd[row][col] = nullptr;
		}
	}
}

void Board::print() const
{
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			std::cout << _brd[row][col]->getSign();
		}
		std::cout << std::endl;
	}
}

void Board::getString(char res[]) const
{
	std::string s = "";
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			res[row * BOARD_SIZE + col] = _brd[row][col]->getSign();
		}
	}
}

bool Board::isPieceOfPlayer(int row, int col, Player* pl) const
{
	return pl == _brd[row][col]->getPlayer();
}

bool Board::tryMove(int srcRow, int srcCol, int dstRow, int dstCol) const
{
	return _brd[srcRow][srcCol]->isLegalMove(dstRow, dstCol);
}

Piece** Board::getBoard() const
{
	return (Piece**)_brd;
}

void Board::Move(int srcRow, int srcCol, int dstRow, int dstCol)
{
	Piece* tmp;

	_lastSrcRow = srcRow;
	_lastSrcCol = srcCol;
	_lastDstRow = dstRow;
	_lastDstCol = dstCol;

	if (_lastPiece != nullptr)
	{
		delete _lastPiece;
		_lastPiece = nullptr;
	}

	if (_brd[dstRow][dstCol]->getPlayer() != NULL && _brd[dstRow][dstCol]->getPlayer() != _brd[srcRow][srcCol]->getPlayer())
	{
		tmp = new NullPiece(srcRow, srcCol);
		_lastPiece = _brd[dstRow][dstCol];

	} else
	{
		tmp = _brd[dstRow][dstCol];
	}

	_brd[dstRow][dstCol] = _brd[srcRow][srcCol];
	_brd[dstRow][dstCol]->setPosition(dstRow, dstCol);

	_brd[srcRow][srcCol] = tmp;
	_brd[srcRow][srcCol]->setPosition(srcRow, srcCol);
}

void Board::undoLastMove()
{
	if(_lastPiece == nullptr)
	{
		Move(_lastDstRow, _lastDstCol, _lastSrcRow, _lastSrcCol);
	} else
	{
		delete _brd[_lastSrcRow][_lastSrcCol];

		_brd[_lastSrcRow][_lastSrcCol] = _brd[_lastDstRow][_lastDstCol];
		_brd[_lastSrcRow][_lastSrcCol]->setPosition(_lastSrcRow, _lastSrcCol);

		_brd[_lastDstRow][_lastDstCol] = _lastPiece;
		_brd[_lastDstRow][_lastDstCol]->setPosition(_lastDstRow, _lastDstCol);
		_lastPiece = nullptr;
	}
}



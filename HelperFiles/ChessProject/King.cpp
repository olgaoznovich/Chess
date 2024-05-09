#include "King.h"

King::King(Player* p, int row, int col, Board* b) : Piece(p, 'k', row, col, b)
{
	p->setKing(this);
}


bool King::isLegalMove(int dstRow, int dstCol) const
{
	if (abs(dstRow - _row) > 1 || abs(dstCol - _col) > 1)
		return false;
	return isWayFree(dstRow, dstCol);
}

bool King::isChess()
{
	Piece** matBoard = _brd->getBoard();
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			Piece* currPiece = *(matBoard + row * BOARD_SIZE + col);

			if(currPiece->getPlayer() != NULL && currPiece->getPlayer() != _player)
			{
				if (currPiece->isLegalMove(_row, _col))
					return true;
			} 
		}
	}

    return false;
}

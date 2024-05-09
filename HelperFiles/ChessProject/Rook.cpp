#include "Rook.h"

Rook::Rook(Player* p, int row, int col, Board* b) :
	Piece(p, 'r', row, col, b)
{
}

bool Rook::isLegalMove(int dstRow, int dstCol) const
{
	if (dstRow != _row && dstCol != _col)
		return false;
	return isWayFree(dstRow, dstCol);
}

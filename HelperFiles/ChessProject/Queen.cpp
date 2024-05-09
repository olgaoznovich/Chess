#include "Queen.h"

Queen::Queen(Player* p, int row, int col, Board* b) :
	Piece(p, 'q', row, col, b)
{
}

bool Queen::isLegalMove(int dstRow, int dstCol) const
{
	if (abs(_row - dstRow) != abs(_col - dstCol) && dstRow != _row && dstCol != _col)
		return false;
	return isWayFree(dstRow, dstCol);
}

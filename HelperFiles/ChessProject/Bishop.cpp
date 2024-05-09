#include "Bishop.h"

Bishop::Bishop(Player* p, int row, int col, Board* b) :
	Piece(p, 'b', row, col, b)
{
}

bool Bishop::isLegalMove(int dstRow, int dstCol) const
{
	if ((abs(_row - dstRow) != abs(_col - dstCol)))
		return false;
	return isWayFree(dstRow, dstCol);
}

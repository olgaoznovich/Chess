#include "Knight.h"

Knight::Knight(Player* p, int row, int col, Board* b) :
	Piece(p, 'n', row, col, b)
{
}

bool Knight::isLegalMove(int dstRow, int dstCol) const
{
	return (abs(_row - dstRow) == 2 && abs(_col - dstCol) == 1) ||
		(abs(_row - dstRow) == 1 && abs(_col - dstCol) == 2);
}
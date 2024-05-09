#include "Pawn.h"

Pawn::Pawn(Player* p, int row, int col, Board* b) :
	Piece(p, 'p', row, col, b)
{
}

bool Pawn::isLegalMove(int dstRow, int dstCol) const
{
	int rowDiff = dstRow - _row;

	if (!_player->isWhite())
		rowDiff *= -1;

	bool singularMovement = rowDiff == 1;
	bool doubleMovement = _startRow == _row && rowDiff == 2;
	bool forwardMovement = (singularMovement || doubleMovement) && dstCol == _col;
	bool diagonalMovement = singularMovement && abs(dstCol - _col) == 1;
	bool otherPlayersPiece = !_brd->isPieceOfPlayer(dstRow, dstCol, _player) && !_brd->isPieceOfPlayer(dstRow, dstCol, NULL);

	forwardMovement = forwardMovement && _brd->isPieceOfPlayer(dstRow, dstCol, NULL);
	diagonalMovement = diagonalMovement && otherPlayersPiece;

	return (forwardMovement || diagonalMovement) && isWayFree(dstRow, dstCol);
}

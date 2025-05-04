#include "bishop.hh"
#include "move_utils.hh"

Bishop::Bishop(ChessColor col):
    ChessPiece(col, BISHOP, "bishop")
{
}

set<Coord> Bishop::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> validMoves;

    ChessMovesUtils::findDiagonalMoves(board, *this, validMoves);

    return validMoves;
}

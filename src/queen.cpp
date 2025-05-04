#include "queen.hh"
#include "move_utils.hh"

Queen::Queen(ChessColor col):
    ChessPiece(col, QUEEN, "queen")
{
}

set<Coord> Queen::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> validMoves;

    ChessMovesUtils::findStraightMoves(board, *this, validMoves);
    ChessMovesUtils::findDiagonalMoves(board, *this, validMoves);

    return validMoves;
}

#include "rook.hh"
#include "move_utils.hh"

Rook::Rook(ChessColor col):
    ChessPiece(col, ROOK, "rook")
{
}

set<Coord> Rook::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> validMoves;

    ChessMovesUtils::findStraightMoves(board, *this, validMoves);

    return validMoves;
}

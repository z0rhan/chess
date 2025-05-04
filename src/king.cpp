#include "king.hh"
#include "move_utils.hh"

King::King(ChessColor col):
    ChessPiece(col, KING, "king")
{
}

set<Coord> King::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> validMoves;

    ChessMovesUtils::findKingMoves(board, *this, validMoves);

    return validMoves;
}

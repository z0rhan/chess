#include "king.hh"
#include "move_utils.hh"
#include "rook.hh"

King::King(ChessColor col) : ChessPiece(col, KING, "king") {}

set<Coord> King::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> validMoves;
    auto [currentRow, currentCol] = get_position();

    const std::array<std::pair<int, int>, 8> c_directions = {{
        {1, 0},  // Down
        {0, 1},  // Right
        {-1, 0}, // Up
        {0, -1}, // Left
        {1, 1},  // Down-right
        {1, -1}, // Down-left
        {-1, 1}, // Up-right
        {-1, -1} // Up-left
    }};

    for (const auto &[dr, dc] : c_directions)
    {
        int newRow = currentRow + dr;
        int newCol = currentCol + dc;

        // No need for more checks
        check_move(board, {newRow, newCol}, validMoves);
    }

    addMovesForCastling(currentRow, currentCol, board, validMoves);

    return validMoves;
}

void King::check_move(const ChessBoard &board, const Coord &dest,
                      set<Coord> &moves) const
{
    if (board.coord_in_bounds(dest))
    {
        shared_ptr<ChessPiece> piece = board.get_piece_at(dest);
        if (piece == nullptr || piece->get_color() != get_color())
        {
            moves.insert(dest);
        }
    }
}

bool King::canCastleKingSide(int& row, int& col, const ChessBoard &board) const
{
    if (getMovesCount())
    {
        return false;
    }

    int rookRow = get_color() == ChessColor::WHITE ? BOARD_SIZE - 1 : 0;

    shared_ptr<ChessPiece> piece = board.get_piece_at({rookRow, BOARD_SIZE - 1});
    shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(piece);
    if (!rook || rook->get_color() != get_color() || rook->getMovesCount() > 0)
    {
        return false;
    }

    for (int tempCol = col + 1; tempCol < BOARD_SIZE; tempCol++)
    {
        shared_ptr<ChessPiece> piece = board.get_piece_at({row, tempCol});
        if (piece)
        {
            shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(piece);
            if (!rook)
            {
                return false;
            }
        }
    }

    return true;
}

bool King::canCastleQueenSide(int& row, int& col, const ChessBoard &board) const
{
    if (getMovesCount())
    {
        return false;
    }

    int rookRow = get_color() == ChessColor::WHITE ? BOARD_SIZE - 1 : 0;

    shared_ptr<ChessPiece> piece = board.get_piece_at({rookRow, 0});
    shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(piece);
    if (!rook || rook->get_color() != get_color() || rook->getMovesCount() > 0)
    {
        return false;
    }

    for (int tempCol = col - 1; tempCol >= 0; tempCol--) // To the left
    {
        shared_ptr<ChessPiece> piece = board.get_piece_at({row, tempCol});
        if (piece)
        {
            shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(piece);
            if (!rook)
            {
                return false;
            }
        }
    }

    return true;
}

void King::addMovesForCastling(int& row, int& col, const ChessBoard& board, set<Coord>& moves) const
{
    if (canCastleKingSide(row, col, board))
    {
        moves.insert({row, col + 2});
    }
    
    if (canCastleQueenSide(row, col, board))
    {
        moves.insert({row, col - 2});
    }
}

/* Author: Zorhan Salami
 * Email: zorhan.salami@tuni.fi
 *
 * I have changed the implementation of reset_board()
 * to setup chess piece in both way:
 * White/Black can be both up and down now
 */
#include "chess.hh"
#include "chesspiece.hh"

Chess::Chess() {}

void Chess::change_turn()
{
    current_turn_ = current_turn_ == WHITE ? BLACK : WHITE;
}

bool Chess::make_move(shared_ptr<ChessPiece> piece, Coord dest)
{
    // If game is not in progress, return
    if (game_state_ != IN_PROGRESS)
    {
        return false;
    }

    // If it's the wrong player's turn, return
    if (current_turn_ != piece->get_color())
    {
        return false;
    }

    // If the move is not allowed, don't make it.
    auto allowed_moves = piece->get_allowed_moves(board_);
    if (allowed_moves.find(dest) == allowed_moves.end())
    {
        return false;
    }

    // Try to make the move
    Move move = move_piece(piece->get_position(), dest);

    // If the move could not be made, stop here
    if (!move.moved)
    {
        return false;
    }

    // If the king was captured, the game ends
    if (move.captured_piece != nullptr and
        move.captured_piece->get_type() == KING)
    {
        game_state_ =
            move.captured_piece->get_color() == BLACK ? WHITE_WIN : BLACK_WIN;
    }

    // If a pawn was moved, check for promotion
    if (piece->get_type() == PAWN)
    {
        int row_to_reach = piece->get_color() == WHITE ? BOARD_SIZE - 1 : 0;
        if (piece->get_position().row == row_to_reach)
        {
            shared_ptr<Queen> promoted = make_shared<Queen>(piece->get_color());
            board_.set_piece(piece->get_position(), promoted);
            promoted->set_position(dest);
            piece->set_position(NULL_COORD);
        }
    }

    piece->increaseMovesCount();
    change_turn();
    return true;
}

Move Chess::move_piece(Coord src, Coord dest)
{
    Move move = {false, src, dest, nullptr, nullptr};

    // Check bounds
    if (not board_.coord_in_bounds(src) || not board_.coord_in_bounds(dest))
    {
        return move;
    }

    // Get the piece at the source, if one exists
    move.moved_piece = board_.get_piece_at(src);
    if (move.moved_piece == nullptr)
    {
        return move;
    }

    // Check for capture
    move.captured_piece = board_.get_piece_at(dest);

    castleIfNeeded(src, dest);

    // Move the piece
    set_piece(src, nullptr);
    set_piece(dest, move.moved_piece);
    move.moved = true;

    // Set the captured piece's position to null, since it is no longer on the
    // board
    if (move.captured_piece != nullptr)
    {
        move.captured_piece->set_position(NULL_COORD);
    }

    return move;
}

void Chess::castleIfNeeded(const Coord& src, const Coord& dest)
{
    shared_ptr<ChessPiece> piece = board_.get_piece_at(src);
    shared_ptr<King> king = dynamic_pointer_cast<King>(piece);

    if (!king)
    {
        return;
    }

    int row = get_current_turn() == ChessColor::WHITE ? BOARD_SIZE - 1 : 0;

    if (dest.col - src.col == 2)
    {
        shared_ptr<ChessPiece> rook = board_.get_piece_at({row, BOARD_SIZE - 1});
        set_piece({row, src.col + 1}, rook);
        set_piece({row, BOARD_SIZE - 1}, nullptr);
    }
    else if (src.col - dest.col == 2)
    {
        shared_ptr<ChessPiece> rook = board_.get_piece_at({row, 0});
        set_piece({row, src.col - 1}, rook);
        set_piece({row, 0}, nullptr);
    }
}

void Chess::set_piece(Coord coord, shared_ptr<ChessPiece> piece)
{
    if (board_.set_piece(coord, piece) && piece != nullptr)
    {
        piece->set_position(coord);
    }
}

void Chess::set_piece(int row, int col, shared_ptr<ChessPiece> piece)
{
    set_piece({row, col}, piece);
}

void Chess::start_game(ChessColor starting_player)
{
    current_turn_ = starting_player;
    game_state_ = IN_PROGRESS;
    reset_board();
}

void Chess::reset_board()
{
    // Clear all squares
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            set_piece(i, j, nullptr);
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        shared_ptr<Pawn> whitePawn = make_shared<Pawn>(ChessColor::WHITE);
        shared_ptr<Pawn> blackPawn = make_shared<Pawn>(ChessColor::BLACK);

        set_piece(1, i, blackPawn);
        set_piece(BOARD_SIZE - 2, i, whitePawn);
    }

    // KINGS
    set_piece(0, 4, make_shared<King>(ChessColor::BLACK));
    set_piece(BOARD_SIZE - 1, 4, make_shared<King>(ChessColor::WHITE));

    // QUEENS
    set_piece(0, 3, make_shared<Queen>(ChessColor::BLACK));
    set_piece(BOARD_SIZE - 1, 3, make_shared<Queen>(ChessColor::WHITE));

    // ROOKS
    set_piece(0, 0, make_shared<Rook>(ChessColor::BLACK));
    set_piece(0, BOARD_SIZE - 1, make_shared<Rook>(ChessColor::BLACK));
    set_piece(BOARD_SIZE - 1, 0, make_shared<Rook>(ChessColor::WHITE));
    set_piece(BOARD_SIZE - 1, BOARD_SIZE - 1,
              make_shared<Rook>(ChessColor::WHITE));

    // BISHOPS
    set_piece(0, 2, make_shared<Bishop>(ChessColor::BLACK));
    set_piece(0, BOARD_SIZE - 3, make_shared<Bishop>(ChessColor::BLACK));
    set_piece(BOARD_SIZE - 1, 2, make_shared<Bishop>(ChessColor::WHITE));
    set_piece(BOARD_SIZE - 1, BOARD_SIZE - 3,
              make_shared<Bishop>(ChessColor::WHITE));

    // KNIGHTS
    set_piece(0, 1, make_shared<Knight>(ChessColor::BLACK));
    set_piece(0, BOARD_SIZE - 2, make_shared<Knight>(ChessColor::BLACK));
    set_piece(BOARD_SIZE - 1, 1, make_shared<Knight>(ChessColor::WHITE));
    set_piece(BOARD_SIZE - 1, BOARD_SIZE - 2,
              make_shared<Knight>(ChessColor::WHITE));

    return;
}

ChessColor Chess::get_current_turn() const { return current_turn_; }

ChessBoard Chess::get_board() const { return board_; }

GameState Chess::get_game_state() const { return game_state_; }


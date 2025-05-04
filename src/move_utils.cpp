/*
 * Author: Zorhan Salami
 * Student Number: 153159921
 * Email: zorhan.salami@tuni.fi
 * ID: nkk362
 *
 * Description:
 * This implementation file defines the utility functions declared in the
 * ChessMovesUtils namespace. These functions are responsible for determining
 * the valid movement patterns for various chess pieces based on the current
 * state of the board. The logic accounts for board boundaries, piece colors,
 * and movement rules for specific pieces.
 *
 * Implemented Features:
 * - Diagonal move generation for bishops and queens.
 * - Straight move generation for rooks and queens.
 * - King move generation with basic constraints.
 * - General move validation utility to check destination legality.
 *
 * Notes:
 * These functions are intended to be called from within ChessPiece subclasses
 */

#include "move_utils.hh"
#include "chessboard.hh"

void ChessMovesUtils::findDiagonalMoves(const ChessBoard &board,
                                        const ChessPiece &currentPiece,
                                        set<Coord> &validMoves)
{
    auto [currentRow, currentCol] = currentPiece.get_position();

    for (int tempRow = currentRow + 1, tempCol = currentCol + 1;
         tempRow < BOARD_SIZE && tempCol < BOARD_SIZE;
         tempRow++, tempCol++)
    {
        if (!ChessMovesUtils::checkMove(board,
                                        currentPiece,
                                        {tempRow, tempCol},
                                        validMoves))
        {
            break;
        }
    }

    // Find all possible moves Down-left
    for (int tempRow = currentRow + 1, tempCol = currentCol - 1;
         tempRow < BOARD_SIZE && tempCol >= 0;
         tempRow++, tempCol--)
    {
        if (!ChessMovesUtils::checkMove(board,
                                        currentPiece,
                                        {tempRow, tempCol},
                                        validMoves))
        {
            break;
        }
    }

    // Find all possible moves Up-left
    for (int tempRow = currentRow - 1, tempCol = currentCol - 1;
         tempRow >= 0 && tempCol >= 0;
         tempRow--, tempCol--)
    {
        if (!ChessMovesUtils::checkMove(board,
                                        currentPiece,
                                        {tempRow, tempCol},
                                        validMoves))
        {
            break;
        }
    }

    // Find all possible moves Up-right
    for (int tempRow = currentRow - 1, tempCol = currentCol + 1;
         tempRow >= 0 && tempCol <= BOARD_SIZE;
         tempRow--, tempCol++)
    {
        if (!ChessMovesUtils::checkMove(board,
                                        currentPiece,
                                        {tempRow, tempCol},
                                        validMoves))
        {
            break;
        }
    }
}

void ChessMovesUtils::findStraightMoves(const ChessBoard &board,
                                        const ChessPiece &currentPiece,
                                        set<Coord> &validMoves)
{
    auto [currentRow, currentCol] = currentPiece.get_position();

    // Find all possible moves Down
   for (int tempRow = currentRow + 1;
        tempRow < BOARD_SIZE;
        tempRow++)
   {
        if (!ChessMovesUtils::checkMove(board,
                                        currentPiece,
                                        {tempRow, currentCol},
                                        validMoves))
        {
           break;
        }
   }

    // Find all possible moves Up
   for (int tempRow = currentRow - 1;
        tempRow >= 0;
        tempRow--)
   {
        if (!ChessMovesUtils::checkMove(board,
                                        currentPiece,
                                        {tempRow, currentCol},
                                        validMoves))
        {
           break;
        }
   }

    // Find all possible moves Right
   for (int tempCol = currentCol + 1;
        tempCol < BOARD_SIZE;
        tempCol++)
   {
       if (!ChessMovesUtils::checkMove(board,
                                       currentPiece,
                                       {currentRow, tempCol},
                                       validMoves))
       {
           break;
       }
   }

    // Find all possible moves Left
   for (int tempCol = currentCol - 1;
        tempCol >= 0;
        tempCol--)
   {
       if (!ChessMovesUtils::checkMove(board,
                                       currentPiece,
                                       {currentRow, tempCol},
                                       validMoves))
       {
           break;
       }
   }
}

void ChessMovesUtils::findKingMoves(const ChessBoard &board,
                                    const ChessPiece &currentPiece,
                                    set<Coord> &validMoves)
{
    auto [currentRow, currentCol] = currentPiece.get_position();

    const std::array<std::pair<int, int>, 8> c_directions = {{
        {1,0},  	// Down
        {0,1},  	// Right
        {-1,0}, 	// Up
        {0,-1}, 	// Left
        {1,1},  	// Down-right
        {1,-1}, 	// Down-left
        {-1,1}, 	// Up-right
        {-1,-1} 	// Up-left
    }};

    for (const auto& [dr, dc] : c_directions) {
        int newRow = currentRow + dr;
        int newCol = currentCol + dc;

        // No need for more checks
        ChessMovesUtils::checkMove(board,
                                   currentPiece,
                                   {newRow, newCol},
                                   validMoves);
    }

}

bool ChessMovesUtils::checkMove(const ChessBoard &board,
                                const ChessPiece &currentPiece,
                                const Coord &dest,
                                set<Coord> &validMoves)
{
    // Add the move, if the square is in bounds, it's empty or there is an enemy piece
    if (board.coord_in_bounds(dest))
    {
        shared_ptr<ChessPiece> piece = board.get_piece_at(dest);
        if (piece == nullptr)
        {
            validMoves.insert(dest);

            return true;
        }

        if (piece->get_color() != currentPiece.get_color()) {
            validMoves.insert(dest);

            return false;
        }
    }

    return false;
}

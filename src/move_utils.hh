/*
 * Author: Zorhan Salami
 * Student Number: 153159921
 * Email: zorhan.salami@tuni.fi
 * ID: nkk362
 *
 * Description:
 * This header file declares utility functions in the ChessMovesUtils namespace
 * that assist in calculating valid chess moves for different piece types.
 * These functions operate based on the current game state provided by the
 * ChessBoard and ChessPiece classes, helping to determine legal move positions
 * such as diagonals, straight lines, and king movements.
 *
 * Key Features:
 * - Computes legal diagonal and straight-line moves for pieces like bishops,
 *   rooks, and queens.
 * - Computes king-specific movement options.
 * - Validates whether a destination coordinate is a valid move.
 * - Designed to be used internally by ChessPiece subclasses for move logic.
 */
#pragma once

#include "chessboard.hh"
#include "chesspiece.hh"

#include <set>

namespace ChessMovesUtils {
    /**
     * @brief Find all possible diagonal moves from given position
     * @param board
     * @param currentRow
     * @param currentCol
     * @param validMoves
     */
    void findDiagonalMoves(const ChessBoard &board,
                           const ChessPiece &currentPiece,
                           set<Coord> &validMoves);

    /**
     * @brief Find all possible straight moves from given position
     * @param board
     * @param currentRow
     * @param currentCol
     * @param validMoves
     */
    void findStraightMoves(const ChessBoard &board,
                           const ChessPiece &currentPiece,
                           set<Coord> &validMoves);
    
    /**
     * @brief Find all possible moves for King ChessPiece from given position
     * @param board
     * @param currentRow
     * @param currentCol
     * @param validMoves
     */
    void findKingMoves(const ChessBoard &board,
                       const ChessPiece &currentPiece,
                       set<Coord> &validMoves);

    /**
     * @brief Check if the given move is valid or not
     * @param board
     * @param dest
     * @param validMoves
     */
    bool checkMove(const ChessBoard &board,
                   const ChessPiece &currentPiece,
                   const Coord &dest,
                   set<Coord> &validMoves);

}

/*
 * Author: Zorhan Salami
 * Student Number: 153159921
 * Email: zorhan.salami@tuni.fi
 * ID: nkk362
 *
 * I have made some modifications in sub-class Pawn
 * Introduced new enum class WhitePosition
 * Introduced new private member currentPosition which stores
 * enum class WhitePosition and helps to determine the direction
 * for get_allowed_moves() for pawn
 */

#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.hh"

/**
 * @brief The Pawn class
 * The pawn moves forward (only in the direction of the enemy's side) one square at a time.
 * The first time a pawn is moved from its starting position, it can move forward two squares.
 * The pawn captures by moving forward diagonally one square onto an enemy piece.
 */
class Pawn : public ChessPiece
{
public:
    Pawn(ChessColor col);
    virtual ~Pawn() = default;

    virtual set<Coord> get_allowed_moves(ChessBoard const& board) const override;

private:
};

#endif // PAWN_H

#pragma once
#include "../Piece.h"

///@brief  Representation of King.
class King : public Piece
{
private:
    /// @brief Name of type 'S'
    const char CharPieceType = 'K';
    PieceType name = KingT;

public:
    /**
    * @brief Gets possible moves from coordinates
    * @param MoveList reference to vector of possible moves, acts as return value.
    * @param  x X coordinate of piece
    * @param  y Y coordinate of piece.
    */
    void GetMoves(std::vector<Move> &MoveList, int x, int y) override;

    char GetPieceType() override;

    King(std::vector<Square> &BoardPtr);
    ~King();
};

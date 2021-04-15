#pragma once
#include "../Piece.h"

///@brief  Representation of Queen.
class Queen : public Piece
{
private:
    /// @brief Name of type 'S'
    const char CharPieceType = 'D';
    PieceType name = QueenT;

public:
    /**
    * @brief Gets possible moves from coordinates
    * @param MoveList reference to vector of possible moves, acts as return value.
    * @param  x X coordinate of piece
    * @param  y Y coordinate of piece.
    */
    void GetMoves(std::vector<Move> &MoveList, int x, int y) override;

    char GetPieceType() override;
    Queen(std::vector<Square> &BoardPtr);
    ~Queen();
};

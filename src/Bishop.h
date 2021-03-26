#pragma once
#include "Piece.h"

///@brief  Representation of Bishop.
class Bishop : public Piece
{
private:
    /// @brief Name of type 'S'
    const char CharPieceType = 'S';
	PieceType name = BishopT;
public:
	/**
    * @brief Gets possible moves from coordinates
    * @param MoveList reference to vector of possible moves, acts as return value.
    * @param  x X coordinate of piece
    * @param  y Y coordinate of piece.
    */
	void GetMoves(std::vector<Move>& MoveList, int x, int y) override;
	/**
    * @brief Returns piece type
    * @return char 'S'.
    */
	char GetPieceType() override;

	Bishop( std::vector<Square>& BoardPtr );
	~Bishop();

};


#pragma once
#include "../Piece.h"

///@brief  Representation of Rook.
class Rook : public Piece
{
private:
    /// @brief Name of type 'S'	
        const char CharPieceType = 'V';
		PieceType name = RookT;
public:
		/**
    * @brief Gets possible moves from coordinates
    * @param MoveList reference to vector of possible moves, acts as return value.
    * @param  x X coordinate of piece
    * @param  y Y coordinate of piece.
    */
	void GetMoves(std::vector<Move>& MoveList, int x, int y) override;

	Rook(  std::vector<Square>& BoardPtr );
	~Rook();
	char GetPieceType() override;

};


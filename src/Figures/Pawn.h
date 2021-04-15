#pragma once
#include "../Piece.h"
#include "../Square.h"
#include <iostream> 
#include <list> 
#include <vector>
#include <map>
#include <string>
#include <stdlib.h> 

///@brief  Representation of Pawn.
class Pawn : public Piece
{
private:
    /// @brief Name of type 'S'	
    const char CharPieceType = 'p';
	PieceType name = PawnT;
public:
	/**
    * @brief Gets possible moves from coordinates
    * @param MoveList reference to vector of possible moves, acts as return value.
    * @param  x X coordinate of piece
    * @param  y Y coordinate of piece.
    */
	void GetMoves( std::vector<Move>& MoveList, int x, int y) override;
	void PrintName();


	char GetPieceType() override ;
	
	Pawn( std::vector<Square>& BoardPtr );
	~Pawn();

};


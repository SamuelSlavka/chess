#include "Piece.h"

/**
 * Representation of piece expanded by specific types.
 * @brief Source file for Piece
 * @file Piece.cpp
 * @author Samuel Slavka (xslavk02)
 */

bool Piece::CheckBounds( int x, int y) const {
    return (x < 8 && y < 8 && x >= 0 && y >= 0);
};

PieceColor Piece::GetColour() const {
	return color;
};

void Piece::SetColour( PieceColor col ) {
	color = col;
};

const std::vector<Square>& Piece::GetBoard() const {
	return board;
};

const Piece& Piece::GetPiece( int x, int y) const {
	return *(GetBoard()[x+y*8].piece);
};

const Square& Piece::GetSquare( int x, int y) const {
	return GetBoard()[x+y*8];
};


Move Piece::SetMove(int fromx, int fromy, int tox, int toy, bool removes)
{
	Move move;
	move.FromX = fromx;
	move.FromY = fromy;
	move.ToX = tox;
	move.ToY = toy;
	move.Moved = GetBoard()[fromx+fromy*8].piece;
	if (removes) move.Removed = GetBoard()[tox+toy*8].piece;
    move.Removes = removes;
	return move;
};


Piece::Piece( std::vector<Square>& BoardPtr ) : board(BoardPtr) {};


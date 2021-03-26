#pragma once

#include "Headers.h"
#include "Square.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"
#include "King.h"

#include <iostream> 
#include <array> 
#include <vector>
#include <map>
#include <string>
#include <stdlib.h> 
#include <memory>

#include <boost/array.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>

///@brief  Game Board with 64 Squares.
class Board 
{
private: 
    /// @brief Pointer to Square with White King
    Square* WhiteKing;
    /// @brief Pointer to Square with Black King
    Square* BlackKing;

    /// @brief coonst value 8 width of board
    const int BOARDWIDTH{8};
    /// @brief const value 64 size of board
    const int BOARDSIZE{64};

public:
    /// @brief Vector containing Squares forming board.
	std::vector<Square> board;

    /**
    * @brief Initialize new Board.
    */
	int StartInitBoard();
	
    /**
    * @brief Removes piece from Board.
    * @param piece Pointer to input Piece object.
    * @return int Value of piece.
    */
	int RemovePiece(Piece *piece);
    
    /**
    * @brief Sets Piece on Board.
    * @param value Type of  piece.
    * @param  x X coordinate of piece
    * @param  y Y coordinate of piece.
    * @return int Value of piece.
    */
	int SetPiece(int value, int x, int y);
     
    /**
    * @brief Moves Piece on Board.
    * @param move Reference to move structure.
    */
	void MovePiece(Move& move);

    /**
    * @brief Reverses move.
    * @param move Reference to move structure.
    */
    void UnMovePiece(Move& move);


    /**
    * @brief Checks if move causes check.
    */
    char CheckCheck();

    /**
    * @brief Checks if x,y point to board.
    * @param x Coordinate x.
    * @param y Coordinate y.
    * @return true if x,y at board.
    */
    bool CheckBounds( int x, int y);

    /**
    * @brief Return pointer to Square in board.
    * @param x Coordinate x.
    * @param y Coordinate y.
    * @return Pointer to Square
    */
	Square GetSquare(int x, int y);

    /**
    * @brief Moves Kings.
    * @param un True if reversing move false if regular move.
    * @param move Reference to Move.
    */
    void UpdateKing(bool un, Move& move );

    /**
    * @brief Sets Kings special pointer.
    * @param turn King color.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    */
    void SetKing( PieceColor turn , int x, int y );

	Board();
	~Board();
};


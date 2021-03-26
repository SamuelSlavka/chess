#include "Pawn.h"

/**
 * Representation of Pawn.
 * @brief Source file for Pawn
 * @file Pawn.cpp
 * @author Samuel Slavka (xslavk02)
 */

void Pawn::PrintName()
{
    std::cout << name;
}

void Pawn::GetMoves( std::vector<Move>& MoveList, int x, int y ) 
{
    PieceColor col = GetPiece( x,y ).GetColour();

    if( GetSquare( x,y ).Used )
    {
        if ( CheckBounds( x,y+1*col ) && !GetSquare( x,y+1*col ).Used )
        {
            //one step forward
            MoveList.push_back( SetMove( x,y,x,y+1*col,false ) );
            //two steps forward
            if ( CheckBounds( x,y+2*col ) && (( y == 1 && col == white ) || ( y == 6 && col == black )) && !GetSquare( x,y+2*col ).Used )
                MoveList.push_back( SetMove( x,y,x,y+2*col,false ) );
        }

        if ( CheckBounds( x+1*col,y+1*col ) && GetSquare( x+1*col,y+1*col ).Used )
        {	//left remove
            if ( GetSquare( x+1*col,y+1*col ).piece->GetColour() != col )
                MoveList.push_back( SetMove( x,y,x+1*col,y+1*col,true ) );
        }
        if ( CheckBounds( x-1*col,y+1*col ) && GetSquare( x-1*col,y+1*col ).Used )
        {	//right remove
            if ( GetSquare( x-1*col,y+1*col ).piece->GetColour() != col )
                MoveList.push_back( SetMove( x,y,x-1*col,y+1*col,true ) );
        };
    };
};


char Pawn::GetPieceType()
{
    return CharPieceType;
};


Pawn::Pawn( std::vector<Square>& BoardPtr ) : Piece(BoardPtr)
{
}

Pawn::~Pawn()
{
}


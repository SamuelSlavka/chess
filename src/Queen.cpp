#include "Queen.h"

/**
 * Representation of Queen.
 * @brief Source file for Queen
 * @file Queen.cpp
 * @author Samuel Slavka (xslavk02)
 */

void Queen::GetMoves(std::vector<Move>& MoveList, int x, int y) 
{
	PieceColor col = GetPiece( x,y ).GetColour();

	std::vector<int> const av{ 0,0,1,-1,1,1,-1,-1 };
    std::vector<int> const bv{ 1,-1,0,0,1,-1,1,-1 };
	for (auto const& tmp : boost::combine(av, bv)) {
        bool rmvflag = false;
        int a,b;
		boost::tie(a,b) = tmp;
		for ( int i = 1; CheckBounds(x+a*i,y+b*i); ++i ) {
            rmvflag = false;
			if (  CheckBounds(x+a*i,y+b*i) && ((!GetSquare( x+a*i,y+b*i ).Used || GetSquare( x+a*i,y+b*i ).piece->GetColour() != col)) )
			{
				if ( GetSquare( x+a*i,y+b*i ).Used ) 
					rmvflag = ( GetSquare( x+a*i,y+b*i ).piece->GetColour() != col);

				MoveList.push_back( SetMove( x,y,x+a*i,y+b*i, rmvflag ) );
				if (rmvflag) break;
			}
			else break;
		};
	};
};

char Queen::GetPieceType()
{
	return CharPieceType;
};

Queen::Queen( std::vector<Square>& BoardPtr ) : Piece(BoardPtr)
{
}

Queen::~Queen()
{
}


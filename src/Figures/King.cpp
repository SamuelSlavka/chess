#include "King.h"

/**
 * Representation of King.
 * @brief Source file for King
 * @file King.cpp
 * @author Samuel Slavka (xslavk02)
 */

void King::GetMoves(std::vector<Move> &MoveList, int x, int y)
{
	PieceColor col = GetPiece(x, y).GetColour();

	std::vector<int> const av{0, 0, 1, -1, 1, 1, -1, -1};
	std::vector<int> const bv{1, -1, 0, 0, 1, -1, 1, -1};

	for (auto const &tmp : boost::combine(av, bv))
	{
		bool rmvflag = false;
		int a, b;
		boost::tie(a, b) = tmp;
		if (CheckBounds(x + a, y + b) && (!GetSquare(x + a, y + b).Used || GetSquare(x + a, y + b).piece->GetColour() != col))
		{
			if (GetSquare(x + a, y + b).Used)
				rmvflag = (GetSquare(x + a, y + b).piece->GetColour() != col);
			MoveList.push_back(SetMove(x, y, x + a, y + b, rmvflag));
		};
	};
};

char King::GetPieceType()
{
	return CharPieceType;
};

King::King(std::vector<Square> &BoardPtr) : Piece(BoardPtr)
{
}

King::~King()
{
}

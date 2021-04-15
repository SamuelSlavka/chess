#include "Knight.h"

/**
 * Representation of Knight.
 * @brief Source file for Knight
 * @file Knight.cpp
 * @author Samuel Slavka (xslavk02)
 */

void Knight::GetMoves(std::vector<Move> &MoveList, int x, int y)
{
    PieceColor col = GetPiece(x, y).GetColour();
    for (auto const &tmp : boost::combine(KnightMoveVectorA, KnightMoveVectorB))
    {
        bool rmvflag = false;
        int a, b;
        boost::tie(a, b) = tmp;

        if (CheckBounds(x + a, y + b) && ((!GetSquare(x + a, y + b).Used || GetSquare(x + a, y + b).piece->GetColour() != col)))
        {
            bool used = GetSquare(x + a, y + b).Used;
            if (used)
                rmvflag = true;
            MoveList.push_back(SetMove(x, y, x + a, y + b, rmvflag));
        };
    };
};

char Knight::GetPieceType()
{
    return CharPieceType;
};

Knight::Knight(std::vector<Square> &BoardPtr) : Piece(BoardPtr)
{
}

Knight::~Knight()
{
}

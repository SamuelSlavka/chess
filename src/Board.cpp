#include "Board.h"

/**
 * Representation of Board.
 * @brief Source file for Board
 * @file board.cpp
 * @author Samuel Slavka (xslavk02)
 */

bool Board::CheckBounds(int x, int y)
{
    return (x < 8 && y < 8 && x >= 0 && y >= 0) ? true : false;
};

void Board::SetKing(PieceColor turn, int x, int y)
{
    if (turn == white)
        WhiteKing = &(board.at(static_cast<size_t>(x + y * 8)));
    else
        BlackKing = &(board.at(static_cast<size_t>(x + y * 8)));
}

Square Board::GetSquare(int x, int y)
{
    if (CheckBounds(x, y))
        return board.at(static_cast<size_t>(x + y * BOARDWIDTH));
    Square sq = Square(-1, -1);
    return sq;
};

char Board::CheckCheck()
{
    int x = BlackKing->x;
    int y = BlackKing->y;
    char colr = 'B';

    for (int j = 0; j < 2; j++)
    {
        if (GetSquare(x, y).Used)
        {
            //checking for knights
            for (auto const &tmp : boost::combine(KnightMoveVectorA, KnightMoveVectorB))
            {
                int a, b;
                boost::tie(a, b) = tmp;

                if (CheckBounds(x + a, y + b) && GetSquare(x + a, y + b).Used)
                {
                    if (GetSquare(x + a, y + b).piece->GetPieceType() == 'J')
                    {
                        PieceColor pcolr = GetSquare(x + a, y + b).piece->GetColour();
                        if ((colr == 'W' && pcolr == black) || (colr == 'B' && pcolr == white))
                            return colr;
                    }
                }
            };

            //check all other types
            for (auto const &tmp : boost::combine(AllMoveVectorA, AllMoveVectorB))
            {
                int a, b;
                boost::tie(a, b) = tmp;
                for (int i = 1; CheckBounds(x + a * i, y + b * i); ++i)
                {
                    if (GetSquare(x + a * i, y + b * i).Used)
                    {
                        if (GetSquare(x + a * i, y + b * i).piece->GetColour() != GetSquare(x, y).piece->GetColour())
                        {
                            std::vector<Move> moves;
                            GetSquare(x + a * i, y + b * i).piece->GetMoves(moves, x + a * i, y + b * i);
                            auto it = std::find_if(moves.begin(), moves.end(),
                                                   ((boost::bind(&Move::ToX, _1) == x) && (boost::bind(&Move::ToY, _1) == y)));
                            if (it != moves.end())
                            {
                                GetSquare(x, y).piece->GetMoves(moves, x, y);
                                if (moves.empty())
                                    return 'M';
                                return colr;
                            }
                            else
                                break;
                        };
                    };
                };
            };
        };
        colr = 'W';
        x = WhiteKing->x;
        y = WhiteKing->y;
    };
    return 'n';
};

void Board::UpdateKing(bool un, Move &move)
{
    int x = move.ToX;
    int y = move.ToY * 8;
    if (!un)
    {
        x = move.FromX;
        y = move.FromY * 8;
    }

    if (move.Moved->GetColour() == white)
        WhiteKing = &board.at(static_cast<size_t>(x + y));
    else
        BlackKing = &board.at(static_cast<size_t>(x + y));
}

void Board::UnMovePiece(Move &move)
{
    if (move.Moved->GetPieceType() == 'K')
        UpdateKing(false, move);

    if (move.Promoted)
    {
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).piece = std::make_shared<Pawn>(board);
        move.Moved = board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).piece;
    }
    else
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).piece = move.Moved;
    board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).Used = true;

    if (move.Removes)
    {
        board.at(static_cast<size_t>(move.ToX + move.ToY * 8)).piece = move.Removed;
        board.at(static_cast<size_t>(move.ToX + move.ToY * 8)).Used = true;
    }
    else
    {
        board.at(static_cast<size_t>(move.ToX + move.ToY * 8)).piece = nullptr;
        board.at(static_cast<size_t>(move.ToX + move.ToY * 8)).Used = false;
    }
}

void Board::MovePiece(Move &move)
{
    if (move.Castle)
    {
    }
    else if (move.Promoted)
    {
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).piece = nullptr;
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).piece = std::make_shared<Queen>(board);
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).piece->SetColour(move.Moved->GetColour());
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).Used = false;
        board.at(static_cast<size_t>(move.ToX + move.ToY * 8)).Used = true;
    }
    else
    {
        if (move.Moved->GetPieceType() == 'K')
            UpdateKing(true, move);
        board.at(static_cast<size_t>(move.ToX + move.ToY * 8)).piece = move.Moved;
        board.at(static_cast<size_t>(move.ToX + move.ToY * 8)).Used = true;
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).piece = nullptr;
        board.at(static_cast<size_t>(move.FromX + move.FromY * 8)).Used = false;
    }
};

int Board::StartInitBoard()
{
    for (int i = 0; i < BOARDWIDTH; ++i)
    {
        board.at(size_t(i + 8)).piece = std::make_shared<Pawn>(board);
        board.at(size_t(i + 8 * 6)).piece = std::make_shared<Pawn>(board);
    };

    board[0 + 0].piece = std::make_shared<Rook>(board);
    board[7 + 0].piece = std::make_shared<Rook>(board);
    board[0 + 8 * 7].piece = std::make_shared<Rook>(board);
    board[7 + 8 * 7].piece = std::make_shared<Rook>(board);

    board[1 + 0].piece = std::make_shared<Knight>(board);
    board[6 + 0].piece = std::make_shared<Knight>(board);
    board[1 + 8 * 7].piece = std::make_shared<Knight>(board);
    board[6 + 8 * 7].piece = std::make_shared<Knight>(board);

    board[2 + 0].piece = std::make_shared<Bishop>(board);
    board[5 + 0].piece = std::make_shared<Bishop>(board);
    board[2 + 8 * 7].piece = std::make_shared<Bishop>(board);
    board[5 + 8 * 7].piece = std::make_shared<Bishop>(board);

    board[3 + 0].piece = std::make_shared<King>(board);
    board[4 + 0].piece = std::make_shared<Queen>(board);
    board[3 + 8 * 7].piece = std::make_shared<King>(board);
    board[4 + 8 * 7].piece = std::make_shared<Queen>(board);

    for (int i = 0; i < 16; ++i)
    {
        board.at(size_t(i)).piece->SetColour(white);
        board.at(size_t(i)).Used = true;
    }

    for (int i = 8 * 6; i < BOARDSIZE; ++i)
    {
        board.at(size_t(i)).piece->SetColour(black);
        board.at(size_t(i)).Used = true;
    }

    return 0;
};

Board::Board()
{
    for (int i = 0; i < BOARDSIZE; ++i)
    {
        Square sq = Square(i - (i / 8) * 8, i / 8);
        board.push_back(sq); //todo smart pointers
    }
    WhiteKing = &(board[3 + 0]);
    BlackKing = &(board[3 + 8 * 7]);
}

Board::~Board()
{
}

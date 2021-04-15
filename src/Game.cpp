#include "Game.h"

/**
 * Handles single instance of game.
 * @brief Source file for Game
 * @file Game.cpp
 * @author Samuel Slavka (xslavk02)
 */

//initialize new board
void Game::NewInit()
{
    board.StartInitBoard();
    log = std::make_shared<Log>(board.board); //TODO loading init saving init etc...
};

std::shared_ptr<Piece> Game::GetPiece(int x, int y)
{
    return board.board[x + y * 8].piece;
}

//make a move from PossibleMoves
void Game::MakeMove(int x, int y)
{
    auto it = std::find_if(PossibleMoves.begin(), PossibleMoves.end(),
                           ((boost::bind(&Move::ToX, _1) == x) && (boost::bind(&Move::ToY, _1) == y)));
    if (it == PossibleMoves.end())
    {
        PossibleMoves.clear();
        return;
    };

    it->Order = static_cast<int>(MoveList.size()) + 1;

    MoveList.push_back(it->Moved->SetMove(it->FromX, it->FromY, it->ToX, it->ToY, it->Removes));

    if (it->Moved->GetPieceType() == 'K')
        board.SetKing(Turn, it->ToX, it->ToY);

    board.MovePiece(*it);

    PossibleMoves.clear();
    char check = it->Chess;

    check = board.CheckCheck();

    if (check != 'n')
    {
        if (check == 'M')
            MoveList.back().Mat = it->Mat = true;
        else
            MoveList.back().Chess = it->Chess = true;
    }

    log->MoveToNotation(*it);

    SwitchTurn();
};

//check if piece is on spot
bool Game::IsUsed(int x, int y)
{
    return board.GetSquare(x, y).Used;
};

//make already created move
void Game::MakeMove(int index)
{
    Move &move = MoveList.at(index);

    if (move.Moved->GetPieceType() == 'K')
        board.SetKing(Turn, move.ToX, move.ToY);

    board.MovePiece(move);
    SwitchTurn();
}

//unmake already created move
void Game::UnMakeMove(int index)
{
    Move &move = MoveList.at(index);

    if (move.Moved->GetPieceType() == 'K')
        board.SetKing(Turn, move.FromX, move.FromY);

    board.UnMovePiece(move);
    SwitchTurn();
}

void Game::ClearMoveList(int index)
{
    if (index < MoveListLength())
        for (auto it = MoveList.begin() + index; it < MoveList.end();)
            MoveList.erase(it);
}

char Game::GetPieceColor(int x, int y)
{
    if (board.board[static_cast<size_t>(x + y * 8)].piece->GetColour() == white)
        return 'W';
    else
        return 'B';
}
char Game::GetPieceType(int x, int y)
{
    return board.board[static_cast<size_t>(x + y * 8)].piece->GetPieceType();
}

//unmove test move piece
void Game::UnMakeTestMove(Move move)
{
    board.UnMovePiece(move);
};
//test move piece for checking check
void Game::MakeTestMove(Move move)
{
    board.MovePiece(move);
};

//asigns moves to PossibleMoves
void Game::GetMoves(int x, int y)
{
    if (!MoveList.empty())
        if (MoveList.back().Mat)
        {
            std::cout << "Game Over" << std::endl;
            return;
        }

    if (board.GetSquare(x, y).Used)
    {
        if (GetTurn() == board.GetSquare(x, y).piece->GetColour())
            board.GetSquare(x, y).piece->GetMoves(PossibleMoves, x, y);
        if (!PossibleMoves.empty())
            RemoveGettingCheckMoves();
    }
    else if (!PossibleMoves.empty())
        PossibleMoves.clear();

    if (!MoveList.empty())
        if (MoveList.back().Chess)
        {
            if (!PossibleMoves.empty())
                RemoveNonCheckMoves();
        }
};

void Game::RemoveGettingCheckMoves()
{
    for (auto it = PossibleMoves.begin(); it != PossibleMoves.end();)
    {
        MakeTestMove(*it);
        char flag = 'n';

        flag = board.CheckCheck();

        UnMakeTestMove(*it);
        if ((flag == 'W' && Turn == white) || (flag == 'B' && Turn == black) || (flag != 'n' && it->Moved->GetPieceType() == 'K'))
            it = PossibleMoves.erase(it);
        else
            it++;
    }
}

void Game::RemoveNonCheckMoves()
{
    for (auto it = PossibleMoves.begin(); it != PossibleMoves.end();)
    {
        MakeTestMove(*it);
        char flag = 'n';

        flag = board.CheckCheck();

        UnMakeTestMove(*it);
        if (flag != 'n')
            it = PossibleMoves.erase(it);
        else
            it++;
    }
}

//get last line of notation
std::string Game::GetNotationLine()
{
    return log->GetNotation();
};

int Game::MoveListLength()
{
    return MoveList.size();
};

void Game::MoveListPopback()
{
    MoveList.pop_back();
}

void Game::ClearOneMoveNotation()
{
    log->ClearOneMove();
}
void Game::ClearNotation()
{
    log->ClearTempNoation();
}

//After opening parse one line and add to vector
bool Game::ParseNotation(std::vector<Move> &moves, std::string line)
{
    return log->NotationToMove(*this, moves, line);
}
//make move from MoveList vector while opening
void Game::MakeMovesOpen(std::vector<Move> &moves)
{
    for (auto it = moves.begin(); it != moves.end(); ++it)
    {
        GetMoves(it->FromX, it->FromY);
        MakeMove(it->ToX, it->ToY); // todo check success of move
    }
}

//TURN fnc
void Game::SwitchTurn()
{
    (Turn == white) ? Turn = black : Turn = white;
};
void Game::SetWhiteTurn()
{
    Turn = white;
}
PieceColor Game::GetTurn()
{
    return Turn;
};

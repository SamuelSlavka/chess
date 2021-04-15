#pragma once
#include "Board.h"
#include "Piece.h"
#include "Log.h"
#include <iostream>
#include <list>
#include <iterator>

#include <boost/array.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <string>
#include <stdlib.h>
#include <memory>

class Log;
///@brief  Single instance of Game.
class Game
{
private:
    /// @brief Current turn in game.
    PieceColor Turn = white;
    /// @brief List of all moves in game.
    std::vector<Move> MoveList;
    /// @brief Instance of Board.
    Board board;
    /// @brief Instance of Log.
    std::shared_ptr<Log> log;

public:
    /// @brief temporary vector of possible moves from selected square.
    std::vector<Move> PossibleMoves;

    /**
    * @brief Returns Piece pointer.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    * @return std::shared_ptr<Piece>  ppiece pointer
    */
    std::shared_ptr<Piece> GetPiece(int x, int y);

    ///@brief Switches turn color.
    void SwitchTurn();

    ///@brief Sets white turn color.
    void SetWhiteTurn();

    /// @brief Switches turn color.
    PieceColor GetTurn();

    ///@brief Removes moves that dont prevent check when in check.
    void RemoveNonCheckMoves();

    ///@brief  Removes moves leading to check from PossibleMoves vec.
    void RemoveGettingCheckMoves();

    /**
    * @brief Puts all possible moves to PossibleMoves vector.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    */
    void GetMoves(int x, int y);

    /**
    * @brief Make move From PossibleMoves
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    */
    void MakeMove(int x, int y);

    /**
    * @brief Remove elements after index from movelist.
    * @param index
    */
    void ClearMoveList(int index);
    ///@brief pop last element from MoveList
    void MoveListPopback();
    /**
    * @brief Unmakes one move for shift l
    * @param index
    */
    void UnMakeMove(int index);
    /**
    * @brief Makes move by index for shift r.
    * @param index
    */
    void MakeMove(int index);

    /**
    * @brief For testing Check and legality of move
    * @param move move
    */
    void MakeTestMove(Move move);
    /**
    * @brief Reverses test move.
    * @param move move
    */
    void UnMakeTestMove(Move move);

    /**
    * @brief Checks if Square has piece.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    * @return true if used.
    */
    bool IsUsed(int x, int y);

    ///@breif returns last line of Notation
    ///@return string last line
    std::string GetNotationLine();
    ///@brief clears whole notation from Log.
    void ClearNotation();
    ///@brief clears just lastline from notation from Log.
    void ClearOneMoveNotation();

    /**
    * @brief Open SavedGame.
    * @param moves vector of moves acts as return value.
    *@ param line string to parse
    */
    bool ParseNotation(std::vector<Move> &moves, std::string line);

    /**
    * @brief Make opened game moves.
    * @param moves vector of moves to make.
    */
    void MakeMovesOpen(std::vector<Move> &moves);
    ///@brief NEW GAME
    void NewInit();

    /**
    * @brief Returns Piece color.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    * @return char Piece color 'w' as white 'b' as black.
    */
    char GetPieceColor(int x, int y);

    /**
    * @brief Returns Piece type.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    * @return Char type of piece.
    */
    char GetPieceType(int x, int y);

    /// @brief Returns MoveListLength.
    int MoveListLength();
};

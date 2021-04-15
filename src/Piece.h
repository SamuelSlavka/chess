#pragma once

#include "Square.h"
#include "Headers.h"

#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <stdlib.h>

#include <boost/array.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>

enum PieceColor
{
    black = -1,
    white = 1
};

struct Move;
class Square;

///@brief  Representation of Piece.
class Piece
{
private:
    /// @brief Name of type 'S'
    const char CharPieceType = 'n';
    /// @brief Reference to board.
    const std::vector<Square> &board;
    /// @brief Piece color.
    PieceColor color;
    /// @True if moved used for Castle.
    bool Moved;

public:
    /// @brief  Returns reference to board.
    /// @return std::vector<Square>&  Reference to Board.
    const std::vector<Square> &GetBoard() const;
    //retruns ref to Piece
    /**
    * @brief Retruns ref to Piece.
    * @param  x X coordinate.
    * @param  y Y coordinate.
    * @ return Piece reference.
    */
    const Piece &GetPiece(int x, int y) const;
    /**
    * @brief Retruns reference to Square.
    * @param  x X coordinate.
    * @param  y Y coordinate.
    * @ return Square reference.
    */
    const Square &GetSquare(int x, int y) const;

    /**
    * @brief Checks bounds of board.
    * @param  x X coordinate.
    * @param  y Y coordinate.
    * @ return bool True if inbounds.
    */
    bool CheckBounds(int x, int y) const;

    /// @brief sets Piece color
    void SetColour(PieceColor col);
    /// @return PieceColor
    PieceColor GetColour() const;

    /// @brief retruns type of piece
    virtual char GetPieceType() { return CharPieceType; }

    /**
    * @brief Vitrual finction retruning moves for each Piece differently.
    * @param MoveList reference to vector of possible moves, acts as return value.
    * @param  x X coordinate of piece
    * @param  y Y coordinate of piece.
    */
    virtual void GetMoves(std::vector<Move> &, int, int) {}

    /**
    * @brief Creates Move and sets unique pointers to Pieces.
    * @param  fromx X coordinate of piece.
    * @param  fromy Y coordinate of piece.
    * @param  tox X coordinate.
    * @param  toy Y coordinate.
    * @param removes flag of removing.
    * @return Move New initialised move.
    */
    Move SetMove(int fromx, int fromy, int tox, int toy, bool removes);

    Piece();
    Piece(std::vector<Square> &BoardPtr);
};

/// @brief Structure containing single move
struct Move
{
    /// @brief From x.
    int FromX;
    /// @brief From y.
    int FromY;
    /// @brief To x.
    int ToX;
    /// @brief To y.
    int ToY;
    /// @brief Flag removing.
    bool Removes = false;
    /// @brief Flag promotion.
    bool Promoted = false; //todo
    /// @brief Flag elpawn.
    bool ElPawn = false; //todo
                         /// @brief Flag castle.
    bool Castle = false; //todo

    /// @brief Flag chess.
    bool Chess = false;
    /// @brief Flag mate.
    bool Mat = false;

    /// @brief Order or move in game.
    int Order = -1;
    /// @brief Pointer to piece moved.
    std::shared_ptr<Piece> Moved;
    /// @brief Pointer to piece removed.
    std::shared_ptr<Piece> Removed;
};

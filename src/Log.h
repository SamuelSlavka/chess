#pragma once

#include <iostream>
#include <string>
#include <regex>
#include "Piece.h"
#include "Game.h"

#include <boost/array.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>

class Game;

///@brief  Creates and parses notation.
class Log
{
private:

    /// @brief Reference to board.
	const std::vector<Square>& board;
    /// @brief Log of one Turn.
	std::string NotationLog;
    /// @brief Tmp variable.
    std::vector<Move> move2;
    /// @brief  Type of notation long/short/notype.
    NotationType notation = notype;

public:

    /**
    * @brief Checks in short notation for conflicting pieces.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    * @param ptype Type of piece.
    * @return char  piece color
    */
	char HasNeighbours( int x, int y, char ptype );

    /**
    * @brief Parses notation and calls notationtomoveshort or notationtomovelong
    * @param game Reference to game for access to board.
    * @param move vector of moves acting as return value.
    * @param strmove String which is parsed.
    * @return bool True if succesfull.
    */
    bool NotationToMove( Game& game, std::vector<Move>& move, std::string& strmove );
    
    /**
    * @brief Parses short notation and creates moves.
    * @param game Reference to game for access to board.
    * @param move vector of moves acting as return value.
    * @param strmove String which is parsed.
    * @return bool True if succesfull.
    */
    bool NotationToMoveShort( Game& game, std::vector<Move>& moves, std::string& strmove );

    /**
    * @brief Parses long notation and creates moves.
    * @param game Reference to game for access to board.
    * @param move vector of moves acting as return value.
    * @param strmove String which is parsed.
    * @return bool True if succesfull.
    */
    bool NotationToMoveLong( Game& game, std::vector<Move>& moves, std::string& strmove );


    /**
    * @brief Parses move and creates notation.
    * @param move reference to move.
    * @return string Returns notation.
    */
	std::string MoveToNotation( const Move& move );
        /**
    * @brief Parses move and creates short notation.
    * @param move reference to move.
    */
	void MoveToNotationShort( const Move& move );
        /**
    * @brief Parses move and creates long notation.
    * @param move reference to move.
    * @return string Returns notation.
    */
	void MoveToNotationLong( const Move& move );

    /// @brief Returns last line of notation
    std::string GetNotation();

    /// @brief Cleares NotationLog.
    void ClearTempNoation();
    /// @brief Clears one move from Log.
    void ClearOneMove();

    /// @brief  Switches from vector axis to chess ( 0 -> a)
	int getX(std::string str);
    /// @brief  Switches from vector axis to chess ( 0 -> 1)
	int getY(std::string str);
	
    /**
    * @brief Sets start position of piece from short notation.
    * @param game Reference to game for accessing its values.
    * @param helpspec If multiple pieces in same row or column.
    * @param typet Type of piece.
    * @para, move Refernce to move.
    * @return bool True on success.
    */
	bool SetStartPosition(Game& game, char helpspec , char typet, Move& move);

	Log();
	Log(std::vector<Square>& BoardPtr);
	~Log();

};


#pragma once
//#include "Piece.h"
#include <stdlib.h>     /* abs */
#include <memory>

class Piece;

///@brief  Square in backend.
class Square
{
private:
	/// @brief Color of square.
    int colour;

public:
	/// @brief X axis value.
	int x;
	/// @brief Y axis value.
	int y;
	/// @brief Pointer to piece on square.
	std::shared_ptr<Piece> piece;
	/// @brief Flag true if used.
	bool Used = false;


    Square(int a, int b);
    Square();
    ~Square();
};


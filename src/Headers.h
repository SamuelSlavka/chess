#pragma once

#include <vector> 
#include <memory>
#include <iostream> 
#include <list> 
#include <map> 
#include <string>
#include <stdlib.h> 

/// @brief struct handling position
struct Position {
	int x;
	int y;
};

/// @brief enum naing piece types.
enum PieceType { NoneT, PawnT, RookT, KnightT, BishopT, QueenT, KingT };
/// @brief enum  naming notation types.
enum NotationType { shorttype , longtype , notype };


/// @brief Vector of all pieces directions except knight
std::vector<int> const AllMoveVectorA{ 0,0,1,-1,1,1,-1,-1 };
std::vector<int> const AllMoveVectorB{ 1,-1,0,0,1,-1,1,-1 };
/// @brief Vector of Knight moves directions
std::vector<int> const KnightMoveVectorA{ 1,2,2,1,-1,-2,-2,-1 };
std::vector<int> const KnightMoveVectorB{ 2,1,-1,-2,-2,-1,1,2 };



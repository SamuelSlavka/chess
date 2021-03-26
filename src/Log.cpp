#include "Log.h"

/**
 *  Creates notation  and parses lnotation.
 * @brief Source file for Log
 * @file Log.cpp
 * @author Samuel Slavka (xslavk02)
 */

std::map<int, char> xmap{ {1, 'a'}, {2, 'b'}, {3, 'c'},{4, 'd'}, {5, 'e'}, {6, 'f'}, {7, 'g'}, {8, 'h'} };

const std::regex DVShortMatch("[D-V]([a-h]|[1-8])?(x)?([a-h][1-8])(\\+|#)? (.*)");
const std::regex PawnShortMatch("([a-h]|[1-8])?(x)?([a-h][1-8])[D-V]?(\\+|#)? (.*)");

const std::regex ShortMatchNoSpace("([D-V]([a-h]|[1-8])?(x)?([a-h][1-8])(\\+|#)?(.*))|(([a-h]|[1-8])?(x)?([a-h][1-8])[D-V]?(\\+|#)?(.*))");

const std::regex DVLongMatch("[D-V]([a-h][1-8])(x)?([a-h][1-8])(\\+|#)? (.*)");
const std::regex PawnLongMatch("([a-h][1-8])(x)?([a-h][1-8])[D-V]?(\\+|#)? (.*)");

const std::regex LongMatchNoSpace("(^[D-V]([a-h][1-8])(x)?([a-h][1-8])(\\+|#)?(.*))|(^([a-h][1-8])(x)?([a-h][1-8])[D-V]?(\\+|#)?(.*))");

const std::regex NotationStart("\\d+. (.*)");



int Log::getX(std::string str)
{
    return int(str.at(0))-97 ;
};
int Log::getY(std::string str)
{
    return int(str.at(1))-49 ;
};


bool Log::SetStartPosition(Game& game, char helpspec , char typet, Move& move)
{
    int hlp = -1;
    char hlptype = 'n';
    std::vector<Move> movess;

    int i = 0;

    if( helpspec!='n' ) {
        if( helpspec < 96 ) {
            hlp = getY(std::string (1, helpspec))*8;
            i = hlp;
            hlptype = 'y';
        }
        else {
            i = getX(std::string (1,helpspec));
            hlptype = 'x';
        }
    };

    while ( i < 64)
    {
        if( board[i].Used ){
            //Get moves from all pieces of same type
            if( board[i].piece->GetPieceType() == typet ) {
                movess.clear();
                game.GetMoves(board[i].x, board[i].y);

                //find move that goes to the same spot
                auto it = std::find_if(movess.begin(), movess.end(),
                                       ((boost::bind(&Move::ToX, _1) == move.ToX) && (boost::bind(&Move::ToY, _1) == move.ToY) ));

                if ( it != movess.end() ) {
                    move.FromX = it->FromX;
                    move.FromY = it->FromY;
                    move.Moved = game.GetPiece(it->FromX, it->FromY);
                    movess.clear();
                    return true;
                }
                else movess.clear();
            };
        };
        i++;
        //jsut one row
        if (hlptype == 'x') i*=8;
        //just one line
        else if(hlptype == 'y')
            if( i > hlp+8 ) break;

    };
    return false;
};

bool Log::NotationToMoveShort(Game& game, std::vector<Move>& moves, std::string&  strmove )
{
    Move move;
    char helpspec = 'n';
    std::string ToLocation, chess;

    std::smatch matches;
    notation = shorttype;

    //checking if removes
    if (regex_search(strmove, matches, std::regex ("^(\\S)*(x)(.*)")))
        move.Removes = true;
    //setting end coordinates
    if (regex_search(strmove, matches, std::regex ("^(\\S)*([a-h][1-8])(.*)"))) {
        move.ToX = getX(matches.str(2));
        move.ToY = getY(matches.str(2));
        if( move.Removes == true) move.Removed = game.GetPiece(move.ToX,move.ToY);//.board.board[move.ToX + move.ToY*8].piece;
    }
    //checking chess or mat
    if (regex_search(strmove, matches, std::regex ("^(\\S)*(\\+|#)(.*)"))) {
        if (matches.str(1) == "#") move.Mat = true;
        else move.Chess = true;
    }
    //checking special attributes
    if (std::regex_match(strmove, DVShortMatch))
    {
        if (regex_search(strmove, matches, std::regex ("^[D-V]([a-h]|[1-8])(x)?([a-h][1-8])(\\+|#)?")))
            helpspec = strmove.at(1);
    }
    else if( std::regex_match(strmove, PawnShortMatch))
    {
        if (regex_search(strmove, matches, std::regex ("^([a-h]|[1-8])(x)?([a-h][1-8])([D-V])?(\\+|#)?(.*)")))
            helpspec = strmove.at(1);
        if (regex_search(strmove, matches, std::regex ("^([a-h]|[1-8])?(x)?([a-h][1-8])([D-V])(\\+|#)?")))
            move.Promoted = true;
    };
    //setting start coordinates
    SetStartPosition(game, helpspec, strmove.at(0), move);
    move.Order= moves.size();
    //adds move to vector of made moves
    moves.push_back(move);

    //end after black move
    if ( std::regex_match(strmove, std::regex("^(\\S)*"))) return true;
    //cut off white move
    strmove = std::regex_replace(strmove, std::regex("^(\\S)* "), "");
    //get black move
    if ( std::regex_match(strmove, LongMatchNoSpace) )
        return NotationToMoveLong( game, moves, strmove );

    return false;
};

bool Log::NotationToMoveLong(Game& game, std::vector<Move>& moves, std::string& strmove )
{
    Move move;
    std::string ToLocation, chess;

    std::smatch matches;
    notation = longtype;
    //chcking if removes
    if (regex_search(strmove, matches, std::regex ("^(\\S)*(x)(.*)")))
        move.Removes = true;

    //setting start coordinates
    if (regex_search(strmove, matches, std::regex ("^([D-V]?)([a-h][1-8])(.*)"))) {
        //std::cout << matches.str(2) << std::endl;
        move.FromX = getX(matches.str(2));
        move.FromY = getY(matches.str(2));
        move.Moved = game.GetPiece(move.FromX, move.FromY);//board.board[move.FromX + move.FromY*8].piece;
    }
    //setting end coordinates
    if (regex_search(strmove, matches, std::regex ("^([D-V]?)([a-h][1-8])(x)?([a-h][1-8])(.*)"))) {
        //std::cout << matches.str(3) << std::endl;
        int group = 4;
        if( move.Removes ) group = 4;

        move.ToX = getX(matches.str( group ));
        move.ToY = getY(matches.str( group ));

        if( move.Removes ) move.Removed = game.GetPiece(move.ToX, move.ToY);
    }
    //checking for chess or mat
    if (regex_search(strmove, matches, std::regex ("^(\\S)*(\\+|#)(.*)"))) {
        if (matches.str(1) == "#") move.Mat = true;
        else move.Chess = true;
    }

    //special pawn attributes
    if(std::regex_match(strmove, PawnLongMatch))
    {
        if (regex_search(strmove, matches, std::regex ("^(\\S)*([a-h][1-8])(x)?([a-h][1-8])([D-V])(.*)")))
            move.Promoted = true;
    };

    move.Order= moves.size();
    moves.push_back(move);

    //end after black move
    if ( std::regex_match(strmove, std::regex("^(\\S)*"))) return true;
    //cut off white move
    strmove = std::regex_replace(strmove, std::regex("^(\\S)* "), "");
    //get black move
    if ( std::regex_match(strmove, LongMatchNoSpace) )
        return NotationToMoveLong( game, moves, strmove );

    return false;
};

bool Log::NotationToMove( Game& game, std::vector<Move>& move, std::string& strmove )	//TODO zajtra
{
    if (std::regex_match(strmove, NotationStart))
    {
        std::string::size_type sz;
        int res = std::stoi(strmove, &sz);	//todo check order of lines

        //cutting off "[num]. "
        strmove = std::regex_replace(strmove, std::regex("^(\\S)*. "), "");

        //Short notation
        if (std::regex_match(strmove, DVShortMatch) || std::regex_match(strmove, PawnShortMatch))
        {
            //checking for switch of notation in middle
            if ( notation != shorttype && res != 1 ) return false;
            return NotationToMoveShort(game, move, strmove);
        }
        //Long notation
        else if (std::regex_match(strmove, DVLongMatch) || std::regex_match(strmove, PawnLongMatch))
        {
            //checking for switch of notation in middle
            if ( notation != longtype && res != 1 ) return false;
            return NotationToMoveLong( game, move, strmove);
        }
        else return false;
    };
    return false;
};

//checks for pieces in same row/column
char Log::HasNeighbours(int x, int y, char ptype)	//todo pawn removing
{
    if ( ptype != 'p' && ptype != 'Q' && ptype != 'K')
    {
        int i;
        for ( i=0; i<8; ++i )
        {
            Square sq = board[i+y*8];
            if (sq.Used && i!=x)
                if (board[i+y*8].piece->GetPieceType() == ptype)
                    return xmap.at(x);
        };
        for ( i=0; i<8; ++i )
        {
            Square sq = board[x+i*8];
            if (sq.Used && i!=y)
                if (board[x+i*8].piece->GetPieceType() == ptype)
                    return y;
        };
    };
    if ( ptype == 'p' )
    {
        if( board[x+y*8].piece->CheckBounds(x+2,y) )
            if ( board[x+2+y*8].Used )
                if (board[x+2+y*8].piece->GetPieceType() == ptype)
                    return xmap.at(x);
        if( board[x+y*8].piece->CheckBounds(x-2,y) )
            if ( board[x-2+y*8].Used )
                if (board[x-2+y*8].piece->GetPieceType() == ptype)
                    return xmap.at(x);
    };
    return 'n';
};

std::string Log::MoveToNotation( const Move& move )
{
    if ((move.Order % 2)) {
        if (move.Order != 1)	NotationLog += "\n";
        NotationLog += std::to_string( (move.Order/2 + 1) );
        NotationLog += ". ";
    }
    else NotationLog += " ";
    if ( notation == shorttype ) MoveToNotationShort( move );
    else MoveToNotationLong( move );

    // GameLog.push_back(NotationLog);


    return NotationLog;
};

void Log::MoveToNotationShort( const Move& move )
{
    char ptype =  move.Moved->GetPieceType();
    if ( ptype != 'p' && !move.Promoted )	//not pawn
        NotationLog.push_back( ptype );

    char neighbours =  HasNeighbours( move.FromX, move.FromY, ptype);
    if ( neighbours != 'n' ) NotationLog.push_back( neighbours );

    if ( move.Removes ) NotationLog.push_back( 'x' );

    NotationLog.push_back( xmap.at(move.ToX+1) );
    NotationLog += std::to_string(move.ToY+1);

    if ( move.Promoted ) NotationLog.push_back( ptype );

    if ( move.Chess ) NotationLog.push_back('+');
    if ( move.Mat ) NotationLog.push_back('#');


};

void Log::MoveToNotationLong( const Move& move )
{
    char ptype =  move.Moved->GetPieceType();
    if ( ptype != 'p' && !move.Promoted )	//not pawn
        NotationLog.push_back( ptype );

    NotationLog.push_back( xmap.at(move.FromX+1) );
    NotationLog += std::to_string(move.FromY+1);

    if ( move.Removes ) NotationLog.push_back( 'x' );

    NotationLog.push_back( xmap.at(move.ToX+1) );
    NotationLog += std::to_string(move.ToY+1);

    if ( move.Promoted ) NotationLog.push_back( ptype );

    if ( move.Chess ) NotationLog.push_back('+');
    if ( move.Mat ) NotationLog.push_back('#');

};


void Log::ClearTempNoation()
{
    NotationLog.clear();
}

void Log::ClearOneMove()
{
    if ( NotationLog.size() ) {
        //first part
        if ( std::regex_match(NotationLog, std::regex("^[0-9]+\\. (\\S)+$")  )) {
            NotationLog.clear();
        }//second part
        else {
            const auto pos = NotationLog.find_last_of(" ");
            NotationLog = NotationLog.substr(0, pos);
        }
    }
}

std::string Log::GetNotation()
{
    std::istringstream input;
    input.str(NotationLog);
    std::string line;
    
    //for ( line; std::getline( input , line););
    while ( std::getline( input , line) );
    
    return line;
}

Log::Log( std::vector<Square>& BoardPtr) : board(BoardPtr) {};

Log::~Log() {};



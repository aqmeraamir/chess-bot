#ifndef EVALUATION_H
#define EVALUATION_H

#include "ChessBoard.h"

// Piece values
const int PAWN_VALUE = 1;
const int KNIGHT_VALUE = 3;
const int BISHOP_VALUE = 3;
const int ROOK_VALUE = 5;
const int QUEEN_VALUE = 9;
const int KING_VALUE = 10000;

// weights
const double DOUBLED_PAWNS_WEIGHT = -0.5;
const double MOBILITY_WEIGHT = 0.1;


int evaluateMaterial(ChessBoard& board);
int evaluatePosition(ChessBoard& board);
int evaluateDoubledPawns(ChessBoard& board);
int evaluateMobility(ChessBoard& board);

pair<int, Move> minimax(ChessBoard& board, int depth, bool isWhite);

#endif 

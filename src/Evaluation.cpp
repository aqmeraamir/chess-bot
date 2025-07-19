#include "Evaluation.h"

// functions to evaluate score 
 
int evaluatePosition(ChessBoard& board) {
    if (board.isCheckmate(true)) {
        return -10000;  
    }
    if (board.isCheckmate(false)) {
        return 10000;   
    }
    
    int score = evaluateMaterial(board);

    score += evaluateDoubledPawns(board) * DOUBLED_PAWNS_WEIGHT;
    score += evaluateMobility(board) * MOBILITY_WEIGHT;

    return score;
}

int evaluateMaterial(ChessBoard& board) {
    int whiteMaterial = 0;
    int blackMaterial = 0;

    // white material
    whiteMaterial += __builtin_popcountll(board.whitePawns) * PAWN_VALUE;
    whiteMaterial += __builtin_popcountll(board.whiteKnights) * KNIGHT_VALUE;
    whiteMaterial += __builtin_popcountll(board.whiteBishops) * BISHOP_VALUE;
    whiteMaterial += __builtin_popcountll(board.whiteRooks) * ROOK_VALUE;
    whiteMaterial += __builtin_popcountll(board.whiteQueen) * QUEEN_VALUE;
    whiteMaterial += __builtin_popcountll(board.whiteKing) * KING_VALUE;

    // black material
    blackMaterial += __builtin_popcountll(board.blackPawns) * PAWN_VALUE;
    blackMaterial += __builtin_popcountll(board.blackKnights) * KNIGHT_VALUE;
    blackMaterial += __builtin_popcountll(board.blackBishops) * BISHOP_VALUE;
    blackMaterial += __builtin_popcountll(board.blackRooks) * ROOK_VALUE;
    blackMaterial += __builtin_popcountll(board.blackQueen) * QUEEN_VALUE;
    blackMaterial += __builtin_popcountll(board.blackKing) * KING_VALUE;

    return whiteMaterial - blackMaterial;
}

int evaluateDoubledPawns(ChessBoard& board) {
    int whiteDoubledPawns = 0;
    int blackDoubledPawns = 0;

    // white pawns
    for (int file = 0; file < 8; ++file) {
        ULL fileMask = 0x0101010101010101 << file;
        int pawnsInFile = __builtin_popcountll(board.whitePawns & fileMask);
        if (pawnsInFile > 1) whiteDoubledPawns += pawnsInFile - 1;
    }

    // black pawns
    for (int file = 0; file < 8; ++file) {
        ULL fileMask = 0x0101010101010101 << file;
        int pawnsInFile = __builtin_popcountll(board.blackPawns & fileMask);
        if (pawnsInFile > 1) blackDoubledPawns += pawnsInFile - 1;
    }

    return whiteDoubledPawns - blackDoubledPawns;

}

int evaluateMobility(ChessBoard& board) {
    vector<Move> legalMovesWhite = board.generateLegalMoves(true);
    vector<Move> legalMovesBlack = board.generateLegalMoves(false);

    return legalMovesWhite.size() - legalMovesBlack.size();

}

// minimax to find best move
pair<int, Move> minimax(ChessBoard& board, int depth, bool isWhite) {
    if (depth == 0 || board.isGameOver()) return {evaluatePosition(board), Move()};

    vector<Move> legalMoves = board.generateLegalMoves(isWhite);
    Move bestMove;
    if (isWhite) {
        int bestValue = INT_MIN;
        for (const Move& move : legalMoves) {
            ChessBoard newBoard = board;
            newBoard.makeMove(move, isWhite);
            int value = minimax(newBoard, depth - 1, false).first;
            if (value > bestValue) {
                bestValue = value;
                bestMove = move;
            }
        }
        return {bestValue, bestMove};
    } 
    
    else {
        int bestValue = INT_MAX;
        for (const Move& move : legalMoves) {
            ChessBoard newBoard = board;
            newBoard.makeMove(move, isWhite);
            int value = minimax(newBoard, depth - 1, true).first;
            if (value < bestValue) {
                bestValue = value;
                bestMove = move;
            }
        }
        return {bestValue, bestMove};
    }
}
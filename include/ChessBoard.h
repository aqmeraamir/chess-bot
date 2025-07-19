#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <bitset>
#include <vector>
#include <tuple>

using ULL = unsigned long long int;
using namespace std;

struct Move {
    int source; // Source square index (0-63)
    int target; // Target square index (0-63)
    char moveType; // 'M' = move, 'C' = capture, 'K' = castling
    char piece; // 'P', 'N', 'B', 'R', 'Q', 'K'

    bool operator==(const Move& other) const {
        return source == other.source && target == other.target && moveType == other.moveType && piece == other.piece;
    }
};


class ChessBoard {

    private:

        // Constants
        const ULL notAFile = 0x7F7F7F7F7F7F7F7F;
        const ULL notABFile = 0x3F3F3F3F3F3F3F3F;
        const ULL notHFile = 0xFEFEFEFEFEFEFEFE;
        const ULL notGHFile = 0xFCFCFCFCFCFCFCFC;

        // Private functions
        ULL slide(ULL piece, ULL blockers, int direction);
        ULL* findOpponentBoard(const Move& move, bool isWhite);
        

    public:
        
        pair<char, bool> getPieceAtPosition(int position);
        vector<int> getPositionOfPiece(char piece, bool isWhite);

        string indexToChessPosition(int number);
        int chessPositionToIndex(string position);

        // Member variables
        ULL whitePawns = 0x00FF000000000000;
        ULL whiteKnights = 0x4200000000000000;
        ULL whiteBishops = 0x2400000000000000;
        ULL whiteRooks = 0x8100000000000000;
        ULL whiteQueen = 0x1000000000000000;
        ULL whiteKing = 0x0800000000000000;

        ULL blackPawns = 0x000000000000FF00;
        ULL blackKnights = 0x0000000000000042;
        ULL blackBishops = 0x0000000000000024;
        ULL blackRooks = 0x0000000000000081;
        ULL blackQueen = 0x0000000000000010;
        ULL blackKing = 0x0000000000000008;

        // Public functions
        void displayBoard(ULL whitePawns = -1, ULL whiteKnights = -1, ULL whiteBishops = -1, 
                        ULL whiteRooks = -1, ULL whiteQueen = -1, ULL whiteKing = -1,
                        ULL blackPawns = -1, ULL blackKnights = -1, ULL blackBishops = -1,
                        ULL blackRooks = -1, ULL blackQueen = -1, ULL blackKing = -1);
        ULL getAllPieces();
        ULL whitePieces();
        ULL blackPieces();
        
        vector<Move> generatePawnMoves(bool isWhite);
        vector<Move> generateKnightMoves(bool isWhite);
        vector<Move> generateBishopMoves(bool isWhite, ULL bishops = -1, ULL allPieces = -1);
        vector<Move> generateRookMoves(bool isWhite, ULL rooks = -1, ULL allPieces = -1);
        vector<Move> generateQueenMoves(bool isWhite, ULL queen = -1, ULL allPieces = -1);
        vector<Move> generateKingMoves(bool isWhite, ULL king = -1, ULL allPieces = -1);

        ULL makeMove(const Move& move, bool isWhite);
        void undoMove(const Move& move, bool isWhite, ULL* capturedPiece = nullptr);
        bool isKingInCheck(bool isWhite);
        bool isCheckmate(bool isWhite);
        bool isGameOver();
        vector<Move> generateLegalMoves(bool isWhite);
        
};

#endif

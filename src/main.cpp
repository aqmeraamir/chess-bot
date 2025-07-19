#include <iostream>
#include <bitset> 
#include <vector>
#include <tuple>
#include <regex>

#include "ChessBoard.h"
#include "Evaluation.h"

using namespace std;

Move translateNotationToMove(ChessBoard& board, string move, bool isWhite) { 

    Move translatedMove = {-1, -1, '\0', '\0'};
    
    char piece, moveType = 'M';

    if (move.back() == '+' || move.back() == '#') {
        move.pop_back();
    }

    if(find(move.begin(), move.end(), 'x') != move.end()) {
        moveType = 'C';
        move.erase(remove(move.begin(), move.end(), 'x'), move.end());
    }

    int target = board.chessPositionToIndex(move.substr(move.length() - 2, move.length()));
    move = move.erase(move.length() - 2, 2);
    piece = move[0] ? move[0] : 'P';
    
    vector<Move> legalMoves = board.generateLegalMoves(isWhite);
    for (int position : board.getPositionOfPiece(piece, isWhite)) {
        for (Move legalMove : legalMoves) {
            if (legalMove.target == target && legalMove.source == position && legalMove.moveType == moveType) {
                translatedMove = legalMove;
            }
        }
    }
    

    return translatedMove;
}

Move parseMove(ChessBoard& board, string move) {
    if (move.length() != 4) {
        throw invalid_argument("Move must be 4 characters long");
    }

    int source = board.chessPositionToIndex(move.substr(0, 2));
    int target = board.chessPositionToIndex(move.substr(2, 2));
    auto [piece, isWhite] = board.getPieceAtPosition(source);
    auto [targetPiece, targetIsWhite] = board.getPieceAtPosition(target);

    char moveType = (!targetIsWhite && targetPiece) ? 'C' : 'M';

    Move parsedMove = {source, target, moveType, piece};

    return parsedMove;
}

void loadGame(string data) {
    
}

void gameLoop(ChessBoard& board) {
    string move;

    while (true) {
        board.displayBoard();

        cout << "Enter your move (e.g., e2e4) or 'q' to quit: ";
        cin >> move;

        if (move == "q") {
            break;
        }

        vector<Move> legalMoves = board.generateLegalMoves(true);
        Move parsedMove = parseMove(board, move);


        while (find(legalMoves.begin(), legalMoves.end(), parsedMove) == legalMoves.end()) {
            cout << "Illegal move. Try again: ";
            cin >> move;
            parsedMove = parseMove(board, move);
        }
        
        board.makeMove(parsedMove, true);


        auto [evaluation, bestMove] = minimax(board, 2, false);

        cout << "\nAI move: " << board.indexToChessPosition(bestMove.source) << " to " << board.indexToChessPosition(bestMove.target) << "\n" << endl;

        board.makeMove(bestMove, false);
   
    }
}

int main() {
    ChessBoard board;
    gameLoop(board);
    return 0;
}

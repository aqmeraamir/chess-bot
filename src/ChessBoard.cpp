#include "ChessBoard.h"


// private / helper functions

ULL ChessBoard::slide(ULL piece, ULL blockers, int direction) {
    ULL moves = 0;
    ULL nextBlockedMoves = 0;

    while (piece) {

        //handle edge cases
        if (direction == 7 || direction == -9) piece &= notAFile; // exclude A file
        if (direction == 9 || direction == -7) piece &= notHFile; // exclude H file
        if (direction == -1) piece &= notAFile; // exclude A file
        if (direction == 1) piece &= notHFile; // exclude H file


        if (direction > 0) {
            piece = (piece >> direction);
        } else {
            piece = (piece << -direction);
        }

        moves |= piece; // add the move   
        piece = piece & ~blockers; // remove blockers from piece
        blockers |= piece; // add current piece to blockers

    }

    return moves;
}

ULL* ChessBoard::findOpponentBoard(const Move& move, bool isWhite) {
    if (isWhite) {
        int steps = 63 - move.target;

        if (this->blackPawns & (1ULL << steps)) {
            return &this->blackPawns;
        } else if (this->blackKnights & (1ULL << steps)) {
            return &this->blackKnights;
        } else if (this->blackBishops & (1ULL << steps)) {
            return &this->blackBishops;
        } else if (this->blackRooks & (1ULL << steps)) {
            return &this->blackRooks;
        } else if (this->blackQueen & (1ULL << steps)) {
            return &this->blackQueen;
        } else if (this->blackKing & (1ULL << steps)) {
            return &this->blackKing;
        }
    } else {
        int steps = 63 - move.target;

        if (this->whitePawns & (1ULL << steps)) {
            return &this->whitePawns;
        } else if (this->whiteKnights & (1ULL << steps)) {
            return &this->whiteKnights;
        } else if (this->whiteBishops & (1ULL << steps)) {
            return &this->whiteBishops;
        } else if (this->whiteRooks & (1ULL << steps)) {
            return &this->whiteRooks;
        } else if (this->whiteQueen & (1ULL << steps)) {
            return &this->whiteQueen;
        } else if (this->whiteKing & (1ULL << steps)) {
            return &this->whiteKing;
        }
        }

    return nullptr; // If no opponent piece was found
}

pair<char, bool> ChessBoard::getPieceAtPosition(int position) {
    ULL mask = 1ULL << (63 - position);
    if (this->whitePawns & mask) return {'P', true};
    if (this->whiteKnights & mask) return {'N', true};
    if (this->whiteBishops & mask) return {'B', true};
    if (this->whiteRooks & mask) return {'R', true};
    if (this->whiteQueen & mask) return {'Q', true};
    if (this->whiteKing & mask) return {'K', true};

    if (this->blackPawns & mask) return {'P', false};
    if (this->blackKnights & mask) return {'N', false};
    if (this->blackBishops & mask) return {'B', false};
    if (this->blackRooks & mask) return {'R', false};
    if (this->blackQueen & mask) return {'Q', false};
    if (this->blackKing & mask) return {'K', false};

    return {'\0', false};
}

vector<int> ChessBoard::getPositionOfPiece(char piece, bool isWhite) {
    ULL* pieceBoard = nullptr;
    vector<int> positions;

    switch (piece) {
        case 'P': pieceBoard = isWhite ? &this->whitePawns : &this->blackPawns; break;
        case 'N': pieceBoard = isWhite ? &this->whiteKnights : &this->blackKnights; break;
        case 'B': pieceBoard = isWhite ? &this->whiteBishops : &this->blackBishops; break;
        case 'R': pieceBoard = isWhite ? &this->whiteRooks : &this->blackRooks; break;
        case 'Q': pieceBoard = isWhite ? &this->whiteQueen : &this->blackQueen; break;
        case 'K': pieceBoard = isWhite ? &this->whiteKing : &this->blackKing; break;
    }

    for (int i = 0; i < 64; ++i) {
        ULL mask = 1ULL << i;
        if (*pieceBoard & mask) positions.push_back(63 - i);
    }

    return positions;
}

string ChessBoard::indexToChessPosition(int number) {
    if (number < 0 || number > 63) {
        throw invalid_argument("Number must be between 0 and 63");
    }
    
    char column = 'a' + (number % 8);  // calculate column ('a' to 'h')
    int row = 1 + (number / 8);        // calculate row (1 to 8)
    
    return string(1, column) + to_string(row);
}

int ChessBoard::chessPositionToIndex(string position) {
    if (position.length() != 2) {
        throw invalid_argument("Position must be 2 characters long");
    }

    char column = position[0];
    int row = position[1] - '0';

    if (column < 'a' || column > 'h' || row < 1 || row > 8) {
        throw invalid_argument("Invalid position");
    }

    return (row - 1) * 8 + (column - 'a');
}

// public functions

void ChessBoard::displayBoard(
    ULL whitePawns, ULL whiteKnights, ULL whiteBishops,
    ULL whiteRooks, ULL whiteQueen, ULL whiteKing,
    ULL blackPawns, ULL blackKnights, ULL blackBishops,
    ULL blackRooks, ULL blackQueen, ULL blackKing) {

    // default to member variables if nothing provided
    whitePawns = (whitePawns == -1) ? this->whitePawns : whitePawns;
    whiteKnights = (whiteKnights == -1) ? this->whiteKnights : whiteKnights;
    whiteBishops = (whiteBishops == -1) ? this->whiteBishops : whiteBishops;
    whiteRooks = (whiteRooks == -1) ? this->whiteRooks : whiteRooks;
    whiteQueen = (whiteQueen == -1) ? this->whiteQueen : whiteQueen;
    whiteKing = (whiteKing == -1) ? this->whiteKing : whiteKing;

    blackPawns = (blackPawns == -1) ? this->blackPawns : blackPawns;
    blackKnights = (blackKnights == -1) ? this->blackKnights : blackKnights;
    blackBishops = (blackBishops == -1) ? this->blackBishops : blackBishops;
    blackRooks = (blackRooks == -1) ? this->blackRooks : blackRooks;
    blackQueen = (blackQueen == -1) ? this->blackQueen : blackQueen;
    blackKing = (blackKing == -1) ? this->blackKing : blackKing;

    vector<string> board(64, " ");

    // place black pieces
    for (int i = 0; i < 64; ++i) {
        ULL mask = 1LL << i;
        if (blackPawns & mask) board[63-i] = "♙";
        if (blackKnights & mask) board[63-i] = "♘";
        if (blackBishops & mask) board[63-i] = "♗";
        if (blackRooks & mask) board[63-i] = "♖";
        if (blackQueen & mask) board[63-i] = "♕";
        if (blackKing & mask) board[63-i] = "♔";
    }

    // place white pieces
    for (int i = 0; i < 64; ++i) {
        ULL mask = 1LL << i;
        if (whitePawns & mask) board[63-i] = "♟";
        if (whiteKnights & mask) board[63-i] = "♞";
        if (whiteBishops & mask) board[63-i] = "♝";
        if (whiteRooks & mask) board[63-i] = "♜";
        if (whiteQueen & mask) board[63-i] = "♛";
        if (whiteKing & mask) board[63-i] = "♚";
    }

    // Print the board
    for (int rank = 7; rank >= 0; --rank) {
        cout << rank + 1 << " "; // Row numbers
        for (int file = 0; file < 8; ++file) {
            cout << board[rank * 8 + file] << " ";
        }
        cout << endl;
    }
    cout << "  a b c d e f g h\n" << endl; // Column letters
}


// generating moves

ULL ChessBoard::getAllPieces() { 
    return this->whitePawns | this->whiteKnights | this->whiteBishops |
                this->whiteRooks | this->whiteQueen | this->whiteKing |
                this->blackPawns | this->blackKnights | this->blackBishops |
                this->blackRooks | this->blackQueen | this->blackKing;
}

ULL ChessBoard::whitePieces() {
    return this->whitePawns | this->whiteKnights | this->whiteBishops |
                this->whiteRooks | this->whiteQueen | this->whiteKing;
}

ULL ChessBoard::blackPieces() {
    return this->blackPawns | this->blackKnights | this->blackBishops |
                this->blackRooks | this->blackQueen | this->blackKing;
}

vector<Move> ChessBoard::generatePawnMoves(bool isWhite) {
    
    ULL allPieces = this->getAllPieces();
    ULL pawns = isWhite ? this->whitePawns : this->blackPawns;
    ULL opponentPieces = isWhite ? this->blackPieces() : this->whitePieces();

    vector<Move> moves;
    ULL singlePush, doublePush, capturesLeft, capturesRight;

    if (isWhite) {
        singlePush = (pawns >> 8) & ~allPieces; // single pushes
        doublePush = ((pawns & 0xFF000000000000ULL) >> 16) & slide(pawns, allPieces, 8); // double pushes
        capturesRight = (pawns >> 9) & notHFile & opponentPieces; // right
        capturesLeft = (pawns >> 7) & notAFile & opponentPieces; // left
    } else {
        singlePush =  (pawns << 8);
        doublePush = ((pawns & 0xFF00ULL) << 16) & slide(pawns, allPieces, -8);
        capturesRight = (pawns << 9) & notHFile & opponentPieces; 
        capturesLeft = (pawns << 7) & notAFile & opponentPieces; 
    }
    

    for (int i=0; i<64; ++i) {
        ULL mask = 1ULL << i;
        int dest = 63-i;
        if (singlePush & mask) moves.push_back({isWhite ? dest-8 : dest+8, dest, 'M', 'P'});
        if (doublePush & mask) moves.push_back({isWhite ? dest-16 : dest+16, dest, 'M', 'P'});
        if (capturesLeft & mask) moves.push_back({isWhite ? dest-7 : dest+7, dest, 'C', 'P'});
        if (capturesRight & mask) moves.push_back({isWhite ? dest-9 : dest+9, dest, 'C', 'P'});
    }

    return moves;
}

vector<Move> ChessBoard::generateKnightMoves(bool isWhite) {
    ULL allPieces = this->getAllPieces();
    ULL knights = isWhite ? this->whiteKnights : this->blackKnights;
    ULL opponentPieces = isWhite ? this->blackPieces() : this->whitePieces();

    vector<Move> moves;
    ULL allMoves, validMoves, captures;

    allMoves = (knights & notAFile) << 17; 
    allMoves |= (knights & notHFile) << 15; 
    allMoves |= (knights & notHFile) >> 17; 
    allMoves |= (knights & notAFile) >> 15; 
    allMoves |= (knights & notABFile) << 10;
    allMoves |= (knights & notGHFile) << 6; 
    allMoves |= ((knights & notGHFile) >> 10); 
    allMoves |= (knights & notABFile) >> 6;   
    
    validMoves = allMoves & ~allPieces; 
    captures = allMoves & opponentPieces;

    // loop to find source and destination for each move
    for (int dest=0; dest < 64; ++dest) {
        ULL mask = 1LL << dest;

        if (validMoves & mask || captures & mask) {
            for (int src = 0; src < 64; ++src) {
                ULL srcMask = 1ULL << src;

                if (knights & srcMask) {
                    ULL knightMoves = 0;
                    knightMoves |= (srcMask & notAFile) << 17;
                    knightMoves |= (srcMask & notHFile) << 15;
                    knightMoves |= (srcMask & notHFile) >> 17;
                    knightMoves |= (srcMask & notAFile) >> 15;
                    knightMoves |= (srcMask & notABFile) << 10;
                    knightMoves |= (srcMask & notGHFile) << 6;
                    knightMoves |= (srcMask & notGHFile) >> 10;
                    knightMoves |= (srcMask & notABFile) >> 6;

                    if (knightMoves & mask) {
                        char moveType = (captures & mask) ? 'C' : 'M';
                        moves.push_back({63-src, 63-dest, moveType, 'N'});
                        break;
                    }

                }

            }
        }
        
    }

    return moves;
}

vector<Move> ChessBoard::generateBishopMoves(bool isWhite, ULL bishops, ULL allPieces) {

    char pieceType = 'B';

    // if custom bishops are not provided, use the member variables
    if (bishops == -1 || allPieces == -1) {
        bishops = isWhite ? this->whiteBishops : this->blackBishops;
        allPieces = this->getAllPieces();
    } else pieceType = 'Q';

    ULL opponentPieces = isWhite ? this->blackPieces() : this->whitePieces();

    // generate moves
    vector<Move> moves;
    ULL allMoves, validMoves, captures;

    allMoves = slide(bishops, allPieces, 9);
    allMoves |= slide(bishops, allPieces, 7);
    allMoves |= slide(bishops, allPieces, -9);
    allMoves |= slide(bishops, allPieces, -7);

    validMoves = allMoves & ~allPieces;
    captures = allMoves & opponentPieces;

    // loop to find source and destination for each move
    for (int dest=0; dest<64; ++dest) {
        ULL mask = 1LL << dest;

        if (validMoves & mask || captures & mask) {
            for (int src = 0; src < 64; ++src) {
                ULL srcMask = 1ULL << src;

                if (bishops & srcMask) {
                    ULL bishopMoves = 0;
                    bishopMoves |= slide(srcMask, allPieces, 9);
                    bishopMoves |= slide(srcMask, allPieces, 7);
                    bishopMoves |= slide(srcMask, allPieces, -9);
                    bishopMoves |= slide(srcMask, allPieces, -7);

                    if (bishopMoves & mask) {
                        char moveType = (captures & mask) ? 'C' : 'M';
                        moves.push_back({63-src, 63-dest, moveType, pieceType});
                        break;
                    }

                }

            }
        }
        
    }

    return moves;
}

vector<Move> ChessBoard::generateRookMoves(bool isWhite, ULL rooks, ULL allPieces) {
    char pieceType = 'R';

    // if custom rooks are not provided, use the member variables
    if (rooks == -1 || allPieces == -1) {
        rooks = isWhite ? this->whiteRooks : this->blackRooks;
        allPieces = this->getAllPieces();
    } else pieceType = 'Q';

    ULL myPieces = isWhite ? this->whitePieces() : this->blackPieces();
    ULL opponentPieces = isWhite ? this->blackPieces() : this->whitePieces();

    // generate moves
    vector<Move> moves;
    ULL allMoves, validMoves, captures;

    allMoves = slide(rooks, allPieces, 8);   // Up
    allMoves |= slide(rooks, allPieces, -8);  // Down
    allMoves |= slide(rooks, allPieces, 1);   // Right
    allMoves |= slide(rooks, allPieces, -1);  // Left

    // remove moves that are blocked by own pieces and find captures
    validMoves = allMoves & ~allPieces;
    captures = allMoves & opponentPieces;

    // loop to find source and destination for each move
    for (int dest=0; dest<64; ++dest) {
        ULL mask = 1LL << dest;

        if (validMoves & mask || captures & mask) {
            for (int src = 0; src < 64; ++src) {
                ULL srcMask = 1ULL << src;

                if (rooks & srcMask) {
                    ULL rookMoves = 0;
                    rookMoves |= slide(srcMask, allPieces, 8);
                    rookMoves |= slide(srcMask, allPieces, -8);
                    rookMoves |= slide(srcMask, allPieces, 1);
                    rookMoves |= slide(srcMask, allPieces, -1);

                    if (rookMoves & mask) {
                        char moveType = (captures & mask) ? 'C' : 'M';
                        moves.push_back({63-src, 63-dest, moveType, pieceType});
                        break;
                    }

                }

            }
        }
        
    }

    return moves;
}

vector<Move> ChessBoard::generateQueenMoves(bool isWhite, ULL queen, ULL allPieces) {
    // if custom queen(s) is not provided, use the member variables
    if (queen == -1 || allPieces == -1) {
        queen = isWhite ? this->whiteQueen : this->blackQueen;
        allPieces = this->getAllPieces();
    }

    vector<Move> moves;
    vector<Move> diagonalMoves = generateBishopMoves(isWhite, queen, allPieces);
    vector<Move> staightMoves = generateRookMoves(isWhite, queen, allPieces);

    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
    moves.insert(moves.end(), staightMoves.begin(), staightMoves.end());


    return moves;
}

vector<Move> ChessBoard::generateKingMoves(bool isWhite, ULL king, ULL allPieces) {
    // if custom king(s) is not provided, use the member variables
    if (king == -1 || allPieces == -1) {
        king = isWhite ? this->whiteKing : this->blackKing;
        allPieces = this->getAllPieces();
    }

    ULL myPieces = isWhite ? this->whitePieces() : this->blackPieces();
    ULL opponentPieces = isWhite ? this->blackPieces() : this->whitePieces();

    vector<Move> moves;
    ULL allMoves, validMoves, captures;
    
    allMoves = (king << 8);  // down
    allMoves |= (king >> 8);  // up
    allMoves |= (king << 1) & notAFile;  // left
    allMoves |= (king >> 1) & notHFile;  // right
    allMoves |= (king << 9) & notAFile;  // down-left
    allMoves |= (king << 7) & notHFile;  // down-right
    allMoves |= (king >> 9) & notHFile;  // up-left
    allMoves |= (king >> 7) & notAFile;  // up-right

    validMoves &= allMoves & ~allPieces;
    captures = allMoves & opponentPieces;

    // loop to find source and destination for each move
    for (int dest=0; dest<64; ++dest) {
        ULL mask = 1LL << dest;

        if (validMoves & mask || captures & mask) {
            for (int src = 0; src < 64; ++src) {
                ULL srcMask = 1ULL << src;

                if (king & srcMask) {
                    ULL kingMoves = 0;
                    kingMoves |= (srcMask << 8);
                    kingMoves |= (srcMask >> 8);
                    kingMoves |= (srcMask << 1) & notAFile;
                    kingMoves |= (srcMask >> 1) & notHFile;
                    kingMoves |= (srcMask << 9) & notAFile;
                    kingMoves |= (srcMask << 7) & notHFile;
                    kingMoves |= (srcMask >> 9) & notHFile;
                    kingMoves |= (srcMask >> 7) & notAFile;

                    if (kingMoves & mask) {
                        char moveType = (captures & mask) ? 'C' : 'M';
                        moves.push_back({63 - src, 63 - dest, moveType, 'K'});
                        break;
                    }

                }

            }
        }
        
    }

    return moves;
}


// making moves, check, filtering out illegal moves


ULL ChessBoard::makeMove(const Move& move, bool isWhite) {
    ULL* pieceBoard = nullptr;
    ULL* opponentBoard = nullptr;
    ULL capturedPiece = 0;

    // determine which player's piece board is involved in the move
    switch (move.piece) {
        case 'P': pieceBoard = isWhite ? &this->whitePawns : &this->blackPawns; break;
        case 'N': pieceBoard = isWhite ? &this->whiteKnights : &this->blackKnights; break;
        case 'B': pieceBoard = isWhite ? &this->whiteBishops : &this->blackBishops; break;
        case 'R': pieceBoard = isWhite ? &this->whiteRooks : &this->blackRooks; break;
        case 'Q': pieceBoard = isWhite ? &this->whiteQueen : &this->blackQueen; break;
        case 'K': pieceBoard = isWhite ? &this->whiteKing : &this->blackKing; break;
    }

    // remove the piece from the source position and add it to the target
    *pieceBoard &= ~(1ULL << (63 - move.source));
    *pieceBoard |= (1ULL << (63 - move.target));


    if (move.moveType == 'C') {
        opponentBoard = findOpponentBoard(move, isWhite);
        // remove the opponent's piece if found
        if (opponentBoard) {
            capturedPiece = *opponentBoard & (1ULL << (63 - move.target));  // Store captured piece
            *opponentBoard &= ~(1ULL << (63 - move.target));  // Remove opponent's captured piece
        } else {
            std::cerr << "Error: No opponent piece to capture at destination! Move from " << this->indexToChessPosition(move.source) << " To " << this->indexToChessPosition(move.target) << std::endl;
            
        }
    }

    return capturedPiece;

}

void ChessBoard::undoMove(const Move& move, bool isWhite, ULL* capturedPiece) {
    ULL* pieceBoard = nullptr;
    ULL* opponentBoard = nullptr;

    // Determine which player's piece board was involved in the move
    switch (move.piece) {
        case 'P': pieceBoard = isWhite ? &this->whitePawns : &this->blackPawns; break;
        case 'N': pieceBoard = isWhite ? &this->whiteKnights : &this->blackKnights; break;
        case 'B': pieceBoard = isWhite ? &this->whiteBishops : &this->blackBishops; break;
        case 'R': pieceBoard = isWhite ? &this->whiteRooks : &this->blackRooks; break;
        case 'Q': pieceBoard = isWhite ? &this->whiteQueen : &this->blackQueen; break;
        case 'K': pieceBoard = isWhite ? &this->whiteKing : &this->blackKing; break;
    }

    *pieceBoard &= ~(1ULL << move.target);  // Remove from the target square
    *pieceBoard |= (1ULL << move.source);   // Place back at the original source

    // If the move was a capture, undo the capture by restoring the opponent's piece
    if (move.moveType == 'C') {
        opponentBoard = findOpponentBoard(move, isWhite);

        if (capturedPiece) {
            *opponentBoard |= *capturedPiece;  // Restore the captured piece to the opponent's board
        } else {
            std::cerr << "Error: No captured piece to restore!" << std::endl;
        }
    }
}

bool ChessBoard::isKingInCheck(bool isWhite) {
    // get the king's position
    ULL king = isWhite ? this->whiteKing : this->blackKing;
    int kingPosition = 63 - __builtin_ctzll(king); // Get the position of the king (least significant bit set)

    // get the opponents pieces
    ULL opponentPawns = isWhite ? this->blackPawns : this->whitePawns;
    ULL opponentKnights = isWhite ? this->blackKnights : this->whiteKnights;
    ULL opponentBishops = isWhite ? this->blackBishops : this->whiteBishops;
    ULL opponentRooks = isWhite ? this->blackRooks : this->whiteRooks;
    ULL opponentQueen = isWhite ? this->blackQueen : this->whiteQueen;
    ULL opponentKing = isWhite ? this->blackKing : this->whiteKing;

    ULL allPieces = this->getAllPieces();

    // check for pawn attacks
    vector<Move> pawnMoves = generatePawnMoves(!isWhite);
    for (const Move& move : pawnMoves) {
        if (move.target == kingPosition) return true;
    }

    // check for knight attacks
    vector<Move> knightMoves = generateKnightMoves(!isWhite);
    for (const Move& move : knightMoves) {
        if (move.target == kingPosition) return true;
    }

    // check for bishop attacks 
    vector<Move> bishopMoves = generateBishopMoves(!isWhite, opponentBishops, allPieces);
    for (const Move& move : bishopMoves) {
        if (move.target == kingPosition) return true;
    }

    // check for rook attacks 
    vector<Move> rookMoves = generateRookMoves(!isWhite, opponentRooks, allPieces);
    for (const Move& move : rookMoves) {
        if (move.target == kingPosition) return true;
    }

    vector<Move> queenMoves = generateQueenMoves(!isWhite, opponentQueen, allPieces);
    for (const Move& move : queenMoves) {
        if (move.target == kingPosition) return true;
    }

    // Check for king attacks
    vector<Move> kingMoves = generateKingMoves(!isWhite, opponentKing, allPieces);
    for (const Move& move : kingMoves) {
        if (move.target == kingPosition) return true;
    }

    return false;
}

bool ChessBoard::isCheckmate (bool isWhite) {
    vector<Move> legalMoves = generateLegalMoves(isWhite);
    return legalMoves.size() == 0 && isKingInCheck(isWhite);
}

bool ChessBoard::isGameOver() {
    return isCheckmate(true) || isCheckmate(false);
}

vector<Move> ChessBoard::generateLegalMoves(bool isWhite) {
    vector<Move> moves;
    vector<Move> pawnMoves = generatePawnMoves(isWhite);
    vector<Move> knightMoves = generateKnightMoves(isWhite);
    vector<Move> bishopMoves = generateBishopMoves(isWhite);
    vector<Move> rookMoves = generateRookMoves(isWhite);
    vector<Move> queenMoves = generateQueenMoves(isWhite);
    vector<Move> kingMoves = generateKingMoves(isWhite);

    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());
    moves.insert(moves.end(), knightMoves.begin(), knightMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    moves.insert(moves.end(), queenMoves.begin(), queenMoves.end());
    moves.insert(moves.end(), kingMoves.begin(), kingMoves.end());

   
    vector<Move> legalMoves;

    // remove moves that leave king in check
    for (Move move : moves) {
        // create a temporary board
        ChessBoard tempBoard = *this;

        // simulate the move
        tempBoard.makeMove(move, isWhite);

        // check if in check
        if(!tempBoard.isKingInCheck(isWhite)) {
            legalMoves.push_back(move);
        }

    }

    return legalMoves;
}


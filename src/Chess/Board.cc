#include "Types.hh"
#include "Utils.hh"
#include <sstream>

namespace StrixCC {
    Piece CharToPiece(char ch){
        Color color = islower(ch) ? Color::BLACK : Color::WHITE;
        switch(tolower(ch)){
        case 'p':
            return Piece(PieceType::PAWN, color);
        case 'n':
            return Piece(PieceType::KNIGHT, color);
        case 'b':
            return Piece(PieceType::BISHOP, color);
        case 'r':
            return Piece(PieceType::ROOK, color);
        case 'q':
            return Piece(PieceType::QUEEN, color);
        case 'k':
            return Piece(PieceType::KING, color);
        default:
            return Piece(PieceType::EMPTY, Color::NONE);
        }
    }

    void Board::LoadFEN(std::string FEN){
        std::string FENToken;
        std::stringstream FENStream(FEN);

        // Forsyth-Edwards Notation
        // Forsyth-Edwards Notation, mostly referred to as FEN, is the standard way
        // of representing Chess positions. A FEN looks something like this:
        //
        //     rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
        //
        // It is made up of 6 parts
        //   1. Piece Placements
        //   2. Active Color
        //   3. Castling Rights
        //   4. En-Passant Square
        //   5. Half Move Clock (used for the fifty-move rule)
        //   6. Full Move Count
        // We will discuss each part while parsing them.

        FENStream >> FENToken;

        // First, we will parse the piece placements.
        // How it works is that each '/' represents one rank break.
        // Each letter represents the piece and each digit represents the amount of squares
        // in a row which are empty.
        size_t posidx;
        for (char ch : FENToken){
            if (ch == '/') continue;
            if (isdigit(ch)){
                for (int i = 0; i < (ch - '0'); i++){
                    Pieces[posidx].Reset();
                    posidx++;
                }
            }
            else {
                Pieces[posidx] = CharToPiece(ch);
                if (Pieces[posidx].type == PieceType::EMPTY){
                    printf("Invalid FEN Provided.\n"); exit(0);
                }
                posidx++;
            }
        }

        FENStream >> FENToken;

        // Now the side to move
        if (FENToken == "w" || FENToken == "W") SideToMove = Color::WHITE;
        else if (FENToken == "b" || FENToken == "B") SideToMove = Color::BLACK;

        FENStream >> FENToken;

        // Now the Castling Rights
        if (!FENToken.empty() && FENToken != "-" && FENToken.size() <= 4){
            for (char ch : FENToken){
                if (ch == ' ') continue;
                switch (ch)
                {
                case 'k':
                    if (BRights == QUEENSIDE) BRights = BOTH;
                    else BRights = KINGSIDE;
                    break;
                case 'q':
                    if (BRights == KINGSIDE) BRights = BOTH;
                    else BRights = QUEENSIDE;
                    break;
                case 'K':
                    if (WRights == QUEENSIDE) WRights = BOTH;
                    else WRights = KINGSIDE;
                    break;
                case 'Q':
                    if (WRights == KINGSIDE) WRights = BOTH;
                    else WRights = QUEENSIDE;
                    break;
                default:
                    printf("Invalid FEN Provided.\n"); exit(0);
                }
            }
        }

        FENStream >> FENToken;

        // Now the En-Passant Square
        if (FENToken != "-"){ 
            if (FENToken.size() != 2){ printf("Invalid FEN Provided.\n"); exit(0); }
            EnPassantSquare = ToSquare(FENToken[0] - 'a', FENToken[1] - '1');
            if (EnPassantSquare == Square::UNDEFINED){ printf("Invalid FEN Provided.\n"); exit(0); }
        }

        // Now the half-move clock.
        // This part tracks how many half-moves have passed since the last capture
        // or pawn push. If the clock reaches 100, the game is a draw according to
        // the fifty-move rule as 50 full moves would have passed since the last
        // capture or pawn push.
        FENStream >> HalfMoveClock;

        // Now the full-move count.
        // This part tracks the amount of full-moves that have been made since the
        // start of the game.
        FENStream >> FullMoveCount;
    }
};
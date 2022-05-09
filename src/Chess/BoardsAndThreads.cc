#include "BoardsAndThreads.hh"
#include "Utils.hh"
#include "../engine.hh"
#include <cstring>
#include <sstream>

void Board::Load(const char* FEN){
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    // The comment above is the FEN for the starting position. We can use it as a reference
    // to understand how FEN works.
    
    // Check if the FEN is longer than the longest valid FEN
    if (strlen(FEN) > 92) exit(0);

    std::string token = "";
    int count = 0, posidx = 0;
    for (int i = 0; i < strlen(FEN); i++){
        if (FEN[i] == '/') continue;
        if (FEN[i] == ' ' || i == strlen(FEN) - 1){
            if (i == strlen(FEN) - 1) token += FEN[i];
            if (count == 2){
                // Parse the castling rights
                if (token == "KQkq"){
                    WhiteCastle = BlackCastle = true;
                }
                else if (token == "KQ"){
                    WhiteCastle = true;
                }
                else if (token == "kq"){
                    BlackCastle = true;
                }
                else exit(0);
            }
            else if (count == 3){
                // Parse the en passant square
                if (token != "-"){
                    if (strlen(token.c_str()) != 2) exit(0);
                    int file = (int)token[0] - 'a', rank = '8' - (int)token[1];
                    if (file <= 7 && file >= 0 && rank <= 7 && rank >= 0){
                        EnPassantSquare = (Square)(rank * 8 + file);
                    }
                    else exit(0);
                }
            }
            else if (count == 4){
                // Parse the half move clock
                std::stringstream sstream(token);
                sstream >> HalfMoveClock;
                if (HalfMoveClock < 0 || HalfMoveClock > 100) exit(0);
            }
            else if (count == 5){
                // Parse the full move count
                std::stringstream sstream(token);
                sstream >> FullMoveCount;
            }
            token = ""; // Clear the variable
            count++;
            continue;
        }
        else token += FEN[i];

        if (count == 0){
            // Parse the position data
            if (isdigit(FEN[i])){
                int dgt = (int)FEN[i] - 48;
                if (!dgt || dgt > 8) exit(0);
                for (int cnt = 0; cnt < dgt; cnt++){
                    if (posidx > 63) exit(0);
                    Pieces[posidx].color = Color::NONE;
                    Pieces[posidx].type = _PieceType::NONE;
                    Utils::ClearBit(&Occupancy, posidx);
                    posidx++;
                }
            }
            else {
                Piece piece = Utils::CharToPiece(FEN[i]);
                if (piece.color == Color::NONE || posidx > 63) exit(0);
                Pieces[posidx] = piece;
                Utils::SetBit(&Occupancy, posidx);
                posidx++;
            }
        }
        else if (count == 1){
            // Parse the active color
            if (FEN[i] == 'w'){
                ActiveColor = Color::WHITE;
            }
            else if (FEN[i] == 'b'){
                ActiveColor = Color::BLACK;
            }
            else exit(0);
        }
    }
}
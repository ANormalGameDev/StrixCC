#include "BoardsAndThreads.hh"
#include "Utils.hh"
#include <cstring>

void Board::Load(const char* FEN){
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    // The comment above is the FEN for the starting position. We can use it as a reference
    // to understand how FEN works.
    const char* token;
    int count = 0, posidx = 0;
    for (int i = 0; i < strlen(FEN); i++){
        if (FEN[i] == '/') continue;
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
            else if (FEN[i] != ' '){
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
        }

        if (FEN[i] == ' '){
            // if (count == 2){
            //     // Parse the castling rights
            //     if (token == "KQkq"){
            //         WhiteCastle = BlackCastle = true;
            //     }
            //     else if (token == "KQ"){
            //         WhiteCastle = true;
            //     }
            //     else if (token == "kq"){
            //         BlackCastle = true;
            //     }
            //     else exit(0);
            // }
            // else if (count == 3){
            //     // Parse the en passant square
            // }
            // else if (count == 4){
            //     // Parse the half move clock
            // }
            // else if (count == 5){
            //     // Parse the full move count
            // }
            token = ""; // Clear the variable
            count++;
            continue;
        }
        else token += FEN[i];
    }
}
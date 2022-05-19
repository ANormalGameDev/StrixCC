#include "Types.hh"
#include "Utils.hh"
#include <sstream>
#include <cstring>

namespace StrixCC {
    const std::string PieceToChar = ".pnbrqkPNBRQK";
    const std::string FileToChar = "abcdefgh";
    const std::string RankToChar = "12345678";

    Piece CharToPiece(char ch){
        Color color = isupper(ch) ? Color::WHITE : Color::BLACK;
        switch (tolower(ch))
        {
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

    void Board::Load(std::string FEN){
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
        size_t posidx = 0;
        for (char pchar : FENToken){
            if (pchar == '/') continue;
            if (isdigit(pchar)){
                for (int i = 0; i < pchar - '0'; i++){ Pieces[posidx].Clear(); Occupancy &= ~(1ULL << posidx); posidx++; }
            }
            else {
                Piece p = CharToPiece(pchar);
                if (!p.Occupied()) ThrowError("FEN", "Invalid Piece Char Found in FEN.");
                Pieces[posidx] = p; Occupancy |= (1ULL << posidx); posidx++;
            }
        }

        FENStream >> FENToken;

        // Now the side to move
        if (FENToken == "w" || FENToken == "W") SideToMove = Color::WHITE;
        else if (FENToken == "b" || FENToken == "B") SideToMove = Color::BLACK;
        else ThrowError("FEN", "Invalid Color Token Found in FEN.");

        FENStream >> FENToken;

        // Now the castling rights.
        // 'K' represents that White can castle kingside, 'Q' represents that White can
        // castle queenside and it's the same for Black but it uses lowercase characters.
        if (FENToken != "-"){
            for (char crchar : FENToken){
                if (crchar == 'K') WRights.Set(true, true);
                else if (crchar == 'Q') WRights.Set(false, true);
                else if (crchar == 'k') BRights.Set(true, true);
                else if (crchar == 'q') BRights.Set(false, true);
                else ThrowError("FEN", "Invalid Castling Rights Char Found in FEN.");
            }
        }

        FENStream >> FENToken;

        // Now we parse the En Passant Square
        if (FENToken != "-") EnPassantSquare = ToSquare(FENToken[0] - 'a', FENToken[1] - '1');
        else EnPassantSquare = Square::NULLSQ;

        // And finally the Half Move Clock and the Full Move Count.
        // The Half Move Clock is used for the fifty-move rule where a draw can be claimed
        // if 50 full-moves have been made since the last pawn push or capture. Since 1 full
        // move contains of 2 half moves, the game will be considered a draw when the half
        // move clock reaches 100.
        FENStream >> HalfMoveClock;
        FENStream >> FullMoveCount;
    }

    void Board::Print(){
        Piece p;
        for (int r = 0; r < 8; r++){
            printf(" %d ", 8 - r);
            for (int f = 0; f < 8; f++){
                p = Pieces[r * 8 + f];
                printf(" %c", p.color == Color::WHITE ? PieceToChar[6 + p.type] : PieceToChar[p.type]);
            }
            printf("\n");
        }
        printf("\n    A B C D E F G H\n");
    }

    std::string Board::GetFEN(){
        std::string FEN;
        int dgt = 0;
        for (int r = 0; r < 8; r++){
            for (int f = 0; f < 8; f++){
                if (Pieces[r * 8 + f].type == PieceType::EMPTY){ dgt++; continue; }
                if (dgt != 0){
                    for (char ch : std::to_string(dgt)){
                        FEN.push_back(ch);
                    }
                    dgt = 0;
                }
                FEN.push_back(PieceToChar[Pieces[r * 8 + f].color == Color::WHITE ? 6 + Pieces[r * 8 + f].type : Pieces[r * 8 + f].type]);
            }
            if (dgt != 0){
                for (char ch : std::to_string(dgt)){
                    FEN.push_back(ch);
                }
                dgt = 0;
            }
            FEN.push_back('/');
        }
        FEN.pop_back();
        FEN.push_back(' ');

        FEN.push_back(SideToMove == Color::WHITE ? 'w' : 'b');
        FEN.push_back(' ');

        if (WRights.Kingside) FEN.push_back('K');
        if (WRights.Queenside) FEN.push_back('Q');
        if (BRights.Kingside) FEN.push_back('k');
        if (BRights.Queenside) FEN.push_back('q');
        if (FEN[FEN.size() - 1] == ' ') FEN.push_back('-');
        FEN.push_back(' ');

        if (EnPassantSquare != Square::NULLSQ){
            FEN.push_back(FileToChar[FileOf(EnPassantSquare)]);
            FEN.push_back(RankToChar[RankOf(EnPassantSquare)]);
        }
        else FEN.push_back('-');
        FEN.push_back(' ');

        for (char ch : std::to_string(HalfMoveClock)){
            FEN.push_back(ch);
        }
        FEN.push_back(' ');

        for (char ch : std::to_string(FullMoveCount)){
            FEN.push_back(ch);
        }

        return FEN;
    }
};
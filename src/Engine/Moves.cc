#include "Types.hh"
#include "Utils.hh"

namespace StrixCC {
    bool Board::Validate(Move move){
        
    }

    std::vector<Move> Board::Generate(MoveGenerationMode Mode){
        std::vector<Move> generated;
        for (size_t square = Square::A8; square <= Square::H1; square++){
            if (Pieces[square].color != SideToMove) continue;
            switch (Pieces[square].type)
            {
            case PieceType::PAWN:
                if (SideToMove == Color::WHITE && Pieces[square - 8].type == PieceType::EMPTY){
                    Move move = Move((Square)square, (Square)(square - 8), MoveType::STANDARD);
                    if (Mode == PSEUDO_LEGAL)
                        generated.push_back(move);
                    else if (Mode == LEGAL)
                        if (Validate(move)) generated.push_back(move);
                    if (RankOf(square) == 1 && Pieces[square - 16].type == PieceType::EMPTY){
                        Move _move = Move((Square)square, (Square)(square - 16), MoveType::STANDARD);
                        if (Mode == PSEUDO_LEGAL)
                            generated.push_back(_move);
                        else if (Mode == LEGAL)
                            if (Validate(_move)) generated.push_back(_move);
                    }
                }
                if (SideToMove == Color::BLACK && Pieces[square + 8].type == PieceType::EMPTY){
                    Move move = Move((Square)square, (Square)(square + 8), MoveType::STANDARD);
                    if (Mode == PSEUDO_LEGAL)
                        generated.push_back(move);
                    else if (Mode == LEGAL)
                        if (Validate(move)) generated.push_back(move);
                    if (RankOf(square) == 6 && Pieces[square + 16].type == PieceType::EMPTY){
                        Move _move = Move((Square)square, (Square)(square + 16), MoveType::STANDARD);
                        if (Mode == PSEUDO_LEGAL)
                            generated.push_back(_move);
                        else if (Mode == LEGAL)
                            if (Validate(_move)) generated.push_back(_move);
                    }
                }
                break;
            }
        }
    }
};
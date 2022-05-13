#include "Moves.hh"
#include "Bitboards.hh"

namespace StrixCC {
    namespace MoveGen {
        std::vector<Move> GeneratePseudoLegalMoves(){
            std::vector<Move> generated;
            for (Square square = Square::A1; square <= Square::H8; square++){
                ModifiablePiece& piece = MainBoard.Pieces[square];
                if (piece.color != MainBoard.SideToMove) continue;
                if (piece.type == PieceType::PAWN){
                    uint64 attacks = PawnAttacks(square, piece.color);
                    while (attacks){
                        size_t idx = __builtin_ctzl(attacks);
                        if (GetBit(MainBoard.Occupancy, idx) && MainBoard.Pieces[idx].color != piece.color && piece.type != PieceType::EMPTY)
                            generated.push_back(Move(square, (Square)idx, MoveType::CAPTURE));
                        else if (idx == MainBoard.EnPassantSquare)
                            generated.push_back(Move(square, (Square)idx, MoveType::CAPTURE));
                        attacks ^= attacks & -attacks;
                    }
                    if (piece.color == Color::WHITE){
                        if (MainBoard.Pieces[square + NORTH].type == PieceType::EMPTY){
                            generated.push_back(Move(square, (Square)(square + NORTH), STANDARD));
                            if (RankOf(square) == 6 && MainBoard.Pieces[square + NORTH + NORTH].type == PieceType::EMPTY){
                                generated.push_back(Move(square, (Square)(square + NORTH + NORTH), STANDARD));
                            }
                        }
                    }
                    else {
                        if (MainBoard.Pieces[square + SOUTH].type == PieceType::EMPTY){
                            generated.push_back(Move(square, (Square)(square + SOUTH), STANDARD));
                            if (RankOf(square) == 1 && MainBoard.Pieces[square + SOUTH + SOUTH].type == PieceType::EMPTY){
                                generated.push_back(Move(square, (Square)(square + SOUTH + SOUTH), STANDARD));
                            }
                        }
                    }
                }
                else {
                    uint64 attacks = GetAttacks(piece.type, square, MainBoard.Occupancy);
                    while (attacks){
                        size_t idx = __builtin_ctzl(attacks);
                        if (GetBit(MainBoard.Occupancy, idx)){
                            if (MainBoard.Pieces[idx].color != piece.color) generated.push_back(Move(square, (Square)idx, MoveType::CAPTURE));
                        }
                        else
                            generated.push_back(Move(square, (Square)idx, MoveType::STANDARD));
                        attacks ^= attacks & -attacks;
                    }
                }
            }
            return generated;
        }

        std::vector<Move> Generate(MoveGenerationMode Mode){
            std::vector<Move> pseudoLegalMoves = GeneratePseudoLegalMoves();
            switch (Mode)
            {
            case MoveGenerationMode::PSEUDO_LEGAL_ONLY:
                return pseudoLegalMoves;
            default:
                std::vector<Move> nullVec;
                return nullVec;
            }
        }
    };
};
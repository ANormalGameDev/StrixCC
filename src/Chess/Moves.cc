#include "Moves.hh"
#include "../engine.hh"

std::vector<Move> MoveGenerator::GeneratePsuedoLegalMoves(Board board){
    std::vector<Move> moveVec;
    Piece* Pieces = board.GetPieces();
    for (int square = Square::A8; square <= Square::H1; square++){
        Piece& piece = Pieces[square];
        if (piece.color != board.GetActiveColor()) continue;
        switch (piece.type){
            // Pawn Moves
            case _PieceType::PAWN:
            {
                uint64 pMoves = PawnAttacks((Square)square, board.GetActiveColor());
                while (pMoves){
                    int r = __builtin_ctzl(pMoves);
                    if (Utils::GetBit(pMoves, r) && Pieces[r].color != Color::NONE && Pieces[r].color != board.GetActiveColor())
                        moveVec.push_back(Move(MoveType::CAPTURE, (Square)square, (Square)r));
                    pMoves ^= pMoves & -pMoves;
                }
                if (board.GetActiveColor() == Color::WHITE)
                    if (square - 8 >= Square::A8 && Pieces[square - 8].type == _PieceType::NONE){
                        moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)(square - 8)));
                        if (Utils::GetRankOf(square) == 2 && square - 16 >= Square::A8 && Pieces[square - 16].type == _PieceType::NONE){
                            moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)(square - 16)));
                        }
                    }
                else if (board.GetActiveColor() == Color::BLACK){
                    if (square + 8 <= Square::H1 && Pieces[square + 8].type == _PieceType::NONE){
                        moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)(square + 8)));
                        if (Utils::GetRankOf(square) == 6 && square + 16 <= Square::H1 && Pieces[square + 16].type == _PieceType::NONE){
                            moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)(square + 16)));
                        }
                    }
                }
                break;
            }

            // Knight Moves
            case _PieceType::KNIGHT:
            {
                uint64 nMoves = KnightAttacks((Square)square);
                while (nMoves){
                    int r = __builtin_ctzl(nMoves);
                    if (Utils::GetBit(nMoves, r) && Pieces[r].color != board.GetActiveColor()){
                        if (Pieces[r].color == Color::NONE)
                            moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)r));
                        else
                            moveVec.push_back(Move(MoveType::CAPTURE, (Square)square, (Square)r));
                    }
                    nMoves ^= nMoves & -nMoves;
                }
                break;
            }
            
            // Bishop Moves
            case _PieceType::BISHOP:
            {
                uint64 bMoves = BishopAttacks((Square)square, board.GetOccupancy());
                while (bMoves){
                    int r = __builtin_ctzl(bMoves);
                    if (Utils::GetBit(bMoves, r) && Pieces[r].color != board.GetActiveColor()){
                        if (Pieces[r].color == Color::NONE)
                            moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)r));
                        else
                            moveVec.push_back(Move(MoveType::CAPTURE, (Square)square, (Square)r));
                    }
                    bMoves ^= bMoves & -bMoves;
                }
                break;
            }

            // Rook Moves
            case _PieceType::ROOK:
            {
                uint64 rMoves = RookAttacks((Square)square, board.GetOccupancy());
                while (rMoves){
                    int r = __builtin_ctzl(rMoves);
                    if (Utils::GetBit(rMoves, r) && Pieces[r].color != board.GetActiveColor()){
                        if (Pieces[r].color == Color::NONE)
                            moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)r));
                        else
                            moveVec.push_back(Move(MoveType::CAPTURE, (Square)square, (Square)r));
                    }
                    rMoves ^= rMoves & -rMoves;
                }
                break;
            }
            
            // Queen Moves
            case _PieceType::QUEEN:
            {
                uint64 qMoves = BishopAttacks((Square)square, board.GetOccupancy());
                while (qMoves){
                    int r = __builtin_ctzl(qMoves);
                    if (Utils::GetBit(qMoves, r) && Pieces[r].color != board.GetActiveColor()){
                        if (Pieces[r].color == Color::NONE)
                            moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)r));
                        else
                            moveVec.push_back(Move(MoveType::CAPTURE, (Square)square, (Square)r));
                    }
                    qMoves ^= qMoves & -qMoves;
                }
                break;
            }
            
            // King Moves
            case _PieceType::KING:
            {
                uint64 kMoves = KingAttacks((Square)square);
                while (kMoves){
                    int r = __builtin_ctzl(kMoves);
                    if (Utils::GetBit(kMoves, r) && Pieces[r].color != board.GetActiveColor()){
                        if (Pieces[r].color == Color::NONE)
                            moveVec.push_back(Move(MoveType::NORMAL, (Square)square, (Square)r));
                        else
                            moveVec.push_back(Move(MoveType::CAPTURE, (Square)square, (Square)r));
                    }
                    kMoves ^= kMoves & -kMoves;
                }
                break;
            }
        }
    }
    return moveVec;
}



uint64 MoveGenerator::RookAttacks(Square square, uint64 occupancy){
    Magic& magic = RMagics[square];
    return magic.AttackTable[magic.GetIndexFromOccupancy(occupancy)];
}

uint64 MoveGenerator::BishopAttacks(Square square, uint64 occupancy){
    Magic& magic = BMagics[square];
    return magic.AttackTable[magic.GetIndexFromOccupancy(occupancy)];
}

uint64 MoveGenerator::QueenAttacks(Square square, uint64 occupancy){
    return (RookAttacks(square, occupancy) | BishopAttacks(square, occupancy));
}

uint64 MoveGenerator::KnightAttacks(Square square){
    return NAttacks[square];
}

uint64 MoveGenerator::KingAttacks(Square square){
    return KAttacks[square];
}

uint64 MoveGenerator::PawnAttacks(Square square, Color color){
    return (color == Color::WHITE ? PAttacks[64 + square] : PAttacks[square]);
}
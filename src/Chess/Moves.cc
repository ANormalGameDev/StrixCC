#include "Moves.hh"
#include "../engine.hh"

std::vector<Move> MoveGenerator::Generate(Board board){
    
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
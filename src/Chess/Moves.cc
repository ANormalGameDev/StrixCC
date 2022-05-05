#include "Moves.hh"
#include "../engine.hh"

uint64 MoveGenerator::RookAttacks(Square square, uint64 occupancy){
    Magic& magic = RMagics[square];
    return magic.AttackTable[magic.GetIndexFromOccupancy(occupancy)];
}

uint64 MoveGenerator::BishopAttacks(Square square, uint64 occupancy){
    Magic& magic = BMagics[square];
    return magic.AttackTable[magic.GetIndexFromOccupancy(occupancy)];
}
#ifndef MAGICS_HH
#define MAGICS_HH

#include "BoardsAndThreads.hh"
#include "PrestoredMagics.hh"

struct Magic {
    uint64* AttackTable;
    uint64  Mask;
    uint64  Magic;
    int Shift;
    uint64 GetIndexFromOccupancy(uint64 occupancy){
        return ((occupancy & Mask) * Magic) >> Shift;
    }
};

#endif
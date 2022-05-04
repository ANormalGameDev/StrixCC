#ifndef MAGICS_HH
#define MAGICS_HH

#include "BoardsAndThreads.hh"

typedef unsigned long long uint64;

struct Magic {
    uint64* AttackTable;
    uint64  Mask;
    uint64  Magic;
    int Shift;
    uint64 GetIndexFromOccupancy(uint64 occupancy){
        return ((occupancy & Mask) * Magic) >> Shift;
    }
};

class MagicSearch {
    public:
        uint64 GetMagic(Square square, bool bishop);
};

#endif
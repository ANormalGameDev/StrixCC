#ifndef __BITBOARDS_HH__
#define __BITBOARDS_HH__

#include "Types.hh"

namespace StrixCC {
    namespace Bitboards {
        constexpr uint64 NotAFile = 18374403900871474942ULL;
        constexpr uint64 NotHFile = 9187201950435737471ULL;
        constexpr uint64 NotHGFile = 4557430888798830399ULL;
        constexpr uint64 NotABFile = 18229723555195321596ULL;

        extern uint64 KingTable[64], KnightTable[64];

        extern uint64 RookTable[0x19000], BishopTable[0x1480];
        extern SMagic RookMagics[64], BishopMagics[64];

        void Init();
    };

    uint64 BishopAttacks(Square square, uint64 occupancy);
    uint64 RookAttacks(Square square, uint64 occupancy);
    uint64 QueenAttacks(Square square, uint64 occupancy);

    uint64 KingAttacks(Square square);
    uint64 KnightAttacks(Square square);

    uint64 PawnAttacks(Square square, Color color);
};

#endif
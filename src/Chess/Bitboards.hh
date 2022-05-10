#ifndef BITBOARDS_HH
#define BITBOARDS_HH

#include "Types.hh"
#include "Utils.hh"
#include <bit>

namespace StrixCC {
    namespace Bitboards {
        constexpr uint64 edges = 18411139144890810879ULL;

        extern SMagic RMagics[64], BMagics[64];
        extern uint64 RAttacks[0x19000], BAttacks[0x1480];

        void Init();
    };

    constexpr uint64 BishopAttacks(Square square, uint64 occupancy){
        SMagic magic = Bitboards::BMagics[square];
        return magic.Table[magic.GetIndex(occupancy)];
    };
    constexpr uint64 RookAttacks(Square square, uint64 occupancy){
        SMagic magic = Bitboards::RMagics[square];
        return magic.Table[magic.GetIndex(occupancy)];
    }
    constexpr uint64 QueenAttacks(Square square, uint64 occupancy){
        return RookAttacks(square, occupancy) | BishopAttacks (square, occupancy);
    }

    template<PieceType Type>
    constexpr uint64 GetAttacks(Square square, uint64 occupancy){
        switch (Type)
        {
        case PieceType::BISHOP:
            return BishopAttacks(square, occupancy);
        case PieceType::ROOK:
            return RookAttacks(square, occupancy);
        case PieceType::QUEEN:
            return QueenAttacks(square, occupancy);
        default:
            return 0ULL;
        }
    }
};

#endif
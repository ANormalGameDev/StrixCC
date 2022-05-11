#ifndef __BITBOARDS_HH
#define __BITBOARDS_HH

#include "Types.hh"
#include "Utils.hh"
#include <bit>

namespace StrixCC {
    namespace Bitboards {
        constexpr uint64 edges = 18411139144890810879ULL;

        constexpr uint64 NotAFile = 18374403900871474942ULL;
        constexpr uint64 NotHFile = 9187201950435737471ULL;
        constexpr uint64 NotHGFile = 4557430888798830399ULL;
        constexpr uint64 NotABFile = 18229723555195321596ULL;

        extern uint64 NAttacks[64], KAttacks[64];

        extern SMagic RMagics[64], BMagics[64];
        extern uint64 RAttacks[0x19000], BAttacks[0x1480];

        void Init();
    };

    // Attacks Lookup Functions for Slider Pieces
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

    // Attacks Lookup Functions for Other Pieces
    constexpr uint64 KnightAttacks(Square square){
        uint64 attacks = Bitboards::NAttacks[square];
        return attacks;
    }
    constexpr uint64 KingAttacks(Square square){
        uint64 attacks = Bitboards::KAttacks[square];
        return attacks;
    }

    // Attacks Generation Functions for Other Other Pieces
    template<Color color>
    constexpr uint64 PawnAttacks(Square square){
        uint64 bb = 0ULL, attacks = 0ULL;
        SetBit(&bb, square);
        if (color == Color::BLACK){
            if ((bb >> 9) & Bitboards::NotHFile) attacks |= (bb >> 9);
            if ((bb >> 7) & Bitboards::NotAFile) attacks |= (bb >> 7);
        }
        else if (color == Color::WHITE){
            if ((bb << 9) & Bitboards::NotHFile) attacks |= (bb << 9);
            if ((bb << 7) & Bitboards::NotAFile) attacks |= (bb << 7);
        }
        return attacks;
    }

    // Function to get the attacks for any piece other than pawns.
    // Those critters are not going to be added in this function.
    template<PieceType Type>
    constexpr uint64 GetAttacks(Square square, uint64 occupancy){
        switch (Type)
        {
        // Other Pieces
        case PieceType::KNIGHT:
            return KnightAttacks(square);
        case PieceType::KING:
            return KingAttacks(square);
        
        // Slider Pieces
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
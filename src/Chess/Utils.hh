#ifndef __UTILS_HH
#define __UTILS_HH

#include "Types.hh"

namespace StrixCC {
    constexpr bool GetBit(uint64 bb, Square square){ return bb & (1ULL << square); }
    constexpr bool GetBit(uint64 bb, int square){ return bb & (1ULL << square); }
    constexpr void SetBit(uint64* bb, Square square){ (*bb) |= (1ULL << square); }
    constexpr void SetBit(uint64* bb, int square){ (*bb) |= (1ULL << square); }

    constexpr Square ToSquare(int file, int rank){
        if (file > 7 || file < 0 || rank > 7 || rank < 0) return Square::UNDEFINED;
        else return (Square)(rank * 8 + file);
    }

    constexpr int RankOf(Square square) { return square / 8; }
    constexpr int RankOf(int square) { return square / 8; }
    constexpr int FileOf(Square square) { return square % 8; }
    constexpr int FileOf(int square) { return square % 8; }

    constexpr void PrintBitboard(uint64 bitboard)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                int square = rank * 8 + file;
                if (!file)
                    printf(" %d ", rank + 1);
                printf(" %d", GetBit(bitboard, square) ? 1 : 0);
            }
            printf("\n");
        }
        printf("\n    a b c d e f g h\n\n");
        printf(" Bitboard: %llud\n\n", bitboard);
    }
};

#endif
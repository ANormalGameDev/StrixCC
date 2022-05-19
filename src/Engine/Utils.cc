#include "Utils.hh"

namespace StrixCC {
    void ThrowError(const char* Header, const char* Message){
        printf("[%s] %s\n", Header, Message);
        exit(0);
    }

    Square ToSquare(int file, int rank){
        return (Square)(rank * 8 + file);
    }

    void SetBit(uint64* bb, int square){ (*bb) |= (1ULL << square); }
    void ClearBit(uint64* bb, int square){ (*bb) &= ~(1ULL << square); }
    bool GetBit(uint64 bb, int square){ return bb & (1ULL << square); }

    int RankOf(int square) { return square / 8; }
    int FileOf(int square) { return square % 8; }

    void PrintBitboard(uint64 bb){
        for (int r = 0; r < 8; r++){
            printf(" %d ", 8 - r);
            for (int f = 0; f < 8; f++){
                printf(" %d", (GetBit(bb, (r * 8 + f)) ? 1 : 0));
            }
            printf("\n");
        }
        printf("\n    A B C D E F G H\n");
        printf("\n Bitboard: %lluULL\n", bb);
    }
};
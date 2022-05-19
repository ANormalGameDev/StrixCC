#ifndef __UTILS_HH__
#define __UTILS_HH__

#include "Types.hh"

namespace StrixCC {
    void ThrowError(const char* Header, const char* Message);
    Square ToSquare(int file, int rank);
    void SetBit(uint64* bb, int square);
    void ClearBit(uint64* bb, int square);
    bool GetBit(uint64 bb, int square);

    void PrintBitboard(uint64 bb);

    // This function uses index numbering i.e. 0 to 7 and NOT 1 to 8
    int RankOf(int square);
    // This function uses index numbering i.e. 0 to 7 and NOT 1 to 8
    int FileOf(int square);
};

#endif
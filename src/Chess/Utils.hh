#ifndef UTILS_HH
#define UTILS_HH

#include "BoardsAndThreads.hh"
#include "Magics.hh"

class Utils {
    public:
        static void SetBit(uint64* bb, Square square) { (*bb) |= (1ULL << square); }
        static bool GetBit(uint64 bb, Square square) { return bb & (1ULL << square); }
        static void SetBit(uint64* bb, int square){
            if (square >= 0 && square < 64) (*bb) |= (1ULL << square);
            else return;
        }
        static bool GetBit(uint64 bb, int square){
            if (square >= 0 && square < 64) return bb & (1ULL << square);
            else return false;
        }
        static int PopCount(uint64 bb){
            int count = 0;
            for (int i = 0; i < 64; i++){
                if (GetBit(bb, i)) count++;
            }
            return count;
        }
        static void PrintBitboard(uint64 bitboard)
        {
            printf("\n");

            // loop over board ranks
            for (int rank = 0; rank < 8; rank++)
            {
                // loop over board files
                for (int file = 0; file < 8; file++)
                {
                    // convert file & rank into square index
                    int square = rank * 8 + file;
                    
                    // print ranks
                    if (!file)
                        printf("  %d ", 8 - rank);
                    
                    // print bit state (either 1 or 0)
                    printf(" %d", GetBit(bitboard, square) ? 1 : 0);
                    
                }
                
                // print new line every rank
                printf("\n");
            }
            
            // print board files
            printf("\n     a b c d e f g h\n\n");
            
            // print bitboard as unsigned decimal number
            printf("     Bitboard: %llud\n\n", bitboard);
        }
};

#endif
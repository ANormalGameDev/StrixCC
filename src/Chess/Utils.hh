#ifndef UTILS_HH
#define UTILS_HH

#include "BoardsAndThreads.hh"
#include "Magics.hh"

class Utils {
    public:
        static int GetRankOf(Square square){ return 8 - (int)(square / 8); }
        static int GetRankOf(int square){ return 8 - (int)(square / 8); }
        static int GetFileOf(Square square){ return (int)(square % 8) + 1; }
        static int GetFileOf(int square){ return (int)(square % 8) + 1; }
        static void SetBit(uint64* bb, Square square) { (*bb) |= (1ULL << square); }
        static bool GetBit(uint64 bb, Square square) { return bb & (1ULL << square); }
        static void ClearBit(uint64* bb, Square square) { (*bb) &= ~(1ULL << square); }
        static void SetBit(uint64* bb, int square){
            if (square >= 0 && square < 64) (*bb) |= (1ULL << square);
        }
        static bool GetBit(uint64 bb, int square){
            if (square >= 0 && square < 64) return bb & (1ULL << square);
            else return false;
        }
        static void ClearBit(uint64* bb, int square) {
            if (square >= 0 && square < 64) (*bb) &= ~(1ULL << square);
        }
        static int PopCount(uint64 bb){
            int count = 0;
            for (int i = 0; i < 64; i++){
                if (GetBit(bb, i)) count++;
            }
            return count;
        }
        static Piece CharToPiece(char ch){
            switch (ch){
                // Black Pieces
                case 'p':
                    return Piece(Color::BLACK, _PieceType::PAWN);
                case 'n':
                    return Piece(Color::BLACK, _PieceType::KNIGHT);
                case 'b':
                    return Piece(Color::BLACK, _PieceType::BISHOP);
                case 'r':
                    return Piece(Color::BLACK, _PieceType::ROOK);
                case 'q':
                    return Piece(Color::BLACK, _PieceType::QUEEN);
                case 'k':
                    return Piece(Color::BLACK, _PieceType::KING);
                
                // White Pieces
                case 'P':
                    return Piece(Color::WHITE, _PieceType::PAWN);
                case 'N':
                    return Piece(Color::WHITE, _PieceType::KNIGHT);
                case 'B':
                    return Piece(Color::WHITE, _PieceType::BISHOP);
                case 'R':
                    return Piece(Color::WHITE, _PieceType::ROOK);
                case 'Q':
                    return Piece(Color::WHITE, _PieceType::QUEEN);
                case 'K':
                    return Piece(Color::WHITE, _PieceType::KING);
                
                // Invalid Char
                default:
                    return Piece(Color::NONE ,_PieceType::NONE);
            }
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
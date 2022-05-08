#ifndef MOVES_HH
#define MOVES_HH

#include "BoardsAndThreads.hh"
#include "Magics.hh"
#include "Utils.hh"

enum class MoveType {
    NORMAL, CAPTURE, CASTLE
};

struct Move {
    MoveType Type;
    Square From;
    Square To;
    Move(MoveType type, Square from, Square to){
        Type = type;
        From = from;
        To = to;
    }
};

class MoveGenerator {
    private:
        Magic RMagics[64], BMagics[64];
        uint64 RAttacks[0x19000], BAttacks[0x1480], NAttacks[64], KAttacks[64], PAttacks[128];
    public:
        void InitMagicBitboards();
        uint64 RookAttacks(Square square, uint64 occupancy);
        uint64 BishopAttacks(Square square, uint64 occupancy);
        uint64 QueenAttacks(Square square, uint64 occupancy);
        uint64 KnightAttacks(Square square);
        uint64 KingAttacks(Square square);
        uint64 PawnAttacks(Square square, Color color);
        std::vector<Move> GeneratePsuedoLegalMoves(Board board);
};

#endif
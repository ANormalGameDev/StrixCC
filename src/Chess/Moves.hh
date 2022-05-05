#ifndef MOVES_HH
#define MOVES_HH

#include "BoardsAndThreads.hh"
#include "Magics.hh"
#include "Utils.hh"

struct Move {
    Square from;
    Square to;
    Move(Square _from, Square _to){
        from = _from;
        to = _to;
    }
};

class MoveGenerator {
    private:
        Magic RMagics[64], BMagics[64];
        uint64 RAttacks[0x19000], BAttacks[0x1480];
    public:
        void InitMagicBitboards();
        uint64 RookAttacks(Square square, uint64 occupancy);
        uint64 BishopAttacks(Square square, uint64 occupancy);
        uint64 QueenAttacks(Square square, uint64 occupancy);
        std::vector<Move> Generate(Board board);
};

#endif
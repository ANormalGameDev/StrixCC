#include "Engine.hh"
#include <iostream>

namespace StrixCC {
    void Main(){
        Bitboards::Init();
        // // For Testing Purposes
        // uint64 testoccupancy = 0ULL;
        // // SetBit(&testoccupancy, Square::C5);
        // PrintBitboard(GetAttacks<PieceType::KNIGHT>(Square::C2, testoccupancy));
    }
};
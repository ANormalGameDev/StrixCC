#include <iostream>
#include "engine.hh"

EngineController controller;
int main(){
    controller.Initialize();
    
    // For Testing Purposes
    std::cout << "Getting Requested Attack\n";
    uint64 TestOccupancy = 0ULL;
    Utils::SetBit(&TestOccupancy, Square::C5);
    Utils::SetBit(&TestOccupancy, Square::E8);
    Utils::SetBit(&TestOccupancy, Square::F5);
    Utils::SetBit(&TestOccupancy, Square::B2);
    Utils::SetBit(&TestOccupancy, Square::E3);
    Utils::PrintBitboard(TestOccupancy);
    uint64 att = controller.GetMoveGenerator().QueenAttacks(Square::E5, TestOccupancy);
    Utils::PrintBitboard(att);
}
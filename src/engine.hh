#ifndef ENGINE_HH
#define ENGINE_HH

#include "Chess/BoardsAndThreads.hh"
#include "Chess/Moves.hh"
#include "Chess/Magics.hh"

class EngineController {
    private:
        BoardThreadManager boardThreadManager;
        MoveGenerator moveGenerator;
        MagicSearch magicSearch;
    public:
        MagicSearch GetMagicFinder(){ return magicSearch; }
        MoveGenerator GetMoveGenerator() { return moveGenerator; }
        void Initialize(){
            moveGenerator.InitMagicBitboards();
        }
};

extern EngineController controller;

#endif
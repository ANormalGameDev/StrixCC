#ifndef ENGINE_HH
#define ENGINE_HH

#include "Chess/BoardsAndThreads.hh"
#include "Chess/Moves.hh"
#include "Chess/Magics.hh"

extern MoveGenerator MoveGen;

class EngineController {
    private:
        BoardThreadManager boardThreadManager;
    public:
        BoardThreadManager GetBoardThreadManager() { return boardThreadManager; }
        void Initialize(){
        }
};

extern EngineController controller;

#endif
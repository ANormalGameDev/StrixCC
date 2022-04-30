#pragma once

#include "Chess/BoardsAndThreads.hh"

class EngineController {
    private:
        BoardThreadManager boardThreadManager;
    public:
        BoardThreadManager GetBoardThreadManager() { return boardThreadManager; }
};
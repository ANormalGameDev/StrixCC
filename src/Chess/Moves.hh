#ifndef __MOVES_HH
#define __MOVES_HH

#include "Types.hh"

namespace StrixCC {
    namespace MoveGen {
        std::vector<Move> Generate(MoveGenerationMode Mode);
    };
};

#endif
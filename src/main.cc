#include <iostream>
#include "engine.hh"

EngineController controller;
int main(){
    controller.Initialize();
    Board board = controller.GetBoardThreadManager().GetMainBoard();
    board.Load("r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3");
    std::vector<Move> moves = controller.GetMoveGenerator().GeneratePsuedoLegalMoves(board);
    std::cout << moves.size() << "\n\n";
}
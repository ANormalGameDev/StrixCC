#include <iostream>
#include "engine.hh"

EngineController controller;
MoveGenerator MoveGen;
int main(){
    MoveGen.InitMagicBitboards();
    Board board = controller.GetBoardThreadManager().GetMainBoard();
    board.Load("rnbqkbnr/pp3ppp/2p1p3/3pP3/2PP4/8/PP3PPP/RNBQKBNR b KQkq - 0 4");
    std::vector<Move> moves = MoveGen.GeneratePsuedoLegalMoves(board);
    std::cout << moves.size() << "\n";
    for (int i = 0; i < 64; i++){
        if (i % 8 == 0) std::cout << "\n";
        std::cout << (int)board.GetPieces()[i].type << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < 64; i++){
        if (i % 8 == 0) std::cout << "\n";
        std::cout << (int)board.GetPieces()[i].color << " ";
    }
    std::cout << "\n";
}
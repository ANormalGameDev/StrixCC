#ifndef BOARDS_AND_THREADS_HH
#define BOARDS_AND_THREADS_HH

#include <thread>
#include <vector>
#include <iostream>
#include <stdlib.h>

typedef unsigned long long uint64;

enum class _PieceType {
    NONE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum class Color {
    NONE, WHITE, BLACK
};

enum Square : int {
    A8, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A1, B1, C1, D1, E1, F1, G1, H1,
    _NULL
};

struct Piece {
    Color color;
    _PieceType type;
    Piece(Color _color, _PieceType _type){
        color = _color;
        type = _type;
    }
    Piece(){
        color = Color::NONE;
        type = _PieceType::NONE;
    }
};

class Board {
    private:
        Piece Pieces[64];
        Color ActiveColor = Color::WHITE;
        bool BlackCastle, WhiteCastle;
        Square EnPassantSquare;
        int HalfMoveClock;
        int FullMoveCount;
        uint64 Occupancy;
    public:
        Board(){}
        Piece* GetPieces() { return Pieces; }
        Color GetActiveColor() { return ActiveColor; }
        Square GetEnPassantSquare() { return EnPassantSquare; }
        int GetHalfMoveClock() { return HalfMoveClock; }
        int GetFullMoveCount() { return FullMoveCount; }
        uint64 GetOccupancy() { return Occupancy; }
        void Load(const char* FEN);
};

class BoardThreadManager {
    private:
        std::vector<Board> boards;
        int maxThreads;
        int maxDepth;

        const int maxThreadsSupported = std::thread::hardware_concurrency();
        const int maxDepthAllowed = 26;
    public:
        Board GetMainBoard(){ if (boards.size() < 1) boards.push_back(Board()); return boards[0]; } // For Testing
        void Go(Board board); // This Function will be called when the UCI Manager recieves the "go"
                              // command. This function will start all the threads and tell them all
                              // to start calculating.
        void SetMaxThreadsAmount(int amount){
            if (amount > 0 && amount < maxThreadsSupported){
                maxThreads = amount;
            }
        }
        void SetMaxDepth(int depth){
            if (depth > 0 && depth < maxDepthAllowed){
                maxDepth = depth;
            }
        }
};

#endif
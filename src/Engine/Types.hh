#ifndef __TYPES_HH__
#define __TYPES_HH__

#include <stdlib.h>
#include <string>
#include <vector>

namespace StrixCC {
    typedef unsigned long long uint64;

    enum Square : size_t {
        A8, B8, C8, D8, E8, F8, G8, H8,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A1, B1, C1, D1, E1, F1, G1, H1,
        NULLSQ
    };

    enum PieceType : size_t { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
    enum Color { NONE, WHITE, BLACK };
    struct CastlingRights {
        bool Kingside = false, Queenside = false;
        void Set(bool kingside, bool value){
            if (kingside)
                Kingside = value;
            else
                Queenside = value;
        }
    };
    struct Piece {
        PieceType type;
        Color color;
        Piece(){ type = PieceType::EMPTY; color = Color::NONE; }
        Piece(PieceType _type, Color _color){ type = _type; color = _color; }
        void Clear(){ type = PieceType::EMPTY; color = Color::NONE; }
        bool Occupied(){ return type != PieceType::EMPTY; }
    };

    enum MoveType { STANDARD, CAPTURE };
    struct Move {
        const Square From, To;
        const MoveType Type;
        Move(Square from, Square to, MoveType type) : From(from), To(to), Type(type){}
    };

    enum MoveGenerationMode { LEGAL, PSEUDO_LEGAL };

    struct SMagic {
        uint64* Table;
        uint64 Mask;
        uint64 Magic;
        size_t Shift;
        size_t Index(uint64 occupancy){ return ((occupancy & Mask) * Magic) >> Shift; }
    };

    struct Board {
        Piece Pieces[64];
        Color SideToMove = Color::NONE;
        Square EnPassantSquare = Square::NULLSQ;
        CastlingRights WRights, BRights;
        int HalfMoveClock = 0, FullMoveCount = 0;

        // Functions
        void Print();
        void Load(std::string FEN);

        bool Validate(Move move);
        std::string GetFEN();
        std::vector<Move> Generate(MoveGenerationMode GenMode);

        // Other Things
        uint64 Occupancy = 0ULL;
        std::vector<Move> MoveList;
    };
};

#endif
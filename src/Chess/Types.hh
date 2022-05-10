#ifndef TYPES_HH
#define TYPES_HH

// The Types.hh header file contains every type/(type name) that StrixCC needs.
// This header file should be included in every other header file except
// "Prestored Magics.hh".

#include <stdio.h>
#include <stdlib.h>

namespace StrixCC {
    typedef unsigned long long uint64;
    
    enum PieceType {
        EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
    };

    enum Color {
        NONE, WHITE, BLACK
    };

    enum Square : int {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
        UNDEFINED
    };

    struct SMagic {
        uint64* Table;
        uint64 Mask;
        uint64 Magic;
        int Shift;
        constexpr size_t GetIndex(uint64 occupancy){ return (((occupancy & Mask) * Magic) >> Shift); }
    };

    // Postfix increment and decrement operators for enum Square
    //     sq++ <--
    //     sq-- <--
    constexpr void operator++(Square& square, int i){
        square = square == Square::H8 ? Square::UNDEFINED : (Square)(square + 1);
    }
    constexpr void operator--(Square& square, int i){
        square = square == Square::A1 ? Square::UNDEFINED : (Square)(square - 1);
    }
};

#endif
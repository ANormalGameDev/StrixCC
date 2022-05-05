#include "Moves.hh"
#include "../engine.hh"

uint64 NotAFile = 18374403900871474942ULL;
uint64 NotHFile = 9187201950435737471ULL;
uint64 NotHGFile = 4557430888798830399ULL;
uint64 NotABFile = 18229723555195321596ULL;

enum _Color : int{
    WHITE, BLACK
};

enum class SliderPieceType {
    ROOK, BISHOP
};

enum class PieceType {
    KNIGHT, PAWN, KING
};

uint64 GenerateRookAttacks(int square, uint64 occupancy){
    int r, f, pf = square % 8, pr = square / 8;

    uint64 Attacks = 0ULL;
    for (r = pr + 1; r <= 7; r++){
        Attacks |= (1ULL << (r * 8 + pf));
        if (Utils::GetBit(occupancy, r * 8 + pf)) break;
    }
    for (r = pr - 1; r >= 0; r--){
        Attacks |= (1ULL << (r * 8 + pf));
        if (Utils::GetBit(occupancy, r * 8 + pf)) break;
    }
    for (f = pf + 1; f <= 7; f++){
        Attacks |= (1ULL << (pr * 8 + f));
        if (Utils::GetBit(occupancy, pr * 8 + f)) break;
    }
    for (f = pf - 1; f >= 0; f--){
        Attacks |= (1ULL << (pr * 8 + f));
        if (Utils::GetBit(occupancy, pr * 8 + f)) break;
    }
    return Attacks;
}

uint64 GenerateBishopAttacks(int square, uint64 occupancy){
    int r, f, pf = square % 8, pr = square / 8;

    uint64 Attacks = 0ULL;
    for (r = pr - 1, f = pf - 1; r >= 0 && f >= 0; r--, f--){
        Attacks |= (1ULL << (r * 8 + f));
        if (Utils::GetBit(occupancy, r * 8 + f)) break;
    }
    for (r = pr + 1, f = pf - 1; r <= 7 && f >= 0; r++, f--){
        Attacks |= (1ULL << (r * 8 + f));
        if (Utils::GetBit(occupancy, r * 8 + f)) break;
    }
    for (r = pr + 1, f = pf + 1; r <= 7 && f <= 7; r++, f++){
        Attacks |= (1ULL << (r * 8 + f));
        if (Utils::GetBit(occupancy, r * 8 + f)) break;
    }
    for (r = pr - 1, f = pf + 1; r >= 0 && f <= 7; r--, f++){
        Attacks |= (1ULL << (r * 8 + f));
        if (Utils::GetBit(occupancy, r * 8 + f)) break;
    }
    return Attacks;
}

uint64 GenerateKnightAttacks(Square square){
    uint64 Attacks = 0ULL, bb = 0ULL;
    Utils::SetBit(&bb, square);
        
    if ((bb >> 17) & NotHFile) Attacks |= (bb >> 17);
    if ((bb >> 15) & NotAFile) Attacks |= (bb >> 15);
    if ((bb >> 10) & NotHGFile) Attacks |= (bb >> 10);
    if ((bb >> 6) & NotABFile) Attacks |= (bb >> 6);
    if ((bb << 6) & NotHGFile) Attacks |= (bb << 6);
    if ((bb << 10) & NotABFile) Attacks |= (bb << 10);
    if ((bb << 15) & NotHFile) Attacks |= (bb << 15);
    if ((bb << 17) & NotAFile) Attacks |= (bb << 17);

    return Attacks;
}

uint64 GenerateKingAttacks(Square square){
    uint64 Attacks = 0ULL, bb = 0ULL;
    Utils::SetBit(&bb, square);
    
    if (bb >> 8) Attacks |= (bb >> 8);
    if (bb << 8) Attacks |= (bb << 8);
    if ((bb >> 9) & NotHFile) Attacks |= (bb >> 9);
    if ((bb >> 7) & NotAFile) Attacks |= (bb >> 7);
    if ((bb >> 1) & NotHFile) Attacks |= (bb >> 1);
    if ((bb << 1) & NotAFile) Attacks |= (bb << 1);
    if ((bb << 7) & NotHFile) Attacks |= (bb << 7);
    if ((bb << 9) & NotAFile) Attacks |= (bb << 9);

    return Attacks;
}

uint64 GeneratePawnAttacks(Square square, _Color color){
    uint64 Attacks = 0ULL, bb = 0ULL;
    Utils::SetBit(&bb, square);
    
    if (color == _Color::BLACK){
        if ((bb >> 9) & NotHFile) Attacks |= (bb >> 9);
        if ((bb >> 7) & NotAFile) Attacks |= (bb >> 7);
    }
    else {
        if ((bb << 7) & NotHFile) Attacks |= (bb << 7);
        if ((bb << 9) & NotAFile) Attacks |= (bb << 9);
    }

    return Attacks;
}

void InitMagics(SliderPieceType Type, Magic *Magics, uint64 *AttackTable){
    int size = 0;
    uint64 subset;
    for (int square = Square::A8; square <= Square::H1; square++){
        Magic& _Magic = Magics[square];
        int r, f, pf = square % 8, pr = square / 8;
        
        uint64 Attacks = 0ULL;
        if (Type == SliderPieceType::ROOK){
            for (r = pr + 1; r <= 6; r++) Attacks |= (1ULL << (r * 8 + pf));
            for (r = pr - 1; r >= 1; r--) Attacks |= (1ULL << (r * 8 + pf));
            for (f = pf + 1; f <= 6; f++) Attacks |= (1ULL << (pr * 8 + f));
            for (f = pf - 1; f >= 1; f--) Attacks |= (1ULL << (pr * 8 + f));
        }
        else {
            for (r = pr - 1, f = pf - 1; r >= 1 && f >= 1; r--, f--) Attacks |= (1ULL << (r * 8 + f));
            for (r = pr + 1, f = pf - 1; r <= 6 && f >= 1; r++, f--) Attacks |= (1ULL << (r * 8 + f));
            for (r = pr + 1, f = pf + 1; r <= 6 && f <= 6; r++, f++) Attacks |= (1ULL << (r * 8 + f));
            for (r = pr - 1, f = pf + 1; r >= 1 && f <= 6; r--, f++) Attacks |= (1ULL << (r * 8 + f));
        }
        _Magic.Mask = Attacks;
        _Magic.Shift = 64 - Utils::PopCount(_Magic.Mask);

        _Magic.AttackTable = square == Square::A8 ? AttackTable : Magics[square - 1].AttackTable + size;
        _Magic.Magic = Type == SliderPieceType::ROOK ? _RMagicsx64[square] : _BMagicsx64[square];

        size = subset = 0;
        do {
            uint64 index = _Magic.GetIndexFromOccupancy(subset);
            _Magic.AttackTable[index] = Type == SliderPieceType::ROOK ? GenerateRookAttacks(square, subset) : GenerateBishopAttacks(square, subset);
            size++;
            subset = (subset - _Magic.Mask) & _Magic.Mask;
        } while (subset);
    }
}

void InitAttackTable(PieceType Type, uint64* Table){
    if (Type == PieceType::PAWN){
        for (int square = Square::A7; square <= Square::H2; square++){
            Table[square] = GeneratePawnAttacks((Square)square, _Color::BLACK);
            Table[54 + square] = GeneratePawnAttacks((Square)(square), _Color::WHITE);
        }
        return;
    }
    for (int square = Square::A8; square <= Square::H1; square++){
        Table[square] = Type == PieceType::KNIGHT ? GenerateKnightAttacks((Square)square)
                                                  : GenerateKingAttacks((Square)square);
    }
}

void MoveGenerator::InitMagicBitboards(){
    InitMagics(SliderPieceType::ROOK, RMagics, RAttacks);
    InitMagics(SliderPieceType::BISHOP, BMagics, BAttacks);
    InitAttackTable(PieceType::KING, KAttacks);
    InitAttackTable(PieceType::KNIGHT, NAttacks);
    InitAttackTable(PieceType::PAWN, PAttacks);
}
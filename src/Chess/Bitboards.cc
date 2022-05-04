#include "Moves.hh"
#include "../engine.hh"

enum class PieceType : char {
    ROOK, BISHOP
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

void InitMagics(PieceType Type, Magic *Magics, uint64 *AttackTable){
    int size = 0;
    for (int square = (int)Square::A8; square <= (int)Square::H1; square++){
        Magic& _Magic = Magics[square];
        int r, f, pf = square % 8, pr = square / 8;
        
        uint64 Attacks = 0ULL;
        if (Type == PieceType::ROOK){
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

        _Magic.AttackTable = square == (int)Square::A8 ? AttackTable : Magics[square - 1].AttackTable + size;
        _Magic.Magic = controller.GetMagicFinder().GetMagic((Square)square, Type == PieceType::BISHOP);

        size = 0;
        for (uint64 bb = _Magic.Mask; bb; bb = (bb - 1) & _Magic.Mask){
            uint64 index = _Magic.GetIndexFromOccupancy(bb);
            _Magic.AttackTable[index] = Type == PieceType::ROOK ? GenerateRookAttacks(square, bb) : GenerateBishopAttacks(square, bb);
            size++;
        }
        _Magic.AttackTable[0] = Type == PieceType::ROOK ? GenerateRookAttacks(square, 0ULL) : GenerateBishopAttacks(square, 0ULL);
        size++;
    }
}

void MoveGenerator::InitMagicBitboards(){
    InitMagics(PieceType::ROOK, RMagics, RAttacks);
    InitMagics(PieceType::BISHOP, BMagics, BAttacks);
}
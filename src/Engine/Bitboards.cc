#include "Bitboards.hh"
#include "Utils.hh"
#include "Magics.hh"
#include <bit>

namespace StrixCC {
    namespace Bitboards{
        uint64 KingTable[64], KnightTable[64];

        uint64 RookTable[0x19000], BishopTable[0x1480];
        SMagic RookMagics[64], BishopMagics[64];

        uint64 GenerateMask(PieceType Type, Square square){
            uint64 attacks = 0ULL;
            int r, f, pr = RankOf(square), pf = FileOf(square);

            if (Type == PieceType::ROOK){
                for (r = pr + 1; r <= 6; r++){ SetBit(&attacks, (r * 8 + pf)); }
                for (r = pr - 1; r >= 1; r--){ SetBit(&attacks, (r * 8 + pf)); }
                for (f = pf + 1; f <= 6; f++){ SetBit(&attacks, (pr * 8 + f)); }
                for (f = pf - 1; f >= 1; f--){ SetBit(&attacks, (pr * 8 + f)); }
            }
            else if (Type == PieceType::BISHOP){
                for (r = pr + 1, f = pf + 1; r <= 6 && f <= 6; r++, f++) SetBit(&attacks, (r * 8 + f));
                for (r = pr - 1, f = pf + 1; r >= 1 && f <= 6; r--, f++) SetBit(&attacks, (r * 8 + f));
                for (r = pr + 1, f = pf - 1; r <= 6 && f >= 1; r++, f--) SetBit(&attacks, (r * 8 + f));
                for (r = pr - 1, f = pf - 1; r >= 1 && f >= 1; r--, f--) SetBit(&attacks, (r * 8 + f));
            }

            return attacks;
        }

        uint64 GenerateSliderAttacks(PieceType Type, Square square, uint64 occupancy){
            uint64 attacks = 0ULL;
            int r, f, pr = RankOf(square), pf = FileOf(square);

            if (Type == PieceType::ROOK){
                for (r = pr + 1; r <= 7; r++){ SetBit(&attacks, (r * 8 + pf)); if (GetBit(occupancy, (r * 8 + pf))) break; }
                for (r = pr - 1; r >= 0; r--){ SetBit(&attacks, (r * 8 + pf)); if (GetBit(occupancy, (r * 8 + pf))) break; }
                for (f = pf + 1; f <= 7; f++){ SetBit(&attacks, (pr * 8 + f)); if (GetBit(occupancy, (pr * 8 + f))) break; }
                for (f = pf - 1; f >= 0; f--){ SetBit(&attacks, (pr * 8 + f)); if (GetBit(occupancy, (pr * 8 + f))) break; }
            }
            else if (Type == PieceType::BISHOP){
                for (r = pr + 1, f = pf + 1; r <= 7 && f <= 7; r++, f++){ SetBit(&attacks, (r * 8 + f)); if (GetBit(occupancy, (r * 8 + f))) break; }
                for (r = pr - 1, f = pf + 1; r >= 0 && f <= 7; r--, f++){ SetBit(&attacks, (r * 8 + f)); if (GetBit(occupancy, (r * 8 + f))) break; }
                for (r = pr + 1, f = pf - 1; r <= 7 && f >= 0; r++, f--){ SetBit(&attacks, (r * 8 + f)); if (GetBit(occupancy, (r * 8 + f))) break; }
                for (r = pr - 1, f = pf - 1; r >= 0 && f >= 0; r--, f--){ SetBit(&attacks, (r * 8 + f)); if (GetBit(occupancy, (r * 8 + f))) break; }
            }

            return attacks;
        }

        uint64 GenerateAttacks(PieceType Type, Square square){
            uint64 attacks = 0ULL, bb = 0ULL;

            SetBit(&bb, square);
            if (Type == PieceType::KING){
                if (bb >> 8) attacks |= (bb >> 8);
                if (bb << 8) attacks |= (bb << 8);
                if ((bb >> 9) & NotHFile) attacks |= (bb >> 9);
                if ((bb >> 7) & NotAFile) attacks |= (bb >> 7);
                if ((bb >> 1) & NotHFile) attacks |= (bb >> 1);
                if ((bb << 1) & NotAFile) attacks |= (bb << 1);
                if ((bb << 7) & NotHFile) attacks |= (bb << 7);
                if ((bb << 9) & NotAFile) attacks |= (bb << 9);
            }
            else if (Type == PieceType::KNIGHT){
                if ((bb >> 17) & NotHFile) attacks |= (bb >> 17);
                if ((bb >> 15) & NotAFile) attacks |= (bb >> 15);
                if ((bb >> 10) & NotHGFile) attacks |= (bb >> 10);
                if ((bb >> 6) & NotABFile) attacks |= (bb >> 6);
                if ((bb << 6) & NotHGFile) attacks |= (bb << 6);
                if ((bb << 10) & NotABFile) attacks |= (bb << 10);
                if ((bb << 15) & NotHFile) attacks |= (bb << 15);
                if ((bb << 17) & NotAFile) attacks |= (bb << 17);
            }

            return attacks;
        }


        void InitMagics(PieceType Type, SMagic* Magics, uint64* Table){
            if (Type != PieceType::ROOK && Type != PieceType::BISHOP)
                ThrowError("Init", "Invalid Type in InitMagics(PieceType, SMagic*, uint64*).");
            size_t size = 0UL;
            uint64 subset = 0ULL;
            for (size_t square = Square::A8; square <= Square::H1; square++){
                SMagic& Magic = Magics[square];

                Magic.Magic = Type == PieceType::ROOK ? _RMagicsx64[square] : _BMagicsx64[square];

                Magic.Mask = GenerateMask(Type, (Square)square);
                Magic.Shift = 64 - std::__popcount<uint64>(Magic.Mask);

                Magic.Table = square == Square::A8 ? Table : Magics[square - 1].Table + size;

                subset = size = 0;
                do {
                    size_t idx = Magic.Index(subset);
                    Magic.Table[idx] = GenerateSliderAttacks(Type, (Square)square, subset); 

                    subset = (subset - Magic.Mask) & Magic.Mask;
                    size++;
                } while (subset);
            }
        }

        void InitTables(PieceType Type, uint64* Table){
            if (Type != PieceType::KING && Type != PieceType::KNIGHT)
                ThrowError("Init", "Invalid Type in InitTables(PieceType, uint64*).");
            for (size_t square = Square::A8; square <= Square::H1; square++){
                Table[square] = GenerateAttacks(Type, (Square)square);
            }
        }

        void Init(){
            InitMagics(PieceType::ROOK, RookMagics, RookTable);
            InitMagics(PieceType::BISHOP, BishopMagics, BishopTable);
            InitTables(PieceType::KING, KingTable);
            InitTables(PieceType::KNIGHT, KnightTable);
        }
    };

    uint64 RookAttacks(Square square, uint64 occupancy){
        SMagic& Magic = Bitboards::RookMagics[square];
        return Magic.Table[Magic.Index(occupancy)];
    }
    uint64 BishopAttacks(Square square, uint64 occupancy){
        SMagic& Magic = Bitboards::BishopMagics[square];
        return Magic.Table[Magic.Index(occupancy)];
    }
    uint64 QueenAttacks(Square square, uint64 occupancy){
        return (RookAttacks(square, occupancy) | BishopAttacks(square, occupancy));
    }

    uint64 KingAttacks(Square square){
        return Bitboards::KingTable[square];
    }
    uint64 KnightAttacks(Square square){
        return Bitboards::KnightTable[square];
    }

    uint64 PawnAttacks(Square square, Color color){
        uint64 attacks = 0ULL, bb = 0ULL;
        SetBit(&bb, square);
        if (color == Color::WHITE){
            if ((bb >> 9) & Bitboards::NotHFile) attacks |= (bb >> 9);
            if ((bb >> 7) & Bitboards::NotAFile) attacks |= (bb >> 7);
        }
        else if (color == Color::BLACK){
            if ((bb << 9) & Bitboards::NotHFile) attacks |= (bb << 9);
            if ((bb << 7) & Bitboards::NotAFile) attacks |= (bb << 7);
        }
        return attacks;
    }
};
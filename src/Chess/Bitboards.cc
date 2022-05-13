#include "Bitboards.hh"
#include "PrestoredMagics.hh"

namespace StrixCC {
    namespace Bitboards {
        // Other Pieces
        uint64 NAttacks[64], KAttacks[64];

        // The Main Slider Pieces
        SMagic RMagics[64], BMagics[64];
        uint64 RAttacks[0x19000], BAttacks[0x1480];

        // Mask Generation Functions for Slider Pieces
        template<PieceType Type>
        uint64 GenerateSliderMasks(Square square){
            int r, f, pr = square / 8, pf = square % 8;

            uint64 attacks = 0ULL;
            if (Type == PieceType::ROOK){
                for (r = pr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + pf));
                for (r = pr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + pf));
                for (f = pf + 1; f <= 6; f++) attacks |= (1ULL << (pr * 8 + f));
                for (f = pf - 1; f >= 1; f--) attacks |= (1ULL << (pr * 8 + f));
            }
            else if (Type == PieceType::BISHOP){
                for (r = pr - 1, f = pf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));
                for (r = pr + 1, f = pf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
                for (r = pr + 1, f = pf + 1; r <= 6 && f <= 6; r++, f++) attacks |= (1ULL << (r * 8 + f));
                for (r = pr - 1, f = pf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
            }

            return attacks;
        }

        // Attacks Generation Functions for Slider Pieces
        template<PieceType Type>
        uint64 GenerateSliderAttacks(Square square, uint64 occupancy){
            int r, f, pr = square / 8, pf = square % 8;

            uint64 attacks = 0ULL;
            if (Type == PieceType::ROOK){
                for (r = pr + 1; r <= 7; r++){
                    attacks |= (1ULL << (r * 8 + pf));
                    if (GetBit(occupancy, r * 8 + pf)) break;
                }
                for (r = pr - 1; r >= 0; r--){
                    attacks |= (1ULL << (r * 8 + pf));
                    if (GetBit(occupancy, r * 8 + pf)) break;
                }
                for (f = pf + 1; f <= 7; f++){
                    attacks |= (1ULL << (pr * 8 + f));
                    if (GetBit(occupancy, pr * 8 + f)) break;
                }
                for (f = pf - 1; f >= 0; f--){
                    attacks |= (1ULL << (pr * 8 + f));
                    if (GetBit(occupancy, pr * 8 + f)) break;
                }
            }
            else if (Type == PieceType::BISHOP){
                for (r = pr - 1, f = pf - 1; r >= 0 && f >= 0; r--, f--){
                    attacks |= (1ULL << (r * 8 + f));
                    if (GetBit(occupancy, r * 8 + f)) break;
                }
                for (r = pr + 1, f = pf - 1; r <= 7 && f >= 0; r++, f--){
                    attacks |= (1ULL << (r * 8 + f));
                    if (GetBit(occupancy, r * 8 + f)) break;
                }
                for (r = pr + 1, f = pf + 1; r <= 7 && f <= 7; r++, f++){
                    attacks |= (1ULL << (r * 8 + f));
                    if (GetBit(occupancy, r * 8 + f)) break;
                }
                for (r = pr - 1, f = pf + 1; r >= 0 && f <= 7; r--, f++){
                    attacks |= (1ULL << (r * 8 + f));
                    if (GetBit(occupancy, r * 8 + f)) break;
                }
            }

            return attacks;
        }

        // Attacks Generation Functions for Other Pieces
        uint64 GenerateKnightAttacks(Square square){
            uint64 bb = 0ULL, attacks = 0ULL;
            SetBit(&bb, square);
            if ((bb >> 17) & NotHFile) attacks |= (bb >> 17);
            if ((bb >> 15) & NotAFile) attacks |= (bb >> 15);
            if ((bb >> 10) & NotHGFile) attacks |= (bb >> 10);
            if ((bb >> 6) & NotABFile) attacks |= (bb >> 6);
            if ((bb << 6) & NotHGFile) attacks |= (bb << 6);
            if ((bb << 10) & NotABFile) attacks |= (bb << 10);
            if ((bb << 15) & NotHFile) attacks |= (bb << 15);
            if ((bb << 17) & NotAFile) attacks |= (bb << 17);
            return attacks;
        }

        uint64 GenerateKingAttacks(Square square){
            uint64 bb = 0ULL, attacks = 0ULL;
            SetBit(&bb, square);
            if (bb >> 8) attacks |= (bb >> 8);
            if (bb << 8) attacks |= (bb << 8);
            if ((bb >> 9) & NotHFile) attacks |= (bb >> 9);
            if ((bb >> 7) & NotAFile) attacks |= (bb >> 7);
            if ((bb >> 1) & NotHFile) attacks |= (bb >> 1);
            if ((bb << 1) & NotAFile) attacks |= (bb << 1);
            if ((bb << 7) & NotHFile) attacks |= (bb << 7);
            if ((bb << 9) & NotAFile) attacks |= (bb << 9);
            return attacks;
        }

        // Initialization Functions
        template<PieceType Type>
        void InitMagics(SMagic* Magics, uint64* AttackTable){
            size_t count;
            uint64 subset;
            for (Square square = Square::A1; square <= Square::H8; square++){
                SMagic& Magic = Magics[square];

                Magic.Mask = GenerateSliderMasks<Type>(square);
                Magic.Shift = 64 - std::__popcount<u_int64_t>(Magic.Mask);
                
                Magic.Magic = Type == PieceType::ROOK ? _RMagics[square] : _BMagics[square];
                Magic.Table = square == Square::A1 ? AttackTable : Magics[square - 1].Table + count;

                subset = count = 0;
                do {
                    Magic.Table[Magic.GetIndex(subset)] = GenerateSliderAttacks<Type>(square, subset);

                    subset = (subset - Magic.Mask) & Magic.Mask;
                    count++;
                } while (subset);
            }
        }

        template<PieceType Type>
        void InitAttackTable(uint64* AttackTable){
            if (Type != PieceType::KNIGHT && Type != PieceType::KING) return;
            for (Square square = Square::A1; square <= Square::H8; square++){
                AttackTable[square] = Type == PieceType::KNIGHT ? GenerateKnightAttacks(square)
                                                                : GenerateKingAttacks(square);
            }
        }

        void Init(){
            InitMagics<PieceType::ROOK>(RMagics, RAttacks);
            InitMagics<PieceType::BISHOP>(BMagics, BAttacks);
            InitAttackTable<PieceType::KNIGHT>(NAttacks);
            InitAttackTable<PieceType::KING>(KAttacks);
        }
    };
};
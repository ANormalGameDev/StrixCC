#include "Bitboards.hh"
#include "PrestoredMagics.hh"

namespace StrixCC {
    namespace Bitboards {
        // The Main Slider Pieces
        SMagic RMagics[64], BMagics[64];
        uint64 RAttacks[0x19000], BAttacks[0x1480];

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

        template<PieceType Type>
        void InitMagics(SMagic* Magics, uint64* AttackTable){
            size_t count;
            uint64 subset;
            for (Square square = Square::A1; square <= Square::H8; square++){
                SMagic& Magic = Magics[square];

                Magic.Mask = GenerateSliderAttacks<Type>(square, 0ULL) & ~(edges);
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

        void Init(){
            InitMagics<PieceType::ROOK>(RMagics, RAttacks);
            InitMagics<PieceType::BISHOP>(BMagics, BAttacks);
        }
    };
};
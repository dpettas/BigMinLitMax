#include "Zkey.hpp"

namespace
{
    Zkey_t SplitBitsFor2(uint64_t value) 
    {
        value = (value                ) & 0x00000000ffffffff;
        value = (value ^ (value << 16)) & 0x0000ffff0000ffff;
        value = (value ^ (value <<  8)) & 0x00ff00ff00ff00ff;
        value = (value ^ (value <<  4)) & 0x0f0f0f0f0f0f0f0f;
        value = (value ^ (value <<  2)) & 0x3333333333333333;
        value = (value ^ (value <<  1)) & 0x5555555555555555;
        return value;
    }

    Zkey_t CombineBitsFor2(uint64_t value) 
    {
        value &= 0x5555555555555555;
        value = (value ^ (value >>  1)) & 0x3333333333333333;
        value = (value ^ (value >>  2)) & 0x0f0f0f0f0f0f0f0f;
        value = (value ^ (value >>  4)) & 0x00ff00ff00ff00ff;
        value = (value ^ (value >>  8)) & 0x0000ffff0000ffff;
        value = (value ^ (value >> 16)) & 0x00000000ffffffff;
        return value;
    }
}


namespace zkey
{
    Zkey_t encode( uint32_t x, uint32_t y)
    {
        return (SplitBitsFor2(x) ) | ( SplitBitsFor2(y) << 1 );
    }
    // -------------------------------------------------------------
    // -------------------------------------------------------------

    void   decode( Zkey_t zkey, uint32_t& x, uint32_t& y)
    {
        x = CombineBitsFor2(zkey);
        y = CombineBitsFor2(zkey >> 1);
        return;
    }
    // -------------------------------------------------------------
    // -------------------------------------------------------------
}
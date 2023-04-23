#include "Zkey.hpp"

namespace
{
    // Zkey for 2 values
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
        value =  value                  & 0x5555555555555555;
        value = (value ^ (value >>  1)) & 0x3333333333333333;
        value = (value ^ (value >>  2)) & 0x0f0f0f0f0f0f0f0f;
        value = (value ^ (value >>  4)) & 0x00ff00ff00ff00ff;
        value = (value ^ (value >>  8)) & 0x0000ffff0000ffff;
        value = (value ^ (value >> 16)) & 0x00000000ffffffff;
        return value;
    }

    // Zkey for 3 values
    Zkey_t SplitBitsFor3(uint64_t value) 
    {
        value =  value                 & 0x00000000001fffff; // we only look at the first 21 bits
        value = (value ^ (value << 32))& 0x001f00000000ffff; // 0000000000011111000000000000000000000000000000001111111111111111
        value = (value ^ (value << 16))& 0x001f0000ff0000ff; // 0000000000011111000000000000000011111111000000000000000011111111
        value = (value ^ (value <<  8))& 0x100f00f00f00f00f; // 0001000000001111000000001111000000001111000000001111000000000000
        value = (value ^ (value <<  4))& 0x10c30c30c30c30c3; // 0001000011000011000011000011000011000011000011000011000100000000
        value = (value ^ (value <<  2))& 0x1249249249249249;
        return value;
    }

    Zkey_t CombineBitsFor3(uint64_t value) 
    {
        value =  value                  & 0x1249249249249249;
        value = ( value ^ (value >>  2))& 0x10c30c30c30c30c3;
        value = ( value ^ (value >>  4))& 0x100f00f00f00f00f;
        value = ( value ^ (value >>  8))& 0x001f0000ff0000ff;
        value = ( value ^ (value >> 16))& 0x001f00000000ffff;
        value = ( value ^ (value >> 32))& 0x00000000001fffff;
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

    Zkey_t encode( uint32_t x, uint32_t y, uint32_t z)
    {
        return (SplitBitsFor3(x) ) | ( SplitBitsFor3(y) << 1 ) | ( SplitBitsFor3(z) << 2 );
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

    void   decode( Zkey_t zkey, uint32_t& x, uint32_t& y, uint32_t& z)
    {
        x = CombineBitsFor3(zkey);
        y = CombineBitsFor3(zkey >> 1);
        z = CombineBitsFor3(zkey >> 2);
        return;
    }
}
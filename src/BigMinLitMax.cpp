#include "BigMinLitMax.hpp"
#include "Zkey.hpp"
#include <stdexcept>
#include <iostream>
#include <bitset>

namespace
{
    int bitset_msb_position( Zkey_t key)
    {
        if(!key) return -1;

        int msb = 0;
        while (key) 
        {
            msb++;
            key = key >> 1;
        }
        return msb - 1;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    void bitset_turn_on_bits( Zkey_t& key, uint32_t start, uint32_t stop, uint32_t step)
    {
        for(uint32_t pos = start; pos <= stop; pos += step)
        {
            Zkey_t on_bit = 0x1ul << (pos);
            key |= on_bit;
        }

        return;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    void bitset_turn_off_bits( Zkey_t& key, uint32_t start, uint32_t stop, uint32_t step)
    {
        for(uint32_t pos = start; pos <= stop; pos += step)
        {
            Zkey_t on_bit = 0x1ul << (pos);
            key &= ~on_bit;
        }

        return;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    void bitset_turn_on_bit( Zkey_t& key, uint32_t i)
    {
        key = key | (0x1ul << i);
        return;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    void bitset_turn_off_bit( Zkey_t& key, uint32_t i)
    {
        key = key & (~(0x1ul << i));
        return;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Zkey_t bitset_set_ones(uint32_t start)
    {
        return (1ul<< (start+1)) - 1ul;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Zkey_t load_xxx10000( Zkey_t value, Zkey_t bit_pos)
    {
        int pos = bitset_msb_position(bit_pos);
        bitset_turn_off_bits(value, pos%2, pos, 2 );
        bitset_turn_on_bit  (value, pos);
        return value;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Zkey_t load_xxx01111( Zkey_t value, Zkey_t bit_pos)
    {
        int pos = bitset_msb_position(bit_pos);
        bitset_turn_on_bits( value, pos%2, pos, 2);
        bitset_turn_off_bit( value, pos);
        return value;
    }
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



BigMinLitMax::BigMinLitMax(Range_t xrange, Range_t yrange)
{
    xmin = xrange.left;
    xmax = xrange.right;

    ymin = yrange.left;
    ymax = yrange.right;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::zkey_min() const
{
    return zkey::encode(ymin, xmin);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::zkey_max() const
{
    return zkey::encode(ymax, xmax);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool BigMinLitMax::is_in_the_range(Zkey_t zval) const
{
    uint32_t x;
    uint32_t y;

    zkey::decode(zval, y, x);
    return ((xmin <= x) && ( x <= xmax)) &&
           ((ymin <= y) && ( y <= ymax));
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::bigmin( Zkey_t zval) const
{
    Zkey_t bigmin    = 0ul;
    
    Zkey_t zmin      = zkey_min();
    Zkey_t zmax      = zkey_max();

    Zkey_t bpos      = 0b1000000000000000000000000000000000000000000000000000000000000000;
    
    while(bpos)
    {
        Zkey_t bzval = zval & bpos;
        Zkey_t bzmin = zmin & bpos;
        Zkey_t bzmax = zmax & bpos;

        if( !bzval && !bzmin && !bzmax)
        {}
        else if( !bzval && !bzmin && bzmax)
        {
            bigmin = load_xxx10000(zmin, bpos);
            zmax   = load_xxx01111(zmax, bpos);
            
        }
        else if( !bzval && bzmin && bzmax)
        {
            bigmin = zmin;
            break;
        }
        else if( bzval && !bzmin && !bzmax)
        {
            break;
        }
        else if( bzval && !bzmin && bzmax)
        {
            zmin = load_xxx10000(zmin, bpos);
        }
        else if( bzval && bzmin && bzmax)
        {

        }

        bpos >>= 1;
    }

    return bigmin;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


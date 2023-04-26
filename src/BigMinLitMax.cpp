#include "BigMinLitMax.hpp"
#include "Zkey.hpp"
#include <stdexcept>
#include <iostream>
#include <bitset>
#include "biset_manip.hpp"

namespace
{

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
    
    // ---------------------------------------------------------------------------------------
    // Calculate the min and max range
    // ---------------------------------------------------------------------------------------
    Zkey_t zmin      = zkey_min();
    Zkey_t zmax      = zkey_max();

    // ---------------------------------------------------------------------------------------
    // Calculate the MSB position of the key
    // ---------------------------------------------------------------------------------------
    int msb = bitset_msb_position(zval);

    // ---------------------------------------------------------------------------------------
    // Traditionally, you need to start from the last one bit (a.k.a 63 in this case)
    // However for optimization purposes we start from the most significant bit of the 
    // key zval
    // Zkey_t bpos      = 0b0100000000000000000000000000000000000000000000000000000000000000;
    // ---------------------------------------------------------------------------------------

    Zkey_t bpos = 0x1ul << (msb+1);
    
    while(bpos)
    {
        Zkey_t bzval = zval & bpos;
        Zkey_t bzmin = zmin & bpos;
        Zkey_t bzmax = zmax & bpos;

        if     ( !bzval && !bzmin && !bzmax)
        {}
        else if( !bzval && !bzmin &&  bzmax)
        {
            bigmin = load_xxx10000(zmin, bpos);
            zmax   = load_xxx01111(zmax, bpos);    
        }
        else if( !bzval &&  bzmin &&  bzmax)
        {
            bigmin = zmin;
            break;
        }
        else if(  bzval && !bzmin && !bzmax)
        {
            break;
        }
        else if(  bzval && !bzmin &&  bzmax)
        {
            zmin = load_xxx10000(zmin, bpos);
        }
        else if(  bzval &&  bzmin &&  bzmax)
        {}

        bpos >>= 1;
    }

    return bigmin;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::litmax( Zkey_t zval) const
{
    Zkey_t litmax    = 0ul;
    
    // ---------------------------------------------------------------------------------------
    // Calculate the min and max range
    // ---------------------------------------------------------------------------------------
    Zkey_t zmin      = zkey_min();
    Zkey_t zmax      = zkey_max();

    // ---------------------------------------------------------------------------------------
    // Calculate the MSB position of the key
    // ---------------------------------------------------------------------------------------
    int msb = bitset_msb_position(zval);

    // ---------------------------------------------------------------------------------------
    // Traditionally, you need to start from the last one bit (a.k.a 63 in this case)
    // However for optimization purposes we start from the most significant bit of the 
    // key zval
    // Zkey_t bpos      = 0b0100000000000000000000000000000000000000000000000000000000000000;
    // ---------------------------------------------------------------------------------------

    Zkey_t bpos = 0x1ul << (msb+1);
    
    while(bpos)
    {
        Zkey_t bzval = zval & bpos;
        Zkey_t bzmin = zmin & bpos;
        Zkey_t bzmax = zmax & bpos;

        if     ( !bzval && !bzmin && !bzmax)
        {}
        else if( !bzval && !bzmin &&  bzmax)
        {
            zmax   = load_xxx01111(zmax, bpos);    
        }
        else if( !bzval &&  bzmin &&  bzmax)
        {
            break;
        }
        else if(  bzval && !bzmin && !bzmax)
        {
            litmax = zmax;
            break;
        }
        else if(  bzval && !bzmin &&  bzmax)
        {
            litmax = load_xxx01111(zmax, bpos);
            zmin   = load_xxx10000(zmin, bpos);
        }
        else if(  bzval &&  bzmin &&  bzmax)
        {}

        bpos >>= 1;
    }

    return litmax;

}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void   BigMinLitMax::bigmin_litmax( Zkey_t zval, Zkey_t& bigmin, Zkey_t& litmax)
{
    litmax    = 0ul;
    bigmin    = 0ul;
    
    // ---------------------------------------------------------------------------------------
    // Calculate the min and max range
    // ---------------------------------------------------------------------------------------
    Zkey_t zmin      = zkey_min();
    Zkey_t zmax      = zkey_max();

    // ---------------------------------------------------------------------------------------
    // Calculate the MSB position of the key
    // ---------------------------------------------------------------------------------------
    int msb = bitset_msb_position(zval);

    // ---------------------------------------------------------------------------------------
    // Traditionally, you need to start from the last one bit (a.k.a 63 in this case)
    // However for optimization purposes we start from the most significant bit of the 
    // key zval
    // Zkey_t bpos      = 0b0100000000000000000000000000000000000000000000000000000000000000;
    // ---------------------------------------------------------------------------------------

    Zkey_t bpos = 0x1ul << (msb+1);
    
    while(bpos)
    {
        Zkey_t bzval = zval & bpos;
        Zkey_t bzmin = zmin & bpos;
        Zkey_t bzmax = zmax & bpos;

        if     ( !bzval && !bzmin && !bzmax)
        {}
        else if( !bzval && !bzmin &&  bzmax)
        {
            bigmin = load_xxx10000(zmin, bpos);
            zmax   = load_xxx01111(zmax, bpos);    
        }
        else if( !bzval &&  bzmin &&  bzmax)
        {
            bigmin = zmin;
            break;
        }
        else if(  bzval && !bzmin && !bzmax)
        {
            litmax = zmax;
            break;
        }
        else if(  bzval && !bzmin &&  bzmax)
        {
            litmax = load_xxx01111(zmax, bpos);
            zmin   = load_xxx10000(zmin, bpos);
        }
        else if(  bzval &&  bzmin &&  bzmax)
        {}

        bpos >>= 1;
    }

    return;
}
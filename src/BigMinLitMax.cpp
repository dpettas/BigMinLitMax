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
        bitset_turn_off_bits(value, pos%3, pos, 3 );
        bitset_turn_on_bit  (value, pos);

        return value;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Zkey_t load_xxx01111( Zkey_t value, Zkey_t bit_pos)
    {
        int pos = bitset_msb_position(bit_pos);
        bitset_turn_on_bits( value, pos%3, pos, 3);
        bitset_turn_off_bit( value, pos);

        return value;
    }
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

BigMinLitMax::BigMinLitMax(Range_t xrange, Range_t yrange, Range_t zrange)
{
    xmin = xrange.left;
    xmax = xrange.right;

    ymin = yrange.left;
    ymax = yrange.right;

    zmin = zrange.left;
    zmax = zrange.right;


    z_min = zkey::encode(zmin, ymin, xmin);
    z_max = zkey::encode(zmax, ymax, xmax);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::zkey_min() const
{
    return z_min;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::zkey_max() const
{
    return z_max;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool BigMinLitMax::is_in_the_range(Zkey_t zval) const
{
    uint32_t x;
    uint32_t y;
    uint32_t z;

    zkey::decode(zval, z, y, x);
    return ((xmin <= x) && ( x <= xmax)) &&
           ((ymin <= y) && ( y <= ymax)) &&
           ((zmin <= z) && ( z <= zmax));
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

void   BigMinLitMax::bigmin_litmax( Zkey_t zval, Zkey_t& bigmin, Zkey_t& litmax) const
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
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::next_of (Zkey_t zval) const
{
    if(zval < z_min || zval >= z_max){
        return end();
    }
    
    int num_attemts = 3;
    int attempts    = 0;

    while(true)
    {
        zval++;
        attempts++;
        if( is_in_the_range(zval)  ) return zval;
        if( attempts == num_attemts) break;
    }

    // compute bigmin
    return bigmin(zval);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::prev_of (Zkey_t zval) const
{
    if(zval <= z_min || zval > z_max){
        return end();
    }

    int num_attemts = 3;
    int attempts    = 0;

    while(true)
    {
        zval--;
        attempts++;
        if( is_in_the_range(zval)  ) return zval;
        if( attempts == num_attemts) break;
    }

    return litmax(zval);
}
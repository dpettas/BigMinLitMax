#include "BigMinLitMax.hpp"
#include "Zkey.hpp"
#include <stdexcept>
#include <iostream>

namespace
{
    // 0b0100100100100100100100100100100100100100100100100100100100100100
    // 0b0010010010010010010010010010010010010010010010010010010010010010
    // 0b0001001001001001001001001001001001001001001001001001001001001001
    // 0b0xyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyzxyz
    Zkey_t load_xxx10000( Zkey_t value, Zkey_t bit_pos)
    {
        Zkey_t pattern_00010000 = bit_pos;
        Zkey_t pattern_00001111 = pattern_00010000 - 1ul;
        Zkey_t pattern_11110000 = ~pattern_00001111;

        return (value | pattern_00010000) & pattern_11110000;
    }
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Zkey_t load_xxx01111( Zkey_t value, Zkey_t bit_pos)
    {
        Zkey_t pattern_00010000 = bit_pos;
        Zkey_t pattern_11101111 = ~pattern_00010000;
        Zkey_t pattern_00001111 =  pattern_00010000 -1ul;

        return (value & pattern_11101111) | pattern_00001111;
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
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::zkey_min() const
{
    return zkey::encode(xmin, ymin, zmin);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::zkey_max() const
{
    return zkey::encode(xmax, ymax, zmax);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool BigMinLitMax::is_in_the_range(Zkey_t zval) const
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
    
    zkey::decode(zval, x,y,z);

    return ((xmin <= x) && ( x <= xmax)) &&
           ((ymin <= y) && ( y <= ymax)) &&
           ((zmin <= z) && ( z <= zmax));
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Zkey_t BigMinLitMax::bigmin( Zkey_t zval) const
{
    Zkey_t bigmin = 0ul;
    Zkey_t mask   = (1ul << 62);
    
    Zkey_t zmin   = zkey_min();
    Zkey_t zmax   = zkey_max();

    int i  = 0;
    while(mask)
    {
        //-----------------------------------------------
        Zkey_t bzmin = zmin & mask;
        Zkey_t bzmax = zmax & mask;
        Zkey_t bzval = zval & mask;
        //-----------------------------------------------

        bool case1 = !bzval && !bzmin && !bzmax;
        bool case2 = !bzval && !bzmin &&  bzmax;
        bool case3 = !bzval &&  bzmin && !bzmax;
        bool case4 = !bzval &&  bzmin &&  bzmax;
        bool case5 =  bzval && !bzmin && !bzmax;
        bool case6 =  bzval && !bzmin &&  bzmax;
        bool case7 =  bzval &&  bzmin && !bzmax;
        bool case8 =  bzval &&  bzmin &&  bzmax;

        if      ( case1 ) {}
        else if ( case2 ) 
        {
            std::cout << "Case 2 :: " << i << std::endl;

            bigmin = load_xxx10000( zmin, mask);
            zmax   = load_xxx01111( zmax, mask);
        }
        else if ( case3 ) { throw std::logic_error("Not Possible"); }
        else if ( case4 ) 
        {
            std::cout << "Case 4 :: " << i << std::endl;
            bigmin = zmin;
            break;
        }
        else if ( case5 ) 
        {
            std::cout << "Case 5 :: " << i << std::endl;
            break;
        }
        else if ( case6 ) 
        {
            std::cout << "Case 6 :: " << i << std::endl;
            zmin = load_xxx10000(zmin, mask);
            std::cout << "                  " << zmin << std::endl;
        }
        else if ( case7 ) { throw std::logic_error("Not Possible");}
        else if ( case8 ) {}

        ++i;
        mask >>= 1;
    }



    return bigmin;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


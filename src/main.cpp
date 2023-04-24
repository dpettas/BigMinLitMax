#include <iostream>
#include <bitset>
#include "Zkey.hpp"
#include "BigMinLitMax.hpp"


int main(int argc, char** argv) 
{


    auto search = BigMinLitMax({2, 5}, 
                               {2, 5},
                               {2, 5});

    uint32_t x = 342342;
    uint32_t y = 420;
    uint32_t z = 31;

    Zkey_t key = zkey::encode(x,y,z);

    Zkey_t zval = 120;

    std::cout << std::boolalpha;
    std::cout << "Zmin :: " << search.zkey_min() << std::endl;
    std::cout << "Zmax :: " << search.zkey_max() << std::endl;
    std::cout << "Guess:: " << zval << " "  << search.is_in_the_range(zval) << std::endl;




    std::cout << std::boolalpha;
    Zkey_t bigmin = search.bigmin(zval);
    std::cout << "BigMin :: " << bigmin << " " << search.is_in_the_range(bigmin) << std::endl;



    return 0;
}

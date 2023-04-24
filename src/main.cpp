#include <iostream>
#include <bitset>
#include "Zkey.hpp"
#include "BigMinLitMax.hpp"


int main(int argc, char** argv) 
{


    auto search = BigMinLitMax({3, 5}, 
                               {5,10});

    uint32_t x = 342342;
    uint32_t y = 420;
    uint32_t z = 31;

    Zkey_t key = zkey::encode(x,y,z);

    Zkey_t zval = 58;

    std::cout << std::boolalpha;

    std::cout << std::boolalpha;
    Zkey_t bigmin = search.bigmin(zval);
    std::cout << "BigMin :: " << bigmin << " " << search.is_in_the_range(bigmin) << std::endl;



    return 0;
}

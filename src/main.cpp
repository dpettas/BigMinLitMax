#include <iostream>
#include <bitset>
#include <Timer.hpp>
#include "Zkey.hpp"
#include "BigMinLitMax.hpp"


int main(int argc, char** argv) 
{

    auto search = BigMinLitMax({3, 5}, 
                               {5, 10},
                               {2, 5});



    Zkey_t zval = search.zkey_min();
    std::cout << std::boolalpha;
    std::cout << zval                 << " " << search.is_in_the_range(zval) << std::endl;


    while( zval != BigMinLitMax::end() )
    {
        zval = search.next_of(zval);
        std::cout << zval                 << " " << search.is_in_the_range(zval) << std::endl;

    }





    return 0;
}

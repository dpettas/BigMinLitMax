#include <iostream>
#include "Zkey.hpp"
#include "BigMinLitMax.hpp"

int main(int argc, char** argv) 
{
    auto search = BigMinLitMax({2,5}, 
                               {2,5}, 
                               {2,5});

    Zkey_t zval = (search.zkey_min() + search.zkey_max())/2;

    std::cout << zval << std::endl;
    std::cout << search.bigmin(zval) << std::endl;

    return 0;
}

#include <iostream>
#include "Zkey.hpp"
#include "BigMinLitMax.hpp"

int main(int argc, char** argv) 
{
    auto search = BigMinLitMax({2,5}, {2,5}, {2,5});

    std::cout << "-----\n";
    std::cout << search.zkey_min() << std::endl;
    std::cout << search.zkey_max() << std::endl;
    std::cout << "-----\n";
    





    return 0;
}

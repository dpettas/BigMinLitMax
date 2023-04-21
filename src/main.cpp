#include <iostream>
#include "Zkey.hpp"

int main(int argc, char** argv) 
{
    uint32_t x = 10;
    uint32_t y = 1025;

    Zkey_t zkey = zkey::encode(x,y);

    x = 100; 
    y = 43242;

    zkey::decode(zkey, x, y);

    std::cout << x << std::endl;
    std::cout << y << std::endl;



    return 0;
}

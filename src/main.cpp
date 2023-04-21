#include <iostream>
#include "Zkey.hpp"

int main(int argc, char** argv) 
{
    uint32_t x = 10;
    uint32_t y = 1025;

    Zkey_t zkey = zkey::encode(x,y);


    zkey::decode(zkey, x, y);




    return 0;
}

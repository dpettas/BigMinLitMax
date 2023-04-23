#include <iostream>
#include <cstdio>
#include "Zkey.hpp"

int main(int argc, char** argv) 
{
    uint32_t x = 10;
    uint32_t y = 1025;
    uint32_t z = 1123;

    Zkey_t zkey = zkey::encode(x,y, z);


    zkey::decode(zkey, x, y, z);


    printf("%d %d %d\n", x, y, z);



    return 0;
}

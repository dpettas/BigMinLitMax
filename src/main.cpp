#include <iostream>
#include <bitset>
#include <Timer.hpp>
#include "Zkey.hpp"
#include "BigMinLitMax.hpp"


int main(int argc, char** argv) 
{
    uint32_t xmin = 2;
    uint32_t xmax = 5;

    uint32_t ymin = 2;
    uint32_t ymax = 5;

    uint32_t zmin = 2;
    uint32_t zmax = 5;



    auto search = BigMinLitMax({3, 5}, 
                               {5, 10});

    std::cout <<  search.bigmin(58) << std::endl;
    std::cout <<  search.litmax(58) << std::endl;

    Zkey_t bmin; 
    Zkey_t lmax;
    search.bigmin_litmax(58, bmin, lmax);
    std::cout << bmin << std::endl;
    std::cout << lmax << std::endl;





    return 0;
}

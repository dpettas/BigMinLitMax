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



    auto search = BigMinLitMax({xmin, xmax}, 
                               {xmin, xmax},
                               {xmin, xmax});


    double time = 
    Timer(
        [&]()
        {
            for(uint32_t key = search.zkey_min()+1; key < search.zkey_max(); ++key)
            {
                Zkey_t bigmin = search.bigmin(key);
                Zkey_t litmax = search.litmax(key);
                
                if( !search.is_in_the_range(bigmin) )
                {
                    std::cout << "Error in bigmin calculation\n";
                    std::cout << "Case :: " << key - search.zkey_min() << std::endl;
                    std::cout << "zmin :: " << search.zkey_min() << std::endl;
                    std::cout << "zmax :: " << search.zkey_max() << std::endl;
                    std::cout << "key  :: " << key << std::endl;
                    exit(1);
                }

                if( !search.is_in_the_range(litmax) )
                {
                    std::cout << "Error in litmax calculation\n";
                    std::cout << "Case :: " << key - search.zkey_min() << std::endl;
                    std::cout << "zmin :: " << search.zkey_min() << std::endl;
                    std::cout << "zmax :: " << search.zkey_max() << std::endl;
                    std::cout << "key  :: " << key << std::endl;
                    exit(1);
                }

                std::cout << bigmin << " " << litmax << std::endl;
            }
        }
    ,1).duration();


    std::cout << time << std::endl;






    return 0;
}

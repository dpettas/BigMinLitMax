#ifndef BIGMINLITMAX_HPP
#define BIGMINLITMAX_HPP

#include <stdint.h>
#include "Zkey.hpp"

class BigMinLitMax
{
    public:
        BigMinLitMax() = default;
    private:
        uint32_t xmin;
        uint32_t xmax;

        uint32_t ymin;
        uint32_t ymax;

        uint32_t zmin;
        uint32_t zmax;
};


#endif /* BIGMIMLITMAX_HPP */
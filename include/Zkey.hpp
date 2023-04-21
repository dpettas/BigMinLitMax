#ifndef ZKEY_HPP
#define ZKEY_HPP

#include <stdint.h>

// Define the Zkey type
using Zkey_t = uint64_t;

namespace zkey
{
    Zkey_t encode(              uint32_t  x, uint32_t  y);
    void   decode( Zkey_t zkey, uint32_t& x, uint32_t& y);

}

#endif // ZKEY_HPPP
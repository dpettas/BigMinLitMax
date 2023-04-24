#ifndef BIGMINLITMAX_HPP
#define BIGMINLITMAX_HPP

#include <stdint.h>
#include <Zkey.hpp>

class BigMinLitMax
{
    public: 
        struct Range_t
        {
            uint32_t left;
            uint32_t right;
        };
        
    public:
        BigMinLitMax() = delete;
        BigMinLitMax( Range_t xrange, Range_t yrange);
        
        Zkey_t bigmin( Zkey_t zval) const;

        Zkey_t zkey_min() const;
        Zkey_t zkey_max() const;

        bool is_in_the_range( Zkey_t zval) const;
         
    private:
        uint32_t xmin;
        uint32_t xmax;

        uint32_t ymin;
        uint32_t ymax;
};


#endif /* BIGMIMLITMAX_HPP */
#ifndef BIGMINLITMAX_HPP
#define BIGMINLITMAX_HPP

#include <stdint.h>
#include <limits>
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
        static Zkey_t end(){ return std::numeric_limits<uint64_t>::max(); }


        BigMinLitMax() = delete;
        BigMinLitMax( Range_t xrange, Range_t yrange, Range_t zrange);
        
        Zkey_t bigmin( Zkey_t zval) const;
        Zkey_t litmax( Zkey_t zval) const;
        void   bigmin_litmax( Zkey_t zval, Zkey_t& bigmin, Zkey_t& litmax) const;

        Zkey_t zkey_min() const;
        Zkey_t zkey_max() const;
        Zkey_t next_of (Zkey_t zval) const;
        Zkey_t prev_of (Zkey_t zval) const;

        bool is_in_the_range( Zkey_t zval) const;
         
    private:
        Zkey_t   z_min;
        Zkey_t   z_max;

        uint32_t xmin;
        uint32_t xmax;

        uint32_t ymin;
        uint32_t ymax;

        uint32_t zmin;
        uint32_t zmax;
};


#endif /* BIGMIMLITMAX_HPP */
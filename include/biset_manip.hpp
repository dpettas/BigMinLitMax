#ifndef BITSET_MANIP_HPP
#define BITSET_MANIP_HPP

#include <stdint.h>

int  bitset_msb_position ( uint64_t  bset);

void bitset_turn_on_bit  ( uint64_t& bset, int i);
void bitset_turn_off_bit ( uint64_t& bset, int i);

void bitset_turn_on_bits ( uint64_t& bset, int start, int stop, int step);
void bitset_turn_off_bits( uint64_t& bset, int start, int stop, int step);

uint64_t bitset_set_ones( int start);
#endif
#ifndef LIBTH_BITFIELDS_H
#define LIBTH_BITFIELDS_H

#include <stdint.h>

#define SET_BIT(v,b)    v |=   0x1 << b
#define UNSET_BIT(v,b)  v &= ~(0x1 << b)
#define TOGGLE_BIT(v,b) v ^= 0x1 << b
#define GET_BIT(v,b)    (v >> b) % 2

struct Printb
{
    const uint8_t nl : 1;
    const uint8_t prefix : 2;
    const uint8_t fill_zero : 3;
};
extern struct Printb Printb;

/* Print the binary representation of an unsigned int.

   opts is a bitfield witch can be 1 or more of the following:
     0                : no extra options
     Printb.nl        : Print a trailing '\n'.
     Printb.prefix    : Print "0b" prefix.
     Printb.fill_zero : Print leading zeros to the left of the number.

   If an unkown opts is given, nothing will be printed and -1 will be returned.

   return 0 on success.
 */
int printb(unsigned int number, uint8_t opts);

#endif // LIBTH_BITFIELDS_H

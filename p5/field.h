/** 
    @file field.h
    @author William J Krjacovic (wjkrajco)
    This is the field.c header file. This class is to used for arithmetic operations
    on bytes.
*/

#ifndef _FIELD_H_
#define _FIELD_H_

/** Type used for our field, an unsigned byte. */
typedef unsigned char byte;

/** Number of bits in a byte. */
#define BBITS 8

#define HEX_FOR_REDUCTION 0x1B

#define HEX_FOR_HIGH_BIT 0x80

/** 
    This is the fieldAdd function. The function preforms the addition operation
    in 8-bit Galois with byte a and byte b

    @param a The first byte to be added
    @param b The second byte to be added
    @return The byte that is the result of the addition
*/
byte fieldAdd(byte a, byte b);

/** 
    This is the fieldSub function. The function preforms the subtraction operation
    in 8-bit Galois with byte a and byte b

    @param a The first byte to be subtracted
    @param b The second byte to be subtracted
    @return The byte that is the result of the subtraction
*/
byte fieldSub(byte a, byte b);

/** 
    This is the fieldMul function. The function preforms the multiplication operation
    in 8-bit Galois with byte a and byte b

    @param a The first byte to be multiplied
    @param b The second byte to be multiplied
    @return The byte that is the result of the multiplication
*/
byte fieldMul(byte a, byte b);

#endif

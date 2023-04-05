/** 
    @file aes.h
    @author William J Krjacovic (wjkrajco)
    This is the header file for aes.c which is the file that is responsible
    for the decryption and encryption based on given keys using the AES method.
*/
#ifndef _AES_H_
#define _AES_H_

#include "field.h"


/** Number of bytes in an AES key or an AES block. */
#define BLOCK_SIZE 16

/** Numer of rows when a data block is arranged in a square. */
#define BLOCK_ROWS 4

/** Numer of columns when a data block is arranged in a square. */
#define BLOCK_COLS 4

/** Number of bytes in a word. */
#define WORD_SIZE 4

/** Number of roudns for 128-bit AES. */
#define ROUNDS 10

/**Moving over in an array two spaces*/
#define MOVE_OVER_TWO 2

/**Moving over in an array three spaces*/
#define MOVE_OVER_THREE 3

/** 
    This function takes in an arry of bytes in src, preforms substitution and multiplies
    by a constant then adds the values to the dest array
    @param src The 4 byte input array.
    @param dest The 4 byte output array.
    @param r The round of operation to determine constant mutiplication
*/
void gFunction( byte dest[ WORD_SIZE ], byte const src[ WORD_SIZE ], int r );

/** 
    This function takes in an arry of bytes in subkey, which is an array that holds the subkeys
    for each round of computation. The function also takes in key which is a 16 byte array that will
    be used to create the subkeys
    @param subkey The array of subkeys created from key.
    @param key The array of bytes used to make subkeys.
*/
void generateSubkeys( byte subkey[ ROUNDS + 1 ][ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] );

/** 
    The addSubkey function uses the add operation from Galois field to add
    each byte of the subkey to the corresponding byte from the current block.
    @param data The array that is being added to
    @param key The subkey that is being added to data.
*/
void addSubkey( byte data[ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] );

/** 
    This function takes the data array and puts the bytes into the square shaped matrix
    @param square The square shaped matrix that will take data
    @param data The block matrix that will be put into square.
*/
void blockToSquare( byte square[ BLOCK_ROWS ][ BLOCK_COLS ], byte const data[ BLOCK_SIZE ] );

/** 
    This function takes the square matrix and puts the bytes into the data array.
    @param data The array that will take the information from square.
    @param square The square shaped matrix that will be put into data data
*/
void squareToBlock( byte data[ BLOCK_SIZE ], byte const square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/** 
    This function shifts the rows of square so that for every row the column shifts one more than the last.
    @param square The square matrix that will be altered.
*/
void shiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/** 
    This function unshifts the rows. Undoing what was done in shiftRows. Shifting to the right instead
    of shifting the columns to the left.
    @param square The square matrix that will be altered.
*/
void unShiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/** 
    This function mixes the columns of the square matrix by matrix multiplications
    with another constant matrix
    @param square The square matrix that will be altered.
*/
void mixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/** 
    This function unmixes the columns of the square matrix by matrix multiplications
    with another constant matrix but inverse.
    @param square The square matrix that will be altered.
*/
void unMixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/** 
    This function calls to all the other functions in the program that will complete
    all ten rounds of encryption.
    @param data The array that will hold the result of the encryption.
    @param key They array that gives the key for encryption.
*/
void encryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] );

/** 
    This function calls to all the other functions in the program that will complete
    all ten rounds of decryption.
    @param data The array that will hold the result of the decryption.
    @param key They array that gives the key for decryption.
*/
void decryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] );

#endif

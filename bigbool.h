#ifndef BIGBOOL_H
#define BIGBOOL_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH_OF_PARTS 20

#define BB_NULL_ARG 1
#define BB_CANT_ALLOCATE 2
#define BB_EMPTY_VECTOR 3
#define BB_BAD_STRING 4
#define BB_COPY_ITSELF 5
#define BB_OK 0
#define BB_BIG_SHIFT 6
#define BB_SMALL_SHIFT 7

struct bigbool
{
    uint8_t parts [LENGTH_OF_PARTS];//Количество символов
    int last_bit;//биты
    int last_byte;//байты
};

typedef struct bigbool bigb;

int vec_zero(bigb* vector);
/*
    Function: 
        int vec_zero(bigb* vector)

    Logic: 
        resets the vector

    Returns:
        1)BB_OK - function work properly
        2)BB_NULL_ARG - vector == NULL
*/

size_t size_bits(bigb* v);//V
/*
    Function: 
        size_t size_bits(bigb* v)

    Logic: 
        return vector length

    Returns:
        1)vector length
        
*/

int left_shift (bigb* vector,bigb* results, int sizeShift);//V
/*
    Function: 
        int left_shift (bigb* vector,bigb* results, int sizeShift)

    Logic: 
        do left shift of bool vector

    Returns:
        1)BB_NULL_ARG - vector == NULL or result == NULL
        2)BB_OK - function work properly
        3)vec_zero(res)(zero vector) - if sizeshift more then vector length
*/

int right_shift (bigb* vector, bigb* results, int sizeShift);//V
/*
    Function: 
        int right_shift (bigb* vector, bigb* results, int sizeShift)

    Logic: 
        do right shift of bool vector

    Returns:
        1)BB_NULL_ARG - vector == NULL or result == NULL
        2)BB_OK - function work properly
        3)vec_zero(res)(zero vector) - if sizeshift more then vector length
*/

int left_cshift(bigb *vector, bigb *results, int sizeShift);

/*
    Function: 
        int left_cshift(bigb *vector, bigb *results, int sizeShift)

    Logic: 
        do left cycle shift of bool vector

    Returns:
        1)BB_NULL_ARG - vector == NULL or result == NULL
        2)BB_OK - function work properly
        3)BB_CANT_ALLOCATE - didnt allocate memory of vector in function
*/
int right_cshift(bigb *vector, bigb *results, int sizeShift);//V
/*
    Function: 
        int right_cshift(bigb *vector, bigb *results, int sizeShift)

    Logic: 
        do right cycle shift of bool vector

    Returns:
        1)BB_NULL_ARG - vector == NULL or result == NULL
*/

int bb_from_string (const char* str,bigb* v);//V
/*
    Function: 
        int bb_from_string (const char* str,bigb* v)

    Logic: 
        transfer vector from string to bigb

    Returns:
        1)BB_OK - string is normaly or function is work properly
        2)BB_NULL_ARG - v == NULL

*/

char* bb_to_string (bigb* vector);//V
/*
    Function: 
        char* bb_to_string (bigb* vector)

    Logic: 
        transfer vector from bigb to string

    Returns:
        1)BB_NULL_ARG - vector == NULL
        2)BB_NOT_ALLOCATE - Didn't allocate memory to string in function

*/

int bb_from_uint64_t (uint64_t number, bigb* v);
/*
    Function: 
        int bb_from_uint64_t (uint64_t number, bigb* v)

    Logic: 
        transfer vector from 64 bit number to bigb

    Returns:
        1)BB_NULL_ARG - v == NULL
        2)BB_OK - function work properly

*/


int bb_disjunction (bigb* vector1, bigb* vector2, bigb* res);//or V
/*
    Function: 
        int bb_disjunction (bigb* vector1, bigb* vector2, bigb* res)

    Logic: 
        complete disjunction operation with two vectors

    Returns:
        1)BB_NULL_ARG - vector1 == NULL or vector2== NULL or res==NULL 
        2)BB_OK - function work properly

*/

int bb_conjunction (bigb* vector1, bigb* vector2, bigb* res);//and V
/*
    Function: 
        int bb_conjunction (bigb* vector1, bigb* vector2, bigb* results)

    Logic: 
        complete conjunction operation with two vectors

    Returns:
        1)BB_NULL_ARG - vector1 == NULL or vector2== NULL or res==NULL 
        2)BB_OK - function work properly

*/

int bb_xor (bigb* vector1, bigb* vector2, bigb* res);//V
/*
    Function: 
        int bb_xor (bigb* vector1, bigb* vector2, bigb* res)

    Logic: 
        complete xor operation with two vectors

    Returns:
        1)BB_NULL_ARG - vector1 == NULL or vector2== NULL or res==NULL 
        2)BB_OK - function work properly
*/

int bb_inversion (bigb* vector1, bigb* res); //V
/*
    Function: 
        int bb_xor (bigb* vector1, bigb* vector2, bigb* res)

    Logic: 
        complete inversion with vector

    Returns:
        1)BB_NULL_ARG - vector1 == NULL or res==NULL 
        2)BB_OK - function work properly
*/      

#endif

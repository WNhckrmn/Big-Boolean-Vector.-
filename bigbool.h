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

int vec_zero(bigb* vector);//V

int copy_vector(bigb* v, bigb* res);//V

size_t size_bits(bigb* v);//V

int left_shift (bigb* vector,bigb* results, int sizeshift);//V

int right_shift (bigb* vector, bigb* results, int size_of_shift);//V

int left_cshift(bigb *vector, bigb *results, int sizeShift);

int right_cshift(bigb *vector, bigb *results, int sizeShift);//V

int bb_from_string (const char* str,bigb* v);//V

char* bb_to_string (bigb* vector);//V

int bb_from_uint64_t (uint64_t number, bigb* v);//V

int bb_disjunction (bigb* vector1, bigb* vector2, bigb* res);//or V

int bb_conjunction (bigb* vector1, bigb* vector2, bigb* results);//and V

int bb_xor (bigb* vector1, bigb* vector2, bigb* res);//V

int bb_inversion (bigb* vector1, bigb* res); //V


#endif
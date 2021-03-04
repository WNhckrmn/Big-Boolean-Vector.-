#include "bigbool.h"
#include <stdio.h>


/* ______________________
   | HELPER FUNCTIONS   |
   |____________________|   
*/    


size_t high_bit(uint64_t num) 
{
    size_t bytes = 0;
    size_t bits = 0;
    while ((num>> ((bytes + 1) * 8)) != 0)
    {
        bytes++;
    }    
    while ((num >> (bytes * 8 + bits)) != 0)
    {
        bits++;
    }    
    return bytes * 8 + bits;
};

size_t size_bits(bigb* v)
{
    size_t len = v->last_byte*8 + v->last_bit;
    return len;
};

int check_str(const char* str)
{
    int len = strlen(str);
    if (len > LENGTH_OF_PARTS * 8)
    {
        return BB_BAD_STRING;
    }
    
    if (len == 0)
    {
        return BB_NULL_ARG;
    }

    for(size_t el = 0;el < len ; el++)
    {
        if((str[el]!='1')&&(str[el]!='0'))
        {
            return BB_BAD_STRING;
        }
    }
    return BB_OK;
};

int vec_zero(bigb* v)
{
    if(v == NULL)
    {
        return BB_NULL_ARG;
    }
    memset(v->parts, 0, LENGTH_OF_PARTS);
    v->last_bit = 0;
    v->last_byte = 0;
    return BB_OK;
};

int take_bit(bigb *v, int pos)
{
    return (v->parts[pos / 8] >> (pos % 8) & 1);
};


/* ______________________
   |      TRANSFER      |
   |____________________|   
*/    


int bb_from_string(const char* str, bigb* v)
{
    int check;
    if((check = (check_str(str))))
    {
        return BB_OK;
    }

    if (v == NULL)
    {
        return BB_NULL_ARG;
    }

    size_t len = strlen(str);
    
    memset(v->parts, 0, LENGTH_OF_PARTS);

    size_t last_byte = len / 8;
    size_t last_bit = len % 8;

    v->last_byte = last_byte;
    v->last_bit = last_bit;

    size_t j = 0;
    
    for(size_t byte = 0; byte < last_byte; byte++ )
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            j = len - 1 - (byte * 8 + bit);             
            v->parts[byte] |= ((str[j]-'0')<<bit); 
        }
    }
    for(size_t bit = 0; bit < last_bit; bit++)
    {
        j = len - 1 - (last_byte * 8 + bit);
        v->parts[last_byte] |= (((str[j])-'0')<<bit);
    }
    return BB_OK;
};

// bigb* bb_from_string(const char* str, bigb* v)
// {
    
// }

char* bb_to_string(bigb* v)
{
    if(v == NULL)
    {
        return NULL;
    }

    size_t len = size_bits(v);

    char* str =(char*)calloc(len,sizeof(char*));
    if(str == NULL)
    {
        return NULL;
    }

    for(int posSTR = 0; posSTR < len; posSTR++)
    {
       str[len - 1 - posSTR] = '0' + take_bit(v, posSTR);
    }
    str[len]='\0';
    return str;
};

 int bb_from_uint64_t(uint64_t number, bigb* v)
 {
     if(v == NULL)
     {
         return BB_NULL_ARG;
     }

     memset(v->parts, 0,LENGTH_OF_PARTS);

     for (int i = 0; i < 8; i++)
     {
        v->parts[i] |= (number >> 8 * i);
     }

    size_t pos = high_bit(number);

    v->last_byte = pos / 8;
    v->last_bit = pos % 8;   

    return BB_OK; 
};


/* ______________________
   |   BIT OPERATIONS   |
   |____________________|   
*/ 


int bb_disjunction(bigb* v1, bigb* v2, bigb* v){

    if (v1 == NULL || v == NULL ||v2 == NULL){
        return BB_NULL_ARG;
    }
    if(size_bits(v1) < size_bits(v2)){
        return bb_disjunction(v2, v1, v);
    }
    memset(v->parts, 0, LENGTH_OF_PARTS);
    v->last_byte= v1->last_byte;
    v->last_bit = v1->last_bit;

    for(size_t part = 0; part < size_bits(v2); part++){
        v->parts[part] = v1->parts[part] | v2->parts[part];
    }
    for(size_t bit = size_bits(v2); bit < size_bits(v1); bit++) {
        v->parts[bit] = v1->parts[bit];
    }

    return BB_OK;
};

int bb_conjunction (bigb* v1, bigb* v2, bigb* v){

    if (v1 == NULL || v == NULL || v2 == NULL) {
        return BB_NULL_ARG;
    }
    if(size_bits(v1) < size_bits(v2)) {
        return bb_conjunction(v2, v1, v);
    }
    memset(v->parts, 0, LENGTH_OF_PARTS);
    v->last_byte = v1->last_byte;
    v->last_bit = v1->last_bit;

    for (int pos = 0; pos < size_bits(v2); pos++) {
        // v->parts[pos/8] |= (take_bit(v1, pos) & take_bit(v2, pos)) << (pos % 8);
        v->parts[pos] = v1->parts[pos] & v2->parts[pos];
    }
    for (int pos = size_bits(v2); pos < size_bits(v1); pos++) {
        //v->parts[pos / 8] |= take_bit(v1, pos) << (pos % 8);
        v->parts[pos]=0;
    }
    return BB_OK;
};

int bb_xor(bigb* v1, bigb* v2, bigb* res)
{
    if (v1 == NULL || v2 == NULL || res == NULL )
    {
        return BB_NULL_ARG;
    }

    if(size_bits(v2)>size_bits(v1))
    {
        return bb_xor(v2, v1, res);
    }

    res->last_byte = v1->last_byte;
    res->last_bit = v1->last_bit;

    
    // for (size_t i = 0; i < res->last_byte; i++)
    // {
    //     if(i <= v2->last_byte)
    //     {
    //         res->parts[i] = v1->parts[i] ^ v2->parts[i];
    //     }
    //     else
    //     {
    //         res->parts[i] = v1->parts[i];
    //     }
        
    // }

    // for (size_t byte = 0; byte < ; byte++)
    // {
        
    // }
    for (size_t byte = 0; byte < v2->last_byte; byte++)
    {
        res->parts[byte] = v1->parts[byte] ^ v2->parts[byte];
    }
    for (size_t bit = v2->last_byte; bit < v2->last_bit; bit++)
    {
        res->parts[bit] = v1->parts[bit]^v2->parts[bit];
    }
    

    return BB_OK;
};

int bb_inversion(bigb* v1, bigb* res)
{
    if (v1 == NULL || res == NULL )
    {
        return BB_NULL_ARG;
    }

    res->last_byte = v1->last_byte;
    res->last_bit = v1->last_bit;

    for (size_t i = 0; i < res->last_byte; i++)
    { 
        res->parts[i] = ~v1->parts[i];
    }
    for (size_t i = res->last_byte; i < res->last_bit; i++)
    {
        res->parts[i] = ~v1->parts[i];
    }
    
    return BB_OK;
};


/* ______________________
   |      SHIFTS        |
   |____________________|   
*/    


int right_shift (bigb *vector, bigb *res, int len_shift)
{
    if (vector == NULL || res == NULL)
    {
        return BB_NULL_ARG;

    }
    if (abs(len_shift) > size_bits(vector))
    {
        return vec_zero(res);
    }

    if (len_shift < 0)
        return left_shift(vector, res, abs(len_shift));


    size_t  vector_res_len = size_bits(vector) - len_shift;
    res->last_byte = vector_res_len / 8;
    res->last_bit = vector_res_len % 8;

    size_t dif_byte = len_shift / 8;
    size_t dif_bit = len_shift % 8;

    for (size_t part = 0; part <= (res->last_byte + 1); part++)
    {
        res->parts[part] = vector->parts[part + dif_byte];
    }

    for (size_t part = 0; part <= res->last_byte; part++)
    {
        res->parts[part] >>= dif_bit;
        uint8_t buf_part = res->parts[part + 1];
        buf_part <<= (8 - dif_bit);
        res->parts[part] |= buf_part;
    }
    res->parts[res->last_byte + 1] = 0;

    return BB_OK;
};

int left_shift (bigb *vector, bigb *res, int len_shift)
{
    if (vector == NULL || res == NULL)
        return BB_NULL_ARG;

    if (abs(len_shift) > size_bits(vector))
        return vec_zero(res);

    if (len_shift < 0)
        return right_shift(vector, res, abs(len_shift));


    size_t  vector_res_len = size_bits(vector) - len_shift;
    res->last_byte = vector_res_len / 8;
    res->last_bit = vector_res_len % 8;

    for (size_t part = 0; part <= res->last_byte; part++)
        res->parts[part] = vector->parts[part];

    size_t bit_shift = 8 - res->last_bit;
    res->parts[res->last_byte] <<= bit_shift;
    res->parts[res->last_byte] >>= bit_shift;

    return BB_OK;
}

int left_cshift(bigb *vector, bigb *res, int len_shift)
{
    if (vector == NULL || res == NULL)
        return BB_NULL_ARG;

    if (len_shift < 0)
        return right_cshift(vector, res, abs(len_shift));

    bigb *buf_vector = (bigb*)calloc(1, sizeof(bigb*));
    if (buf_vector == NULL)
        return BB_CANT_ALLOCATE;

    len_shift %= size_bits(vector);
    left_shift(vector, buf_vector, len_shift);
    right_shift(vector, res, (size_bits(vector) - len_shift));

    for (size_t part = 0; part <= buf_vector->last_byte; part++)
        res->parts[res->last_byte + part + 1] = buf_vector->parts[part];

    for (size_t part = res->last_byte; part <= (vector->last_byte + 1); part++)
    {
        uint8_t buf_part = res->parts[part + 1];
        buf_part <<= (res->last_bit);
        res->parts[part] |= buf_part;
        res->parts[part + 1] >>= (8 - res->last_bit);
    }

    res->last_byte = vector->last_byte;
    res->last_bit = vector->last_bit;

    //free(buf_vector);
    return BB_OK;
}

int right_cshift(bigb *vector, bigb *res, int len_shift)
{
    if (vector == NULL || res == NULL)
        return BB_NULL_ARG;

    if (len_shift < 0)
        return left_cshift(vector, res, abs(len_shift));

    len_shift %=size_bits(vector);
    size_t rev_len_shift = size_bits(vector) - len_shift;
    return left_cshift(vector, res, rev_len_shift);
}



// int main()
// {
    
//     int response = 0;

//     bigb* v1 =(bigb*)calloc(1, sizeof(bigb));
//     //bigb* result1 = calloc(1, sizeof(bigb));
//     bigb* v2 = (bigb*)calloc(1, sizeof(bigb));
//     bigb* v = (bigb*)calloc(1, sizeof(bigb));

//     int err_flag = 0;



//     bb_from_string("1010101010101010101010101", v1);

//     // bb_disjunction(v1, v2, v);

//     // char* str = bb_to_string(v);

//     // if(strcmp("1111111111111111111111111", str))
//     // {
//     //     printf("1error in bb_disjunction\n");
//     //     err_flag++;
//     // }

//     // vec_zero(v1);
//     // vec_zero(v2);
//     // vec_zero(v);


//     // //equile vectors

//     // bb_from_string("10101010101010101010101010101010101010101011010101010110101010100101010001101010100", v1);
//     // bb_from_string("10101010101010101010101010101010101010101011010101010110101010100101010001101010100", v2);

//     // bb_disjunction(v1, v2, v);

//     // str = bb_to_string(v);

//     // if(strcmp("10101010101010101010101010101010101010101011010101010110101010100101010001101010100", str))
//     // {
//     //     printf("2error in bb_disjunction\n");
//     //     err_flag++;
//     // }

//     // vec_zero(v1);
//     // vec_zero(v2);
//     // vec_zero(v);

//     // // v2 > v1
//     // bb_from_string("101001110110011", v1);
//     // bb_from_string("1010101010101010101001", v2);

//     // bb_disjunction(v1, v2, v);

//     // str = bb_to_string(v);

//     // if(strcmp("1010101111101110111011", str))
//     // {
//     //     printf("3error in bb_disjunction\n");
//     //     err_flag++;
//     // }

//     // vec_zero(v1);
//     // vec_zero(v2);
//     // vec_zero(v);

//     // bb_from_string("1010101010101010101", v1);
//     // bb_from_string("0101010101010101010", v2);

//     // bb_xor(v1, v2, v);

//     // char* str = bb_to_string(v);
//     // if(strcmp("1111111111111111111", str))
//     // {
//     //     printf("1error in xor\n");
//     //     err_flag++;
//     // }

//     // vec_zero(v1);
//     // vec_zero(v2);
//     // vec_zero(v);

//     // //equile vectors
//     // bb_from_string("1010101010101010101", v1);
//     // bb_from_string("1010101010101010101", v2);

//     // bb_xor(v1, v2, v);

//     // str = bb_to_string(v);
//     // if(strcmp("0000000000000000000", str))
//     // {
//     //     printf("2error in xor\n");
//     //     err_flag++;
//     // }

//     // vec_zero(v1);
//     // vec_zero(v2);
//     // vec_zero(v);

//     // //v2 > v1
//     // bb_from_string("1110111010111", v1);
//     // bb_from_string("10101010101010101010", v2);
   
   
//     // bb_xor(v1, v2, v);
    

//     // str = bb_to_string(v);
//     // if(strcmp("10101011011101111101", str))
//     // {
//     //     printf("3error in xor\n");
//     //     err_flag++;
//     // }

//     // vec_zero(v1);
//     // vec_zero(v2);
//     // vec_zero(v);

//     // bb_from_string("000000000000000000000000", v1);
//     // bb_inversion(v1, v);
//     // str = bb_to_string(v);

//     // if(strcmp("111111111111111111111111", str))
//     // {
//     //     printf(" 1error in inversion\n");
//     //     err_flag++;
//     // }

//     // vec_zero(v1);
//     // vec_zero(v);

//     // bb_from_string("11110101", v1);
//     // bb_from_string("100010110101", v2);
//     // bb_conjunction(v1, v2, v);
//     // str = bb_to_string(v);
//     // if(strcmp("000010110101", str))
//     // {
//     //     printf ("3error in bb_conjunction\n");
//     //     err_flag++;
//     // }
//     // vec_zero(v);
//     // vec_zero(v1);
//     // vec_zero(v2);

//     //norm. situation
//     // bb_from_string("101010101010101010101010100011", v);
//     // char* str = bb_to_string(v);
    
//     // if(strcmp("101010101010101010101010100011",str))
//     // {
//     //     printf("error in transfer bb_from_str -> bb_to_str\n");
//     //     err_flag++;
//     // }
//     // vec_zero(v);

//     // // if len equile byte
//     // bb_from_string("100000010001", v);
//     // char* str1 = bb_to_string(v);
//     // if(strcmp("100000010001", str1))
//     // {
//     //     // print(str);
//     //     printf("error in transfer bb_from_str -> bb_to_str\n");
//     //     err_flag++;
//     // }
//     // vec_zero(v);

//     // //max len(parts * 8)
//     // bb_from_string("101000110011101100111110101001111100111111010111110100011110010101010101110101010000001111111010101001001010101010101001010101110011010100111000101100000000110", v);
//     // char* str2 = bb_to_string(v);
//     // if(strcmp("101000110011101100111110101001111100111111010111110100011110010101010101110101010000001111111010101001001010101010101001010101110011010100111000101100000000110",str2))
//     // {
//     //     printf(str2);
//     //     printf("error in transfer bb_from_str -> bb_to_str\n");
//     //     err_flag++;
//     // }
//     // free(v);
     
//     printf("bigb OK!   ");
//     return 0;
// }
#include "bigbool.c"
#define RESET "\033[0m"
#define RED   "\033[31m"
#define GREEN "\033[32m"
#define LOG_ERR(msg) \
	printf(RED "%s:%d %s\n [WARNING!ERROR!]: %s\n" RESET,\
		__FILE__, __LINE__, __func__, msg);



int test_bb_to_from_string(bigb* v)
{
    int err_flag = 0;
    //norm. situation
    bb_from_string("101010101010101010101010100011", v);
    char* str = bb_to_string(v);
    
    if(strcmp("101010101010101010101010100011",str))
    {
        LOG_ERR("error in transfer bb_from_str -> bb_to_str\n");
        err_flag++;
    }
    vec_zero(v);

    // if len equile byte
    bb_from_string("100000010001", v);
    char* str1 = bb_to_string(v);
    if(strcmp("100000010001", str1))
    {
        // print(str);
        LOG_ERR("error in transfer bb_from_str -> bb_to_str\n");
        err_flag++;
    }
    vec_zero(v);

    //max len(parts * 8)
    bb_from_string("101000110011101100111110101001111100111111010111110100011110010101010101110101010000001111111010101001001010101010101001010101110011010100111000101100000000110", v);
    char* str2 = bb_to_string(v);
    if(strcmp("101000110011101100111110101001111100111111010111110100011110010101010101110101010000001111111010101001001010101010101001010101110011010100111000101100000000110",str2))
    {
        LOG_ERR("error in transfer bb_from_str -> bb_to_str\n");
        err_flag++;
    }
    vec_zero(v);
    return err_flag;
};

int test_disjunction(bigb* v,bigb* v1, bigb* v2)
{
    int err_flag = 0;

    bb_from_string("1010101010101010101010101", v1);
    bb_from_string("0101010101010101010101010", v2);

    bb_disjunction(v1, v2, v);

    char* str = bb_to_string(v);

    if(strcmp("1111111111111111111111111", str))
    {
        LOG_ERR("1error in bb_disjunction\n");
        err_flag++;
    }

    vec_zero(v1);
    vec_zero(v2);
    vec_zero(v);


    //equile vectors

    bb_from_string("10101010101010101010101010101010101010101011010101010110101010100101010001101010100", v1);
    bb_from_string("10101010101010101010101010101010101010101011010101010110101010100101010001101010100", v2);

    bb_disjunction(v1, v2, v);

    str = bb_to_string(v);

    if(strcmp("10101010101010101010101010101010101010101011010101010110101010100101010001101010100", str))
    {
        LOG_ERR("2error in bb_disjunction\n");
        err_flag++;
    }

    vec_zero(v1);
    vec_zero(v2);
    vec_zero(v);

    // v2 > v1
    bb_from_string("101001110110011", v1);
    bb_from_string("1010101010101010101001", v2);

    bb_disjunction(v1, v2, v);

    str = bb_to_string(v);

    if(strcmp("1010101111101110111011", str))
    {
        LOG_ERR("3error in bb_disjunction\n");
        err_flag++;
    }

    vec_zero(v1);
    vec_zero(v2);
    vec_zero(v);

    return err_flag;
};

int test_conjunction(bigb* v, bigb*v1, bigb* v2)
{
    int err_flag = 0;
    //v2 > v1
    bb_from_string("11110101", v1);
    bb_from_string("100010110101", v2);
    bb_conjunction(v1, v2, v);
    char* str = bb_to_string(v);
    if(strcmp("000010110101", str))
    {
        LOG_ERR ("1error in bb_conjunction\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    vec_zero(v2);

    //norm situation

    bb_from_string("111101010101", v1);
    bb_from_string("100010110101", v2);
    bb_conjunction(v1, v2, v);
    str = bb_to_string(v);
    if(strcmp("100000010101", str))
    {
        LOG_ERR ("2error in bb_conjunction\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    vec_zero(v2);

    bb_from_string("111111111111111111111", v1);
    bb_from_string("000000000000000000000", v2);
    bb_conjunction(v1, v2, v);
    str = bb_to_string(v);
    if(strcmp("000000000000000000000", str))
    {
        LOG_ERR ("3error in bb_conjunction\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    vec_zero(v2);
    return err_flag;
};

int test_xor(bigb* v, bigb*v1, bigb* v2)
{
    int err_flag = 0;

    bb_from_string("10101010101010101010", v1);
    bb_from_string("01010101010101010101", v2);

    bb_xor(v1, v2, v);

    char* str = bb_to_string(v);
    if(strcmp("11111111111111111111", str))
    {
        LOG_ERR("1error in xor\n");
        err_flag++;
    }

    vec_zero(v1);
    vec_zero(v2);
    vec_zero(v);

    //equile vectors
    bb_from_string("10101010101010101010", v1);
    bb_from_string("10101010101010101010", v2);

    bb_xor(v1, v2, v);

    str = bb_to_string(v);
    if(strcmp("00000000000000000000", str))
    {
       LOG_ERR("2error in xor\n");
        err_flag++;
    }

    vec_zero(v1);
    vec_zero(v2);
    vec_zero(v);

    //v2 > v1
    bb_from_string("1110111010111", v1);
    bb_from_string("10101010101010101010", v2);
   
   
    bb_xor(v1, v2, v);
    

    str = bb_to_string(v);
    if(strcmp("10101011011101111101", str))
    {
       LOG_ERR("3error in xor\n");
        err_flag++;
    }

    vec_zero(v1);
    vec_zero(v2);
    vec_zero(v);
    return err_flag;
};

int test_inversion(bigb* v, bigb* v1)
{
    int err_flag = 0;
    bb_from_string("000000000000000000000000", v1);
    bb_inversion(v1, v);
    char* str = bb_to_string(v);

    if(strcmp("111111111111111111111111", str))
    {
        LOG_ERR(" 1error in inversion\n");
        err_flag++;
    }
    free(str);

    bb_from_string("101110111010101001010110", v1);
    bb_inversion(v1, v);
    str = bb_to_string(v);
    if(strcmp("010001000101010110101001", str))
    {
        LOG_ERR(" 2error in inversion\n");
        err_flag++;
    }

    vec_zero(v1);
    vec_zero(v);
    return err_flag;
}

int test_uint64(bigb *v)
{
    int err_flag = 0;

    //empty number
    bb_from_uint64_t(0, v);
    char *str = bb_to_string(v);
    if(strcmp("", str))
    {
        LOG_ERR ("incorrect bb_from_uint64_t -> bb_to_string");
        err_flag++;
    }
    vec_zero(v);
    free(str);

    //len % byte == 0
    bb_from_uint64_t(2048, v);
    str =bb_to_string(v);
    if(strcmp("100000000000", str))
    {
        LOG_ERR ("incorrect bb_from_uint64_t -> bb_to_string");
        err_flag++;
    }
    vec_zero(v);
    free(str);

    //standard situation
    bb_from_uint64_t(81273822, v);
    str = bb_to_string(v);
    if(strcmp("100110110000010001111011110", str))
    {
        LOG_ERR ("incorrect bb_from_uint64_t -> bb_to_string");
        err_flag++;
    }
    vec_zero(v);
    free(str);

    return err_flag;
}

int test_left_shift(bigb* v, bigb* v1)
{
    int err_flag = 0;

    //shift = size_bits(v)
    bb_from_string("10110110110101010101010000000001010000100101", v1);
    left_shift(v1, v, 44);
    char *str = bb_to_string(v);
    if (strcmp("", str)) 
    {
        LOG_ERR ("1)incorrect left_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //shift < byte
    bb_from_string("10110110110101010101000000000000000010101010101011010000000001010000100101", v1);
    left_shift(v1, v, 7);
    str = bb_to_string(v);
    if (strcmp("0110101010101000000000000000010101010101011010000000001010000100101", str)) 
    {
        LOG_ERR ("2)incorrect left_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //standard situation
    bb_from_string("10110110110101010101000000000000000010101010101011010000000001010000100101", v1);
    left_shift(v1, v, 48);
    str = bb_to_string(v);
    if (strcmp("11010000000001010000100101", str)) 
    {
        LOG_ERR ("3)incorrect left_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //negative shift
    bb_from_string("10110110110101010101000000000000000010101010101011010000000001010000100101", v1);
    left_shift(v1, v, -16);
    str = bb_to_string(v);
    if (strcmp("1011011011010101010100000000000000001010101010101101000000", str)) 
    {
        LOG_ERR ("incorrect BB_left_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);
    return err_flag;
}

int test_right_shift(bigb* v, bigb* v1)
{
    int err_flag = 0;
    //shift = size_bits(v)
    bb_from_string("10110110110101010101010000000001010000100101", v1);
    right_shift(v1, v, 44);
    char* str = bb_to_string(v);
    if (strcmp("", str)) {
        LOG_ERR ("incorrect right_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //shift < byte
    bb_from_string("10110110110101010101000000000000000010101010101011010000000001010000100101", v1);
    right_shift(v1, v, 7);
    str = bb_to_string(v);
    if (strcmp("1011011011010101010100000000000000001010101010101101000000000101000", str)) {
        LOG_ERR ("incorrect right_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //standard situation
    bb_from_string("10110110110101010101000000000000000010101010101011010000000001010000100101", v1);
    right_shift(v1, v, 48);
    str = bb_to_string(v);
    if (strcmp("10110110110101010101000000", str)) {
        LOG_ERR ("incorrect right_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //negative shift
    bb_from_string("10110110110101010101000000000000000010101010101011010000000001010000100101", v1);
    right_shift(v1, v, -16);
    str = bb_to_string(v);
    if (strcmp("0101000000000000000010101010101011010000000001010000100101", str)) {
        LOG_ERR ("incorrect right_shift");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    return err_flag;
}

int test_left_cshift(bigb* v, bigb* v1)
{
     int err_flag = 0;

    //len == shift
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    left_cshift(v1, v, 58);
    char *str = bb_to_string(v);
    if(strcmp("1000110101010010001000000000111111111100110000000001111110", str))
    {
        LOG_ERR ("incorrect left_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //empty shift
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    left_cshift(v1, v, 0);
    str = bb_to_string(v);
    if(strcmp("1000110101010010001000000000111111111100110000000001111110", str))
    {
        LOG_ERR ("incorrect left_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //shift > len
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    left_cshift(v1, v, 276);
    str = bb_to_string(v);
    if(strcmp("0000000111111010001101010100100010000000001111111111001100", str))
    {
        LOG_ERR ("incorrect left_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //standard situation
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    left_cshift(v1, v, 14);
    str = bb_to_string(v);
    if(strcmp("1000100000000011111111110011000000000111111010001101010100", str))
    {
        LOG_ERR ("incorrect left_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //negative shift
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    left_cshift(v1, v, -20);
    str = bb_to_string(v);
    if(strcmp("0011000000000111111010001101010100100010000000001111111111", str))
    {
        LOG_ERR ("incorrect left_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    return err_flag;
}

int test_right_cshift(bigb* v, bigb* v1)
{
    int err_flag = 0;
    //len == size_bits(v)
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    right_cshift(v1, v, 58);
    char* str = bb_to_string(v);
    if(strcmp("1000110101010010001000000000111111111100110000000001111110", str))
    {
        LOG_ERR ("incorrect right_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //empty shift
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    right_cshift(v1, v, 0);
    str = bb_to_string(v);
    if(strcmp("1000110101010010001000000000111111111100110000000001111110", str))
    {
        LOG_ERR ("incorrect right_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //shift > len
    bb_from_string("1000110101010010001000000000111111111100110000000001111110", v1);
    right_cshift(v1, v, 314);
    str = bb_to_string(v);
    if(strcmp("1111001100000000011111101000110101010010001000000000111111", str))
    {
        LOG_ERR ("incorrect right_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //standard situation
    bb_from_string("101100101111111111111111111110100101010000001010000111111111000100000100001", v1);
    right_cshift(v1, v, 36);
    str = bb_to_string(v);
    if(strcmp("000001010000111111111000100000100001101100101111111111111111111110100101010", str))
    {
        LOG_ERR ("incorrect right_cshift\n");
        err_flag++;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    //negative shift
    bb_from_string("101100101111111111111111111110100101010000001010000111111111000100000100001", v1);
    right_cshift(v1, v, -40);
    str = bb_to_string(v);
    if(strcmp("000010100001111111110001000001000011011001011111111111111111111101001010100", str))
    {
        LOG_ERR ("incorrect BB_right_cshift\n");
        err_flag;
    }
    vec_zero(v);
    vec_zero(v1);
    free(str);

    return err_flag;
}

int test_de_Morgan(bigb* v, bigb* v1, bigb* v2, bigb* v3, bigb* v4)
{
    int err_flag = 0;

    bb_from_string("1001000000000111111111101", v1);
    bb_from_string("1000110101010010001000000", v2);

    //~(A | B)( = ~A & ~B
    bb_disjunction(v1, v2, v);
    bb_inversion(v, v3);
    char *str1 = bb_to_string(v3);
    vec_zero(v);
    vec_zero(v3);
    bb_inversion(v1, v3);
    bb_inversion(v2, v4);
    bb_conjunction(v3, v4, v);
    char *str2 = bb_to_string(v);
    if(strcmp(str1, str2))
    {
        LOG_ERR ("incorrect ~(A | B) = ~A & ~B\n");
        err_flag++;
    }

    vec_zero(v);
    free(str1);
    free(str2);

    //~(A & B) = ~A | ~B
    bb_conjunction(v1, v2, v);
    vec_zero(v1);
    bb_inversion(v, v1);
    str1 = bb_to_string(v1);
    vec_zero(v);

    bb_disjunction(v3, v4, v);
    str2 = bb_to_string(v);

    if(strcmp(str1, str2))
    {
        LOG_ERR ("incorrect ~(A & B) = ~A | ~B\n");
        err_flag++;
    }

    vec_zero(v);
    vec_zero(v1);
    vec_zero(v2);
    vec_zero(v3);
    vec_zero(v4);
    free(str1);
    free(str2);
    return err_flag;
}


int main()
{
    int errors = 0;

    bigb* v1 =(bigb*)calloc(1, sizeof(bigb));
    bigb* v2 = (bigb*)calloc(1, sizeof(bigb));
    bigb* v = (bigb*)calloc(1, sizeof(bigb));
    bigb* v3 =(bigb*)calloc(1, sizeof(bigb));
    bigb* v4 = (bigb*)calloc(1, sizeof(bigb));

    errors += test_bb_to_from_string(v);
    errors += test_disjunction(v, v1, v2);
    errors +=test_conjunction(v, v1, v2) ;
    errors +=test_xor(v,v1, v2) ;
    errors +=test_inversion(v,v1); 
    errors +=test_uint64(v) ;
    errors += test_left_shift( v, v1);
    errors += test_right_shift(v, v1);
    errors +=test_left_cshift( v, v1);
    errors +=test_right_cshift( v, v1);
    errors +=test_de_Morgan(v, v1, v2, v3, v4);

    if (errors != 0)
    {
        printf(RED"YOU HAVE [ERROR]"RESET);
    }
    else
    {
        printf(GREEN"THAT's GOOD !"RESET);
    }

    return 0;
    
}
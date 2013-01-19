/****************************************************************************
 * log2.c
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * An implementation of the Bailey–Borwein–Plouffe (BBP) formula for log(2)
 * in binary.
 ***************************************************************************/

#include "../include/log2.h"
#include "../include/bbp.h"
#include "../include/aux.h"

char* log_2_binary(int d, int num_places)
{
    int base = 2;
    int c = 1;
    int (*p)(int) = &log_2_binary_p;
    long double result = compute_bbp(d, base, c, p, false);

    return convert_floating_decimal_to_base(result, num_places, base);
}

int log_2_binary_p(int k)
{
    return k;
}


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

/*
 * Function:  log_2_binary
 * --------------------
 * Computes the log(2) binary BBP formula.
 * It is the responsibility of the calling function to free the returned string.
 *
 *  d: binary digit to be calculated
 *  num_places: how many binary places to calculate
 *
 *  returns: the dth binary digit of log(2) (plus num_places - 1 more places)
 */
char* log_2_binary(int d, int num_places)
{
    int base = 2;
    int c = 1;
    void (*p)(mpz_t, mpz_t) = &log_2_binary_p;
    long double result = compute_bbp(d, base, c, p, false);

    return convert_floating_decimal_to_base(result, num_places, base);
}

/*
 * Function:  log_2_binary_p
 * --------------------
 * The polynomial p used for the log(2) BBP formula
 *
 *  k: input to the polynomial p
 *
 *  returns: p(k)
 */
void log_2_binary_p(mpz_t rop, mpz_t k)
{
    mpz_set(rop, k);
}


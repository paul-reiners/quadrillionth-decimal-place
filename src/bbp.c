/****************************************************************************
 * bbp.c
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * An implementation of the generic Bailey–Borwein–Plouffe (BBP) formula.
 ***************************************************************************/

#include <math.h>

#include "../include/aux.h"
#include "../include/bbp.h"

/*
 * Function:  compute_bbp 
 * --------------------
 * Computes the generic BBP formula.
 *
 *  d: digit to be calculated
 *  base: the base
 *  c: a fixed positive integer
 *  p: a simple polynomial like x or x^2
 *
 *  returns: the value of the BBP formula
 */
long double compute_bbp(int digit, int base, int c, int (*p)(int), bool start_at_0)
{
    int d = digit - 1;
    long double sum
        = mod_one(
                compute_bbp_first_sum(d, base, c, p, start_at_0)
                + compute_bbp_second_sum(d, base, c, p));

    return sum;
}

/*
 * Function:  compute_bbp_first_sum 
 * --------------------
 * Computes the first summand in the BBP formula.
 *
 *  d: digit to be calculated
 *  base: the base
 *  c: a fixed positive integer
 *  p: a simple polynomial like x or x^2
 *  start_at_0: start the summation at k=0, if true, at k=1, otherwise.  Most 
 *              instances of the BBP formula, such as pi, have you start at 0.  
 *              But some, such as log(2), have you start at 1.
 *
 *  returns: the value of the first sum
 */
long double compute_bbp_first_sum(int d, int base, int c, int (*p)(int), bool start_at_0)
{
    long double sum = 0.0;
    int k_start = start_at_0 ? 0 : 1;
    for (int k = k_start; k <= floor(d / c); k++)
    {
        int poly_result = (*p)(k);
        int num = modular_pow(base, d - c * k, poly_result);
        int denom = poly_result;
        sum += (long double) num / (long double) denom;
        sum = mod_one(sum);
    }

    return mod_one(sum);
}

/*
 * Function:  compute_bbp_second_sum 
 * --------------------
 * Computes the second summand in the BBP formula.
 *
 *  d: digit to be calculated
 *  base: the base
 *  c: a fixed positive integer
 *  p: a simple polynomial like x or x^2
 *
 *  returns: the value of the second sum
 */
long double compute_bbp_second_sum(int d, int base, int c, int (*p)(int))
{
    long double sum = 0.0;
    int k = floor(d / c) + 1;
    long double prev_sum = sum;
    long double machEps = calculate_machine_epsilon();
    do
    {
        prev_sum = sum;
        int poly_result = (*p)(k);
        long double num = pow(base, d - c * k);
        int denom = poly_result;
        sum += num / (long double) denom;

        k++;
    }
    while (fabs(sum - prev_sum) > machEps);

    return sum;
}


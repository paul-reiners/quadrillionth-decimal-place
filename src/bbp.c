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
                compute_bbp_first_sum_gmp(d, base, c, p, start_at_0)
                + compute_bbp_second_sum(d, base, c, p));

    return sum;
}

/*
 * Function:  compute_bbp_first_sum_gmp 
 * --------------------
 * Computes the first summand in the BBP formula using GNU GMP.
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
long double compute_bbp_first_sum_gmp(int d, int base, int c, int (*p)(int), bool start_at_0) {
    mpf_t sum;
    mpf_init(sum);
    mpf_set_d(sum, 0.0);
    
    int k_start = start_at_0 ? 0 : 1;
    for (int k = k_start; k <= floor(d / c); k++)
    {
        int poly_result = (*p)(k);
        
        mpz_t num;
        mpz_init(num);
        modular_pow_gmp(num, base, d - c * k, poly_result);
        mpf_t num_float;
        mpf_init(num_float);
        mpf_set_z(num_float, num);
        mpz_clear(num);
        
        unsigned long int denom = poly_result;
        
        mpf_t quotient;
        mpf_init(quotient);
        mpf_div_ui(quotient, num_float, denom);        
        mpf_clear(num_float);
        
        mpf_add(sum, sum, quotient);
        mpf_clear(quotient);
        
        mod_one_gmp(sum, sum);
    }
        
    mod_one_gmp(sum, sum);

    double result = mpf_get_d(sum);

    mpf_clear(sum);

    return result;
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


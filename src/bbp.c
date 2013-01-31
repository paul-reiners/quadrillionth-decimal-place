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
long double compute_bbp(int digit, int base, int c, long long int (*p)(long long int), bool start_at_0)
{
    int d = digit - 1;

    mpf_t mpf_first_sum;
    mpf_init(mpf_first_sum);
    compute_bbp_first_sum_gmp(mpf_first_sum, d, base, c, p, start_at_0);
    double first_sum = mpf_get_d(mpf_first_sum);
    mpf_clear(mpf_first_sum);

    mpf_t mpf_second_sum;
    mpf_init(mpf_second_sum);
    compute_bbp_second_sum_gmp(mpf_second_sum, d, base, c, p);
    double second_sum = mpf_get_d(mpf_second_sum);
    mpf_clear(mpf_second_sum);

    long double sum = mod_one(first_sum + second_sum);

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
void compute_bbp_first_sum_gmp(mpf_t sum, int d, int base, int c, long long int (*p)(long long int), bool start_at_0) {
    mpf_set_d(sum, 0.0);
    int k_start = start_at_0 ? 0 : 1;
    for (long long int k = k_start; k <= floor(d / c); k++)
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
}

/*
 * Function:  compute_bbp_second_sum_gmp 
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
void compute_bbp_second_sum_gmp(mpf_t sum, int d, int base, int c, long long int (*p)(long long int)) 
{
    mpf_set_d(sum, 0.0);

    long long int k = floor(d / c) + 1;

    mpf_t prev_sum;
    mpf_init(prev_sum);
    mpf_set(prev_sum, sum);
    
    mpf_t base_gmp;
    mpf_init(base_gmp);
    mpf_set_si(base_gmp, base);

    do
    {
        mpf_set(prev_sum, sum);
        int poly_result = (*p)(k);

        mpf_t num;
        mpf_init(num);
        mpf_pow_ui(num, base_gmp, d - c * k);
        
        unsigned long int denom = poly_result;
        
        mpf_t quotient;
        mpf_init(quotient);
        mpf_div_ui(quotient, num, denom);        
        mpf_clear(num);
        
        mpf_add(sum, sum, quotient);
        mpf_clear(quotient);

        k++;
    }
    while (mpf_cmp(prev_sum, sum) != 0);
}


/****************************************************************************
 * bbp.c
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * An implementation of the generic Bailey–Borwein–Plouffe (BBP) formula.
 ***************************************************************************/

#include <math.h>
#include <stdio.h>

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
long double compute_bbp(int digit, int base, int c, void (*p)(mpz_t, mpz_t), bool start_at_0)
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
void compute_bbp_first_sum_gmp(mpf_t sum, unsigned long int d, int base, long int c, void (*p)(mpz_t, mpz_t), bool start_at_0) {
    mpf_set_d(sum, 0.0);
    signed long int k_start = start_at_0 ? 0 : 1;

    mpz_t k;
    mpz_init_set_si(k, k_start);
    double upper = floor((double) d / (double) c);
    while (mpz_cmp_d(k, upper) <= 0)
    {        
        mpz_t poly_result;
        mpz_init(poly_result);
        (*p)(poly_result, k);
        
        mpz_t num;
        mpz_init(num);
        
        mpz_t exponent;
        mpz_init_set(exponent, k);
        mpz_mul_si(exponent, exponent, c);
        mpz_mul_si(exponent, exponent, -1);
        mpz_add_ui(exponent, exponent, d);
        
        modular_pow_gmp(num, base, exponent, poly_result);
        mpf_t num_float;
        mpf_init(num_float);
        mpf_set_z(num_float, num);
        mpz_clear(num);
        mpz_clear(exponent);
        
        mpf_t denom;
        mpf_init_set_d(denom, mpz_get_d(poly_result));
        
        mpz_clear(poly_result);
        
        mpf_t quotient;
        mpf_init(quotient);
        mpf_div(quotient, num_float, denom);        
        mpf_clear(num_float);
        mpf_clear(denom);
        
        mpf_add(sum, sum, quotient);
        mpf_clear(quotient);
        
        mod_one_gmp(sum, sum);
        
        mpz_add_ui(k, k, 1);
    }
    mpz_clear(k);
        
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
void compute_bbp_second_sum_gmp(mpf_t sum, int d, int base, int c, void (*p)(mpz_t, mpz_t)) 
{
    mpf_set_d(sum, 0.0);

    mpz_t k;
    mpz_init_set_si(k, floor((double) d / (double) c) + 1);

    mpf_t prev_sum;
    mpf_init(prev_sum);
    mpf_set(prev_sum, sum);
    
    mpf_t base_gmp;
    mpf_init(base_gmp);
    mpf_set_si(base_gmp, base);

    double d_diff = 0.0;
    do
    {
        mpf_set(prev_sum, sum);
        mpz_t poly_result;
        mpz_init(poly_result);
        (*p)(poly_result, k);

        mpf_t num;
        mpf_init(num);
                
        mpz_t exponent;
        mpz_init_set(exponent, k);
        mpz_mul_si(exponent, exponent, c);
        mpz_mul_si(exponent, exponent, -1);
        mpz_add_ui(exponent, exponent, d);
        signed long int exp = mpz_get_si(exponent);
        unsigned long int neg_exp = -1 * exp;

        mpf_pow_ui(num, base_gmp, neg_exp);
        mpf_ui_div(num, 1, num);
        mpz_clear(exponent);
        
        mpf_t denom;
        mpf_init_set_d(denom, mpz_get_d(poly_result));
        mpz_clear(poly_result);
       
        mpf_t quotient;
        mpf_init(quotient);
        mpf_div(quotient, num, denom);        
        mpf_clear(num);
        mpf_clear(denom);
        
        mpf_add(sum, sum, quotient);
        mpf_clear(quotient);

        mpz_add_ui(k, k, 1);

        mpf_t diff;
        mpf_init(diff);
        mpf_sub(diff, prev_sum, sum);
        
        d_diff = mpf_get_d(diff);
        d_diff = fabs(d_diff);
        mpf_clear(diff);
    }
    while (d_diff > 0.00000001);
    
    mpz_clear(k);    
    mpf_clear(base_gmp);
    mpf_clear(prev_sum);
}


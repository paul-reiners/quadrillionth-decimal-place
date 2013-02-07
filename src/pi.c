/****************************************************************************
 * pi.c
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * An implementation of the Bailey–Borwein–Plouffe (BBP) formula for pi in
 * hexadecimal.
 ***************************************************************************/

#include "../include/pi.h"
#include "../include/bbp.h"
#include "../include/aux.h"

/*
 * Function:  pi_hex
 * --------------------
 * Computes the pi hex BBP formula.
 * It is the responsibility of the calling function to free the returned string.
 *
 *  d: hex digit to be calculated
 *  num_places: how many hex places to calculate
 *
 *  returns: the dth hex digit of pi (plus num_places - 1 more places)
 */
char* pi_hex(long long int d, int num_places)
{
    int base = 16;
    long double sum = pi(d);

    return convert_floating_decimal_to_base(sum, num_places, base);
}

/*
 * Function:  pi
 * --------------------
 * Computes the pi hex BBP formula.
 * It is the responsibility of the calling function to free the returned string.
 *
 *  d: hex digit to be calculated
 *
 *  returns: pi starting at digit d
 */
long double pi(long long int d)
{
    long double sum =
        4 * compute_pi_sum1(d)
        - 2 * compute_pi_sum2(d)
        - compute_pi_sum3(d)
        - compute_pi_sum4(d);
    long double frac_part = mod_one(sum);

    return frac_part;
}

/*
 * Function:  compute_pi_sum1
 * --------------------
 * Computes the first term of the pi hex BBP formula.
 *
 *  d: hex digit to be calculated
 *
 *  returns: the first term of the pi hex BBP formula
 */
long double compute_pi_sum1(long long int d)
{
    int base = 16;
    int c = 1;
    void (*p)(mpz_t, mpz_t) = &pi_hex_p1;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

/*
 * Function:  compute_pi_sum2
 * --------------------
 * Computes the second term of the pi hex BBP formula.
 *
 *  d: hex digit to be calculated
 *
 *  returns: the second term of the pi hex BBP formula
 */
long double compute_pi_sum2(long long int d)
{
    int base = 16;
    int c = 1;
    void (*p)(mpz_t, mpz_t) = &pi_hex_p2;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

/*
 * Function:  compute_pi_sum3
 * --------------------
 * Computes the third term of the pi hex BBP formula.
 *
 *  d: hex digit to be calculated
 *
 *  returns: the third term of the pi hex BBP formula
 */
long double compute_pi_sum3(long long int d)
{
    int base = 16;
    int c = 1;
    void (*p)(mpz_t, mpz_t) = &pi_hex_p3;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

/*
 * Function:  compute_pi_sum4
 * --------------------
 * Computes the fourth term of the pi hex BBP formula.
 *
 *  d: hex digit to be calculated
 *
 *  returns: the fourth term of the pi hex BBP formula
 */
long double compute_pi_sum4(long long int d)
{
    int base = 16;
    int c = 1;
    void (*p)(mpz_t, mpz_t) = &pi_hex_p4;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

/*
 * Function:  pi_hex_p1
 * --------------------
 * The first polynomial p1 used for the pi BBP formula
 *
 *  k: input to the polynomial p1
 *
 *  returns: p1(k)
 */
void pi_hex_p1(mpz_t rop, mpz_t k)
{
    mpz_set(rop, k);
    mpz_mul_si(rop, rop, 8);
    mpz_add_ui(rop, rop, 1);
}

/*
 * Function:  pi_hex_p2
 * --------------------
 * The second polynomial p2 used for the pi BBP formula
 *
 *  k: input to the polynomial p2
 *
 *  returns: p2(k)
 */
void pi_hex_p2(mpz_t rop, mpz_t k)
{
    mpz_set(rop, k);
    mpz_mul_si(rop, rop, 8);
    mpz_add_ui(rop, rop, 4);
}

/*
 * Function:  pi_hex_p3
 * --------------------
 * The third polynomial p3 used for the pi BBP formula
 *
 *  k: input to the polynomial p3
 *
 *  returns: p3(k)
 */
void pi_hex_p3(mpz_t rop, mpz_t k)
{
    mpz_set(rop, k);
    mpz_mul_si(rop, rop, 8);
    mpz_add_ui(rop, rop, 5);
}

/*
 * Function:  pi_hex_p4
 * --------------------
 * The fourth polynomial p4 used for the pi BBP formula
 *
 *  k: input to the polynomial p4
 *
 *  returns: p4(k)
 */
void pi_hex_p4(mpz_t rop, mpz_t k)
{
    mpz_set(rop, k);
    mpz_mul_si(rop, rop, 8);
    mpz_add_ui(rop, rop, 6);
}


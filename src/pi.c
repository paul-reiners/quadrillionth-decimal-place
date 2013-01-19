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

char* pi_hex(int first_place, int num_places)
{
    int base = 16;
    long double sum =
        4 * compute_pi_sum1(first_place)
        - 2 * compute_pi_sum2(first_place)
        - compute_pi_sum3(first_place)
        - compute_pi_sum4(first_place);

    return convert_floating_decimal_to_base(sum, num_places, base);
}

long double compute_pi_sum1(int d)
{
    int base = 16;
    int c = 1;
    int (*p)(int) = &pi_hex_p1;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

long double compute_pi_sum2(int d)
{
    int base = 16;
    int c = 1;
    int (*p)(int) = &pi_hex_p2;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

long double compute_pi_sum3(int d)
{
    int base = 16;
    int c = 1;
    int (*p)(int) = &pi_hex_p3;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

long double compute_pi_sum4(int d)
{
    int base = 16;
    int c = 1;
    int (*p)(int) = &pi_hex_p4;
    long double result = compute_bbp(d, base, c, p, true);

    return result;
}

int pi_hex_p1(int k)
{
    return 8 * k + 1;
}

int pi_hex_p2(int k)
{
    return 8 * k + 4;
}

int pi_hex_p3(int k)
{
    return 8 * k + 5;
}

int pi_hex_p4(int k)
{
    return 8 * k + 6;
}


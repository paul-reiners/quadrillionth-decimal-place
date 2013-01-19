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

long double compute_bbp(int digit, int base, int c, int (*p)(int), bool start_at_0)
{
    int d = digit - 1;
    long double sum
        = mod_one(
                compute_bbp_first_sum(d, base, c, p, start_at_0)
                + compute_bbp_second_sum(d, base, c, p));

    return sum;
}

long double compute_bbp_first_sum(int n, int base, int c, int (*p)(int), bool start_at_0)
{
    long double sum = 0.0;
    int k_start = start_at_0 ? 0 : 1;
    for (int k = k_start; k <= floor(n / c); k++)
    {
        int poly_result = (*p)(k);
        int num = modular_pow(base, n - c * k, poly_result);
        int denom = poly_result;
        sum += (long double) num / (long double) denom;
        sum = mod_one(sum);
    }

    return mod_one(sum);
}

long double compute_bbp_second_sum(int n, int base, int c, int (*p)(int))
{
    long double sum = 0.0;
    int k = floor(n / c) + 1;
    long double prev_sum = sum;
    long double machEps = calculate_machine_epsilon();
    do
    {
        prev_sum = sum;
        int poly_result = (*p)(k);
        long double num = pow(base, n - c * k);
        int denom = poly_result;
        sum += num / (long double) denom;

        k++;
    }
    while (fabs(sum - prev_sum) > machEps);

    return sum;
}


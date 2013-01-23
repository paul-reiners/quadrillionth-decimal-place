/****************************************************************************
 * bbp.h
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * An implementation of the generic Bailey–Borwein–Plouffe (BBP) formula.
 ***************************************************************************/

#ifndef BBP_H
#define BBP_H

#include <stdbool.h>

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
long double compute_bbp_first_sum(int d, int base, int c, int (*p)(int), bool start_at_0);

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
long double compute_bbp_first_sum_gmp(int d, int base, int c, int (*p)(int), bool start_at_0);

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
long double compute_bbp_second_sum(int d, int base, int c, int (*p)(int));

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
long double compute_bbp(int digit, int base, int c, int (*p)(int), bool start_at_0);

#endif // BBP_H


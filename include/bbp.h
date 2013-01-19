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

long double compute_bbp_first_sum(int n, int base, int c, int (*p)(int), bool start_at_0);
long double compute_bbp_second_sum(int n, int base, int c, int (*p)(int));
long double compute_bbp(int n, int base, int c, int (*p)(int), bool start_at_0);

#endif // BBP_H


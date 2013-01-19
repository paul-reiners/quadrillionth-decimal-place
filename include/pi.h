/****************************************************************************
 * pi.h
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * An implementation of the Bailey–Borwein–Plouffe (BBP) formula for pi in 
 * hexadecimal.
 ***************************************************************************/
 
#ifndef PI_H
#define PI_H

char* pi_hex(int first_place, int num_places);
int pi_hex_p1(int k);
int pi_hex_p2(int k);
int pi_hex_p3(int k);
int pi_hex_p4(int k);
long double compute_pi_sum1(int first_place);
long double compute_pi_sum2(int first_place);
long double compute_pi_sum3(int first_place);
long double compute_pi_sum4(int first_place);

#endif // PI_H


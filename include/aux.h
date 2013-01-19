/****************************************************************************
 * aux.h
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * Contains auxiliary routines that are not specific to the 
 * Bailey–Borwein–Plouffe formula.
 ***************************************************************************/

#ifndef AUX_H
#define AUX_H

/*
 * Function:  modular_pow 
 * --------------------
 * Computes modular exponentiation in an efficient and precise manner.
 *
 * Basically a wrapper method for the GMP method mpz_set_ui.
 * Based on
 *      http://rosettacode.org/wiki/Modular_exponentiation#C
 *
 *  b: base
 *  exponent: the exponent to be raised to
 *  modulus: the modulus to be used
 *
 *  returns: (b ^ exponent) % modulus
 */
unsigned long int modular_pow(unsigned long int b, unsigned long int exponent, unsigned long int modulus);

long double mod_one(long double x);
char* convert_floating_decimal_to_hex(long double x, int places);
char* convert_floating_decimal_to_base(long double x, int places, int base);
long double calculate_machine_epsilon(void);
char* format_elapsed_time(int elapsed_seconds);

#endif // AUX_H


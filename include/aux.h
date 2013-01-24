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

#include<stdbool.h>

#include <gmp.h>

/*
 * Function:  modular_pow_gmp 
 * --------------------
 * Computes modular exponentiation in an efficient and precise manner.
 *
 * Basically a wrapper method for the GMP method mpz_powm.
 * Based on
 *      http://rosettacode.org/wiki/Modular_exponentiation#C
 *
 *  b: base
 *  exponent: the exponent to be raised to
 *  modulus: the modulus to be used
 *
 *  returns: (b ^ exponent) % modulus
 */
void modular_pow_gmp(mpz_t rop, unsigned long long int b, unsigned long long int exponent, unsigned long long int modulus);

/*
 * Function:  mod_one 
 * --------------------
 * Drops the integer part of a real number.  Mathematicians use the term "mod 
 * one", which is not the same as n % 1.
 *
 *  x: a real number
 *
 *  returns: the fractional part of x
 */
long double mod_one(long double x);

/*
 * Function:  mod_one_gmp 
 * --------------------
 * Drops the integer part of a real number.  Mathematicians use the term "mod 
 * one", which is not the same as n % 1.
 *
 *  x: a real number
 *
 *  returns: the fractional part of x
 */
void mod_one_gmp(mpf_t rop, mpf_t x);

/*
 * Function:  convert_floating_decimal_to_hex 
 * --------------------
 * Converts a floating-point number to a hexadecimal representation.  The string
 * that is returned must be freed.
 *
 *  x: a floating-point number < 1.0
 *  places: the number of places to the right of the decimal point to represent 
 *
 *  returns: a hexadecimal representation of x
 */
char* convert_floating_decimal_to_hex(long double x, int places);

/*
 * Function:  convert_floating_decimal_to_base
 * --------------------
 * Converts a floating-point number to a representation in a specified base.  
 * The string that is returned must be freed.
 *
 * Based on algorithm given in "Math Forum - Ask Dr. Math"
 *     http://mathforum.org/library/drmath/view/64392.html
 *
 *  x: a floating-point number < 1.0
 *  places: the number of places to the right of the decimal point to represent
 *  base: the base to be converted to 
 *
 *  returns: a representation of x in the specified base
 */
char* convert_floating_decimal_to_base(long double x, int places, int base);

/*
 * Function:  format_elapsed_time
 * --------------------
 * Formats seconds as HH:MM:SS.
 * Returned string must be freed.
 *
 *  elapsed_seconds: number of seconds
 *
 *  returns: a string in the format HH:MM:SS
 */
char* format_elapsed_time(int elapsed_seconds);

/*
 * Function:  is_integer
 * --------------------
 * Checks whether a string represents a decimal integer.
 *
 *  number_str: a string that may or may not represent an integer
 *
 *  returns: true iff number_str represents an integer
 */
bool is_integer(char* number_str);

#endif // AUX_H


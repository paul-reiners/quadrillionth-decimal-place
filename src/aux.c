/****************************************************************************
 * aux.c
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * Contains auxiliary routines that are not specific to the
 * Bailey–Borwein–Plouffe formula.
 ***************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <gmp.h>

#include "../include/aux.h"

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
unsigned long int modular_pow(unsigned long int b, unsigned long int exponent, unsigned long int modulus)
{
    mpz_t rop;
    mpz_init(rop);

    mpz_t base;
    mpz_init(base);
    mpz_set_ui(base, b);

    mpz_t exp;
    mpz_init(exp);
    mpz_set_ui(exp, exponent);

    mpz_t mod;
    mpz_init(mod);
    mpz_set_ui(mod, modulus);

    mpz_powm(rop, base, exp, mod);

    unsigned long int result = mpz_get_ui(rop);

    mpz_clear(exp);
    mpz_clear(base);
    mpz_clear(mod);
    mpz_clear(rop);

    return result;
}

/*
 * Function:  calculate_machine_epsilon
 * --------------------
 * Calculates the smallest floating-point difference possible on the machine
 * that the program is being run on.
 *
 * This code was not written by me.  It is from:
 *      http://en.wikipedia.org/wiki/Machine_epsilon#Approximation_using_C
 *
 *  returns: the smallest floating-point difference that can be represented on
 *  the machine the program is running on
 */
long double calculate_machine_epsilon(void)
{
    long double machEps = 1.0;

    do
    {
        machEps /= 2.0;
        // If next epsilon yields 1, then break, because current
        // epsilon is the machine epsilon.
    }
    while ((long double)(1.0 + (machEps / 2.0)) != 1.0);

    return machEps;
}

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
long double mod_one(long double x)
{
    return x - floor(x);
}

/*
 * Function:  get_int_part
 * --------------------
 * Returns the part of a number to the left of the decimal point.
 *
 *  x: a real number
 *
 *  returns: the integer part of x
 */
int get_int_part(long double x)
{
    return (int) x;
}

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
char* convert_floating_decimal_to_hex(long double x, int places)
{
    return convert_floating_decimal_to_base(x, places, 16);
}

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
char* convert_floating_decimal_to_base(long double x, int places, int base)
{
    char* result = malloc(places * sizeof(char) + 1);
    char* pos = result;
    long double frac_part = x;
    for (int i = 0; i < places; i++)
    {
        frac_part = mod_one(frac_part);
        frac_part *= base;
        int whole_part = get_int_part(frac_part);
        if (0 <= whole_part && whole_part <= 9)
        {
            *pos = (char)('0' + whole_part);
        }
        else
        {
            *pos = (char)('A' + (whole_part - 10));
        }
        pos++;
    }
    *pos = '\0';

    return result;
}

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
char* format_elapsed_time(int elapsed_seconds)
{
    int left = elapsed_seconds;
    int hours = left / (60 * 60);
    left -= (60 * 60) * hours;
    int minutes = left / 60;
    left = left -= minutes * 60;
    int seconds = left;
    char* formatted_time = malloc(sizeof(char) * 9);
    sprintf(formatted_time, "%02d:%02d:%02d", hours, minutes, seconds);

    return formatted_time;
}

/*
 * Function:  is_integer
 * --------------------
 * Checks whether a string represents a decimal integer.
 *
 *  number_str: a string that may or may not represent an integer
 *
 *  returns: true iff number_str represents an integer
 */
bool is_integer(char* number_str)
{
    for (int i = 0; i < strlen(number_str); i++)
    {
        char c = number_str[i];
        if (!('0' <= c && c <= '9'))
        {
            return false;
        }
    }

    return true;
}


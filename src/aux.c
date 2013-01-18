#include <math.h>
#include <stdlib.h>

#include <gmp.h>

#include "../include/aux.h"

/**
 * Basically a wrapper method for the GMP method mpz_set_ui.
 * Based on
 *      http://rosettacode.org/wiki/Modular_exponentiation#C
 */
unsigned long int modular_pow(unsigned long int b, unsigned long int exponent, unsigned long int modulus) {
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

long double calculate_machine_epsilon(void) {
    // From http://en.wikipedia.org/wiki/Machine_epsilon#Approximation_using_C

    long double machEps = 1.0;
 
    do {
       machEps /= 2.0;
       // If next epsilon yields 1, then break, because current
       // epsilon is the machine epsilon.
    }
    while ((long double)(1.0 + (machEps/2.0)) != 1.0);
 
    return machEps;
}

long double mod_one(long double x) {
    return x - floor(x);
}

int get_int_part(long double x) {
    return (int) x;
}

// Use  to 
char* convert_floating_decimal_to_hex(long double x, int places) {
    return convert_floating_decimal_to_base(x, places, 16);
}

/**
 * Convert long double to other bases.
 * Based on algorithm given in "Math Forum - Ask Dr. Math"
 *     http://mathforum.org/library/drmath/view/64392.html
 */
char* convert_floating_decimal_to_base(long double x, int places, int base) {
    char* result = malloc(places * sizeof(char) + 1);
    char* pos = result;
    long double frac_part = x;
    for (int i = 0; i < places; i++) {
        frac_part = mod_one(frac_part);
        frac_part *= base;
        int whole_part = get_int_part(frac_part);
        if (0 <= whole_part && whole_part <= 9) {
            *pos = (char) ('0' + whole_part);
        } else {
            *pos = (char) ('A' + (whole_part - 10));
        }
        pos++;
    }
    *pos = '\0';
    
    return result;
}


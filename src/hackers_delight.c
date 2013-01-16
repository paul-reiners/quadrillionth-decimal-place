#include <gmp.h>

int pop(unsigned x) {
    // From "Hacker's Delight" (page 82)
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}


/**
 *  Greatest power of 2 less than or equal to x, branch free.
 *  From "Hacker's Delight".
 */
unsigned flp2(unsigned x) {
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x - (x >> 1);
}

/**
 *  Computing x^n mod k by binary decomposition of n.
 *  Adapted from method in "Hacker's Delight".
 */
int modular_pow_2(int x, int n, int k) {
    int c = 1;
    for (int i = 0; i < n; i++) {
        c = (c * x) % k;
    }
    
    return c;
}

/**
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


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
int modular_pow(int x, int n, int k) {
    int c = 1;
    for (int i = 0; i < n; i++) {
        c = (c * x) % k;
    }
    
    return c;
}

/**
 *  Computing base^exponent mod modulus by binary decomposition of exponent.
 *  Based on pseudocode in "Applied Cryptography" by Bruce Schneier.
 */
int modular_pow_2(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
           result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}


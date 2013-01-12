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
int iexp(int x, unsigned n, unsigned k) {
    int p, y;
    
    y = 1;
    p = x;
    while (1) {
        if (n & 1) y = (p*y) % k;
        n = n >> 1;
        if (n == 0) return y;
        p = (p * p) % k;
    }
}


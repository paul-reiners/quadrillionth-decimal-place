int fast_exp(int b, int n, int c);
unsigned flp2(unsigned x);

int main(int argc, char* argv[]) {
    return 0;
}

/**
 * Computes r = b^n mod c
 */
int fast_exp(int b, unsigned n, int c) {
    unsigned t = flp2(n);
    unsigned r = 1;
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

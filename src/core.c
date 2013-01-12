#include <math.h>
#include <stdlib.h>

#include "../include/hackers_delight.h"
#include "../include/core.h"

double decimal_reciprocal(int n, int pos) {
    return (double) iexp(10, pos - 1, n) / (double) n;
}

char* compute_3_4(int n, int base, int c, int (*p)(int), int places) {
    double sum = compute_3_4_first_sum(n, base, c, p) + compute_3_4_second_sum(n, base, c, p);
    
    return convert_floating_decimal_to_hex(sum, places);
}

double compute_3_4_first_sum(int n, int base, int c, int (*p)(int)) {
    double sum = 0.0;
    for (int k = 0; k <= n / c; k++) {
        int poly_result = (*p)(k);
        int num = iexp(base, n - c * k, poly_result);
        int denom = poly_result;
        sum += (double) num / (double) denom;
        sum = mod_one(sum);
    }
    
    return sum;
}

double compute_3_4_second_sum(int n, int base, int c, int (*p)(int)) {
    double sum = 0.0;
    int k = n / c + 1;
    double prev_sum = sum;
    do {
        prev_sum = sum;
        int poly_result = (*p)(k);
        double num = pow(base, n - c * k);
        int denom = poly_result;
        sum += num / (double) denom;
        sum = mod_one(sum);
        
        k++;
    } while (fabs(sum - prev_sum) > 0.00000001);
    
    return sum;
}

int mod_one(double x) {
    return (int) floor(x);
}

// Use http://mathforum.org/library/drmath/view/64392.html to convert double to other bases.
char* convert_floating_decimal_to_hex(double x, int places) {
    char* result = malloc(places * sizeof(char));
    char* pos = result;
    double frac_part = mod_one(x);
    for (int i = 0; i < places; i++) {
        frac_part *= 16;
        int whole_part = mod_one(frac_part);
        if (0 <= whole_part && whole_part <= 9) {
            *pos = (char) ('0' + whole_part);
        } else {
            *pos = (char) ('A' + (whole_part - 10));
        }
        pos++;
    }
    
    return result;
}



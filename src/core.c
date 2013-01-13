#include <math.h>
#include <stdlib.h>

#include "../include/hackers_delight.h"
#include "../include/core.h"

double decimal_reciprocal(int n, int pos) {
    return (double) iexp(10, pos - 1, n) / (double) n;
}

double compute_3_4(int n, int base, int c, int (*p)(int), bool start_at_0) {
    double sum = compute_3_4_first_sum(n, base, c, p, start_at_0) + compute_3_4_second_sum(n, base, c, p);
    
    return sum;
}

char* compute_3_4_to_base(int n, int base, int c, int (*p)(int), int places, bool start_at_0) {
    double sum = compute_3_4(n, base, c, p, start_at_0);
    
    return convert_floating_decimal_to_base(sum, places, base);
}

double compute_3_4_first_sum(int n, int base, int c, int (*p)(int), bool start_at_0) {
    double sum = 0.0;
    int k_start = start_at_0 ? 0 : 1;
    for (int k = k_start; k <= floor(n / c); k++) {
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
    int k = floor(n / c) + 1;
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

double mod_one(double x) {
    return x - floor(x);
}

int get_int_part(double x) {
    return (int) x;
}

// Use  to 
char* convert_floating_decimal_to_hex(double x, int places) {
    return convert_floating_decimal_to_base(x, places, 16);
}

/**
 * Convert double to other bases.
 * Based on algorithm given in "Math Forum - Ask Dr. Math"
 *     http://mathforum.org/library/drmath/view/64392.html
 */
char* convert_floating_decimal_to_base(double x, int places, int base) {
    char* result = malloc(places * sizeof(char) + 1);
    char* pos = result;
    double frac_part = x;
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


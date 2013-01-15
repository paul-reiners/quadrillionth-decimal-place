#include <math.h>
#include <stdlib.h>

#include "../include/hackers_delight.h"
#include "../include/core.h"

long double decimal_reciprocal(int n, int pos) {
    return (long double) modular_pow(10, pos - 1, n) / (long double) n;
}

long double compute_3_4(int n, int base, int c, int (*p)(int), bool start_at_0) {
    long double sum = mod_one(compute_3_4_first_sum(n, base, c, p, start_at_0) + compute_3_4_second_sum(n, base, c, p));
    
    return sum;
}

long double compute_s(int d, int j) {
    long double sum = mod_one(compute_s_first_sum(d, j) + mod_one(compute_s_second_sum(d, j)));
    
    return sum;
}

char* compute_3_4_to_base(int n, int base, int c, int (*p)(int), int places, bool start_at_0) {
    long double sum = compute_3_4(n, base, c, p, start_at_0);
    
    return convert_floating_decimal_to_base(sum, places, base);
}

long double compute_3_4_first_sum(int n, int base, int c, int (*p)(int), bool start_at_0) {
    long double sum = 0.0;
    int k_start = start_at_0 ? 0 : 1;
    for (int k = k_start; k <= floor(n / c); k++) {
        int poly_result = (*p)(k);
        int num = modular_pow(base, n - c * k, poly_result);
        int denom = poly_result;
        sum += (long double) num / (long double) denom;
    }
    
    return mod_one(sum);
}

long double compute_s_first_sum(int d, int j) {
    long double sum = 0.0;
    for (int k = 0; k <= d; k++) {
        int poly_result = 8 * k + j;
        int num = modular_pow(16, d - k, poly_result);
        int denom = poly_result;
        sum += (long double) num / (long double) denom;
        sum = mod_one(sum);
    }
    
    return sum;
}

long double compute_s_second_sum(int d, int j) {
    long double sum = 0.0;
    int k = d + 1;
    long double prev_sum = sum;
    long double machEps = calculate_machine_epsilon();
    do {
        prev_sum = sum;
        int poly_result = 8 * k + j;
        long double num = pow(16.0, (long double) (d - k));
        int denom = poly_result;
        sum += num / (long double) denom;
        
        k++;
    } while (fabs(sum - prev_sum) > machEps);
    
    return sum;
}

long double compute_3_4_second_sum(int n, int base, int c, int (*p)(int)) {
    long double sum = 0.0;
    int k = floor(n / c) + 1;
    long double prev_sum = sum;
    long double machEps = calculate_machine_epsilon();
    do {
        prev_sum = sum;
        int poly_result = (*p)(k);
        long double num = pow(base, n - c * k);
        int denom = poly_result;
        sum += num / (long double) denom;
        
        k++;
    } while (fabs(sum - prev_sum) > machEps);
    
    return sum;
}

long double calculate_machine_epsilon(void) {
    // From http://en.wikipedia.org/wiki/Machine_epsilon#Approximation_using_C
    // Calculated Machine float epsilon:       1.19209E-07
    // Calculated Machine double epsilon:      2.22045E-16
    // Calculated Machine long double epsilon: 1.084202e-19

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


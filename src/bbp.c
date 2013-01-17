#include <math.h>

#include "../include/aux.h"
#include "../include/bbp.h"

long double compute_3_4(int n, int base, int c, int (*p)(int), bool start_at_0) {
    long double sum = mod_one(compute_3_4_first_sum(n, base, c, p, start_at_0) + compute_3_4_second_sum(n, base, c, p));
    
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
        sum = mod_one(sum);
    }
    
    return mod_one(sum);
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


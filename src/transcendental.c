#include "../include/transcendental.h"
#include "../include/core.h"

char* log_2_binary(int first_place, int num_places) {
    int base = 2;
    int c = 1;
    int (*p)(int) = &log_2_binary_p;
    char* result = compute_3_4_to_base(first_place, base, c, p, num_places, false);
    
    return result;
}

int log_2_binary_p(int k) {
    return k;
}

char* pi_hex(int first_place, int num_places) {
    int base = 16;
    long double sum = 
        4 * compute_pi_sum1(first_place - 1) 
            - 2 * compute_pi_sum2(first_place - 1) 
            - compute_pi_sum3(first_place - 1) 
            - compute_pi_sum4(first_place - 1);
            
    return convert_floating_decimal_to_base(sum, num_places, base);
}

long double compute_pi_sum1(int d) {
    long double result = compute_s(d, 1);
    
    return result;
}

long double compute_pi_sum2(int d) {
    long double result = compute_s(d, 4);
    
    return result;
}

long double compute_pi_sum3(int d) {
    long double result = compute_s(d, 5);
    
    return result;
}

long double compute_pi_sum4(int d) {
    long double result = compute_s(d, 6);
    
    return result;
}

int pi_hex_p1(int k) {
    return 8 * k + 1;
}

int pi_hex_p2(int k) {
    return 8 * k + 4;
}

int pi_hex_p3(int k) {
    return 8 * k + 5;
}

int pi_hex_p4(int k) {
    return 8 * k + 6;
}


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
    double sum = 
        4 * compute_pi_sum1(first_place, num_places) 
            - 2 * compute_pi_sum2(first_place, num_places) 
            - compute_pi_sum3(first_place, num_places) 
            - compute_pi_sum4(first_place, num_places);
            
    return convert_floating_decimal_to_base(sum, num_places, base);
}

double compute_pi_sum1(int first_place, int num_places) {
    double result = compute_3_4(first_place, 16, 1, &pi_hex_p1, true);
    
    return result;
}

double compute_pi_sum2(int first_place, int num_places) {
    double result = compute_3_4(first_place, 16, 1, &pi_hex_p2, true);
    
    return result;
}

double compute_pi_sum3(int first_place, int num_places) {
    double result = compute_3_4(first_place, 16, 1, &pi_hex_p3, true);
    
    return result;
}

double compute_pi_sum4(int first_place, int num_places) {
    double result = compute_3_4(first_place, 16, 1, &pi_hex_p4, true);
    
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


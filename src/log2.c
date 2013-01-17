#include "../include/log2.h"
#include "../include/bbp.h"

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


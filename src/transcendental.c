#include "../include/poly.h"
#include "../include/core.h"

char* log_2_binary(int first_place, int num_places) {
    int base = 2;
    int c = 1;
    int (*p)(int) = &log_2_binary_p;
    char* result = compute_3_4(first_place, base, c, p, num_places);
    
    return result;
}


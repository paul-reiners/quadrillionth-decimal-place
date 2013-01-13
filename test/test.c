#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"
#include "../include/hackers_delight.h"
#include "../include/core.h"
#include "../include/transcendental.h"

int test(void) {
    int fail_count = 0;
    fail_count += test_iexp();
    fail_count += test_convert_floating_decimal_to_hex();
    fail_count += test_convert_log_of_2_to_binary();
    fail_count += test_log_2_binary();
    fail_count += test_pi_hex();
    
    return fail_count;
}

int test_log_2_binary(void) {
    // log(2) base 2 = 0.101100010111...
    char* expected = "101100010111";
    int n = 0;
    int places = 12;
    char* actual = log_2_binary(n, places);
    int ret_val;
    if (strcmp(expected, actual) == 0) {
        printf("test_log_2_binary succeeded.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 0;
    } else {
        printf("test_log_2_binary failed.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 1;
    }
    
    return ret_val;
}

int test_pi_hex(void) {
    // pi base 16 = 3.243F6A88...
    char* expected = "243F6A88";
    int n = 0;
    int places = 8;
    char* actual = pi_hex(n, places);
    int ret_val;
    if (strcmp(expected, actual) == 0) {
        printf("test_pi_hex succeeded.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 0;
    } else {
        printf("test_pi_hex failed.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 1;
    }
    
    return ret_val;
}


int test_convert_log_of_2_to_binary(void) {
    // log(2) base 2 = 0.101100010111...
    char* expected  = "101100010111";
    int ret_val;
    char* actual = convert_floating_decimal_to_base(log(2.0), 12, 2);
    if (strcmp(expected, actual) == 0) {
        printf("test_convert_log_of_2_to_binary succeeded.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 0;
    } else {
        printf("test_convert_log_of_2_to_binary failed.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 1;
    }
    
    free(actual);
    
    return ret_val;
}


int test_iexp(void) {
    int x = 10;
    unsigned n = 999;
    unsigned k = 257;
    int expected =  96;
    int actual = iexp(x, n, k);
    if (expected == actual) {
        printf("test_iexp succeeded.\n");
        
        return 0;
    } else {
        printf("test_iexp failed.\n");
        printf("\texpected: %d; actual: %d.\n", expected, actual);
        
        return 1;
    }
}

int test_convert_floating_decimal_to_hex(void) {
    char* expected  = "1C71C71C7";
    int ret_val;
    char* actual = convert_floating_decimal_to_hex(1.0 / 9.0, 9);
    if (strcmp(expected, actual) == 0) {
        printf("test_convert_floating_decimal_to_hex succeeded.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 0;
    } else {
        printf("test_convert_floating_decimal_to_hex failed.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 1;
    }
    
    free(actual);
    
    return ret_val;
}


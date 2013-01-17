#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

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
    fail_count += test_pi_hex_0_8();
    fail_count += test_pi_hex_1_8();
    fail_count += test_pi_hex_2_8();
    fail_count += test_compute_pi_sum1();
    fail_count += test_compute_pi_sum2();
    fail_count += test_pi_hex_10_n();
    printf("\n");
    
    return fail_count;
}

int test_compute_pi_sum1(void) {
    long double actual = compute_pi_sum1(1000000);
    long double expected  = 0.18103953;
    long double tolerance = 0.00000001;
    long double delta = fabs(actual - expected);
    if (delta <= tolerance) {
        printf("test_compute_pi_sum1 passed\n");
        
        return 0;
    } else {
        printf("test_compute_pi_sum1 failed\n");
        printf("\texpected: %Lf; actual: %Lf.\n", expected, actual);
        printf("\tdifference was: %Lf.\n", delta);
        
        return 1;
    } 
}

int test_compute_pi_sum2(void) {
    long double actual = compute_pi_sum2(1000000);
    long double expected  = 0.77606554;
    long double tolerance = 0.00000001;
    if (fabs(actual - expected) <= tolerance) {
        printf("test_compute_pi_sum2 passed\n");
        
        return 0;
    } else {
        printf("test_compute_pi_sum2 failed\n");
        printf("\texpected: \"%Lf\"; actual: \"%Lf\".\n", expected, actual);
        
        return 1;
    } 
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

int test_pi_hex_0_8(void) {
    // pi base 16 = 3.243F6A88...
    char* expected = "243F6A88";
    int n = 1;
    int places = strlen(expected);
    
    return test_pi_hex_n_places(expected, n, places);
}

int test_pi_hex_10_n(void) {
    char* expecteds[] = { "26C65E52CB459", "17AF5863EFED", "ECB840E2192" };
    int ns[] =  { 1000000, 10000000, 100000000 };
    int error_count = 0;
    for (int i = 0; i < sizeof(ns) / sizeof(int); i++) {
        char* expected = expecteds[i];
        int places = strlen(expected);
        int n = ns[i];
        error_count += test_pi_hex_n_places(expected, n, places);
    }
    
    return error_count;
}

int test_pi_hex_n_places(char* expected, int n, int places) {
    time_t t1,t2;
    (void) time(&t1);
	char* actual = pi_hex(n, places);
    (void) time(&t2);
    
    int ret_val;
    if (strcmp(expected, actual) == 0) {
        printf("test_pi_hex_n_places(%d, %d) succeeded.\n", n, places);
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        int left = (int) (t2-t1);
        int hours = left / (60 * 60);
        left -= (60 * 60) * hours;
        int minutes = left / 60;
        left = left -= minutes * 60;
        int seconds = left;
		printf("\tTime to compute = %02d:%02d:%02d.\n", hours, minutes, seconds);
        
        ret_val = 0;
    } else {
        printf("test_pi_hex_n_places(%d, %d) failed.\n", n, places);
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
        ret_val = 1;
    }
    
    return ret_val;
}

int test_pi_hex_1_8(void) {
    // pi base 16 = 3.243F6A888...
    char* expected = "43F6A888";
    int n = 2;
    int places = strlen(expected);
    
    return test_pi_hex_n_places(expected, n, places);
}

int test_pi_hex_2_8(void) {
    // pi base 16 = 3.243F6A8885...
    char* expected = "3F6A8885";
    int n = 3;
    int places = strlen(expected);
    
    return test_pi_hex_n_places(expected, n, places);
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
    int error_count = 0;
    
    int x = 10;
    unsigned n = 999;
    unsigned k = 257;
    int expected =  96;
    int actual = modular_pow(x, n, k);
    if (expected != actual) {
        printf("test_iexp failed.\n");
        printf("\texpected: %d; actual: %d.\n", expected, actual);
        
        error_count++;
    }
    
    x = 4;
    n = 13;
    k = 497;
    expected =  445;
    actual = modular_pow(x, n, k);
    if (expected != actual) {
        printf("test_iexp failed.\n");
        printf("\texpected: %d; actual: %d.\n", expected, actual);
        
        error_count++;
    }
    
    if (error_count == 0) {
        printf("test_iexp passed.\n");
    }
    
    return error_count;
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


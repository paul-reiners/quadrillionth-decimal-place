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
    fail_count += test_pi_hex_0_8();
    fail_count += test_pi_hex_1_8();
    fail_count += test_pi_hex_2_8();
    fail_count += test_pi_hex_1000000();
    
    return fail_count;
}

int test_big_file(void) {
    // char *fileName = "./test/pi.txt";
    // char* pi = readFile(fileName);
    
    return 0;
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
    int n = 0;
    int places = strlen(expected);
    
    return test_pi_hex_n_places(expected, n, places);
}

int test_pi_hex_1000000(void) {
    char* expected = "26C65E52CB4593";
    int n = 1000000;
    int places = strlen(expected);
    
    return test_pi_hex_n_places(expected, n, places);
}

int test_pi_hex_n_places(char* expected, int n, int places) {
    char* actual = pi_hex(n, places);
    int ret_val;
    if (strcmp(expected, actual) == 0) {
        printf("test_pi_hex_n_places(%d, %d) succeeded.\n", n, places);
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
        
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
    int n = 1;
    int places = strlen(expected);
    
    return test_pi_hex_n_places(expected, n, places);
}

int test_pi_hex_2_8(void) {
    // pi base 16 = 3.243F6A8885...
    char* expected = "3F6A8885";
    int n = 2;
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

/**
 * From http://stackoverflow.com/a/4823209/7648
 */
char *readFile(char *fileName)
{
/*    FILE *file = fopen(fileName, "r");*/
/*    char *code;*/
/*    size_t n = 0;*/
/*    int c;*/

/*    if (file == NULL)*/
/*        return NULL; //could not open file*/

/*    code = malloc(1000);*/

/*    while ((c = fgets(file)) != EOF)*/
/*    {*/
/*        code[n++] = (char) c;*/
/*    }*/

/*    // don't forget to terminate with the null character*/
/*    code[n] = '\0';        */

    return 0;
}


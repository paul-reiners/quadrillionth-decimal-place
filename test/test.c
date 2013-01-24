#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include <check.h>

#include "test.h"
#include "../include/aux.h"
#include "../include/bbp.h"
#include "../include/pi.h"
#include "../include/log2.h"

int test(void)
{
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
    fail_count += test_compute_pi_sum3();
    fail_count += test_compute_pi_sum4();

    fail_count += test_pi_hex_10_n();
    printf("\n");

    return fail_count;
}

int test_compute_pi_sum(long double (*pt2_compute_pi_sum)(int), long double expected, long double tolerance)
{
    long double actual = (*pt2_compute_pi_sum)(1000000 + 1);
    long double delta = fabs(actual - expected);
    if (delta <= tolerance)
    {
        printf("test_compute_pi_sum passed\n");

        return 0;
    }
    else
    {
        printf("test_compute_pi_sum failed\n");
        printf("\texpected:   %.30Lf.\n", expected);
        printf("\tactual:     %.30Lf.\n", actual);
        printf("\tdifference: %.30Lf.\n", delta);

        return 1;
    }
}

int test_compute_pi_sum1(void) {
    // Extended value =     0.181039533801436041475746256679
    long double expected  = 0.1810395338014360;
    long double tolerance = 0.0000000000000001;
    int result = test_compute_pi_sum(&compute_pi_sum1, expected, tolerance);
    if (result > 0)
    {
        printf("test_compute_pi_sum1 failed\n");
    }
    
    return result;
}

int test_compute_pi_sum2(void)
{
    // Extended value =     0.776065549807807508742030222493
    long double expected  = 0.776065549807807;
    long double tolerance = 0.000000000000001;
    int result = test_compute_pi_sum(&compute_pi_sum2, expected, tolerance);
    if (result > 0)
    {
        printf("test_compute_pi_sum2 failed\n");
    }
    
    return result;
}

int test_compute_pi_sum3(void)
{
    // Extended value =     0.362458564070574140725256029327
    long double expected  = 0.3624585640705741;
    long double tolerance = 0.0000000000000001;
    int result = test_compute_pi_sum(&compute_pi_sum3, expected, tolerance);
    if (result > 0)
    {
        printf("test_compute_pi_sum3 failed\n");
    }
    
    return result;
}

int test_compute_pi_sum4(void)
{
    // Extended value =     0.386138673952014843671065591479
    long double expected  = 0.38613867395201484;
    long double tolerance = 0.00000000000000001;
    int result = test_compute_pi_sum(&compute_pi_sum4, expected, tolerance);
    if (result > 0)
    {
        printf("test_compute_pi_sum4 failed\n");
    }
    
    return result;
}

int test_log_2_binary(void)
{
    // log(2) base 2 = 0.101100010111...
    char* expected[] = { "101100010111", "01100010111", "1100010111" };
    int n[] = { 1, 2, 3 };
    int ret_val = 0;
    for (int i = 0; i < sizeof(n) / sizeof(int); i++)
    {
        int places = strlen(expected[i]);
        char* actual = log_2_binary(n[i], places);
        if (strcmp(expected[i], actual) == 0)
        {
            printf("test_log_2_binary succeeded.\n");
            printf("\texpected: \"%s\"; actual: \"%s\".\n", expected[i], actual);
        }
        else
        {
            printf("test_log_2_binary failed.\n");
            printf("\texpected: \"%s\"; actual: \"%s\".\n", expected[i], actual);

            ret_val++;
        }
        free(actual);
    }

    return ret_val;
}

int test_pi_hex_0_8(void)
{
    // pi base 16 = 3.243F6A88...
    char* expected = "243F6A88";
    int n = 1;
    int places = strlen(expected);

    return test_pi_hex_n_places(expected, n, places);
}

int test_pi_hex_10_n(void)
{
    char* expecteds[] = 
        { "26C65E52CB459", "17AF5863EFED", "ECB840E2192", /* "85895585A0428B" */ };
    long ns[] =  { 1000000,       10000000,     100000000,      /* 1000000000 */ };
    int error_count = 0;
    for (int i = 0; i < sizeof(ns) / sizeof(int); i++)
    {
        char* expected = expecteds[i];
        int places = strlen(expected);
        long n = ns[i];
        error_count += test_pi_hex_n_places(expected, n, places);
    }

    return error_count;
}

int test_pi_hex_n_places(char* expected, long n, int places)
{
    time_t t1, t2;
    (void) time(&t1);
    char* actual = pi_hex(n, places);
    (void) time(&t2);

    int ret_val;
    if (strcmp(expected, actual) == 0)
    {
        printf("test_pi_hex_n_places(%ld, %d) succeeded.\n", n, places);
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);

        int seconds = (int)(t2 - t1);
        char* formatted_time = format_elapsed_time(seconds);
        fprintf(stderr, "\tTime to compute = %s.\n", formatted_time);
        free(formatted_time);

        ret_val = 0;
    }
    else
    {
        printf("test_pi_hex_n_places(%ld, %d) failed.\n", n, places);
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);

        ret_val = 1;
    }
    free(actual);

    return ret_val;
}

int test_pi_hex_1_8(void)
{
    // pi base 16 = 3.243F6A888...
    char* expected = "43F6A888";
    int n = 2;
    int places = strlen(expected);

    return test_pi_hex_n_places(expected, n, places);
}

int test_pi_hex_2_8(void)
{
    // pi base 16 = 3.243F6A8885...
    char* expected = "3F6A8885";
    int n = 3;
    int places = strlen(expected);

    return test_pi_hex_n_places(expected, n, places);
}


int test_convert_log_of_2_to_binary(void)
{
    // log(2) base 2 = 0.101100010111...
    char* expected  = "101100010111";
    int ret_val;
    char* actual = convert_floating_decimal_to_base(log(2.0), 12, 2);
    if (strcmp(expected, actual) == 0)
    {
        printf("test_convert_log_of_2_to_binary succeeded.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);

        ret_val = 0;
    }
    else
    {
        printf("test_convert_log_of_2_to_binary failed.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);

        ret_val = 1;
    }

    free(actual);

    return ret_val;
}


int test_iexp(void)
{
    int error_count = 0;

    int x = 10;
    unsigned n = 999;
    unsigned k = 257;
    unsigned long int expected =  96;
    mpz_t rop;
    mpz_init(rop);
    modular_pow_gmp(rop, x, n, k);
    unsigned long int actual = mpz_get_ui(rop);
    mpz_clear(rop);
    if (expected != actual)
    {
        printf("test_iexp failed.\n");
        printf("\texpected: %lu; actual: %lu.\n", expected, actual);

        error_count++;
    }

    x = 4;
    n = 13;
    k = 497;
    expected =  445;
    mpz_init(rop);
    modular_pow_gmp(rop, x, n, k);
    actual = mpz_get_ui(rop);
    mpz_clear(rop);
    if (expected != actual)
    {
        printf("test_iexp failed.\n");
        printf("\texpected: %lu; actual: %lu.\n", expected, actual);

        error_count++;
    }

    if (error_count == 0)
    {
        printf("test_iexp passed.\n");
    }

    return error_count;
}

int test_convert_floating_decimal_to_hex(void)
{
    char* expected  = "1C71C71C7";
    int ret_val;
    char* actual = convert_floating_decimal_to_hex(1.0 / 9.0, 9);
    if (strcmp(expected, actual) == 0)
    {
        printf("test_convert_floating_decimal_to_hex succeeded.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);

        ret_val = 0;
    }
    else
    {
        printf("test_convert_floating_decimal_to_hex failed.\n");
        printf("\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);

        ret_val = 1;
    }

    free(actual);

    return ret_val;
}


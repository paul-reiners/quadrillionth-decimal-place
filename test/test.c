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

void
setup (void)
{
}

void
teardown (void)
{
}

START_TEST (test_iexp)
{
    int x = 10;
    unsigned n = 999;
    unsigned k = 257;
    unsigned long int expected =  96;
    mpz_t rop;
    mpz_init(rop);
    modular_pow_gmp(rop, x, n, k);
    unsigned long int actual = mpz_get_ui(rop);
    mpz_clear(rop);

    char errMsg[100];
    sprintf(errMsg, "\texpected: %lu; actual: %lu.\n", expected, actual);
    fail_unless(expected == actual, errMsg);

    x = 4;
    n = 13;
    k = 497;
    expected =  445;
    mpz_init(rop);
    modular_pow_gmp(rop, x, n, k);
    actual = mpz_get_ui(rop);
    mpz_clear(rop);
    sprintf(errMsg, "\texpected: %lu; actual: %lu.\n", expected, actual);
    fail_unless(expected == actual, errMsg);
}
END_TEST

START_TEST (test_convert_floating_decimal_to_hex)
{
    char* expected  = "1C71C71C7";
    char* actual = convert_floating_decimal_to_hex(1.0 / 9.0, 9);
    
    char err_msg[100];
    sprintf(err_msg, "\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
    fail_unless(strcmp(expected, actual) == 0, err_msg);

    free(actual);
}
END_TEST

START_TEST (test_convert_log_of_2_to_binary)
{
    // log(2) base 2 = 0.101100010111...
    char* expected  = "101100010111";
    char* actual = convert_floating_decimal_to_base(log(2.0), 12, 2);

    char err_msg[100];
    sprintf(err_msg, "\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
    fail_unless(strcmp(expected, actual) == 0, err_msg);

    free(actual);
}
END_TEST

Suite *
my_suite (void)
{
  Suite *s = suite_create ("BBP Suite");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);
  tcase_add_test (tc_core, test_iexp);
  tcase_add_test (tc_core, test_convert_floating_decimal_to_hex);
  tcase_add_test (tc_core, test_convert_log_of_2_to_binary);
  suite_add_tcase (s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s = my_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int test(void)
{
    int fail_count = 0;
    fail_count += test_log_2_binary();
    fail_count += test_compute_pi_sums();
    fail_count += test_pi_hex();
    printf("\n");

    return fail_count;
}

int test_compute_pi_sum(int id, long double (*pt2_compute_pi_sum)(int), long double expected, long double tolerance)
{
    long double actual = (*pt2_compute_pi_sum)(1000000 + 1);
    long double delta = fabs(actual - expected);
    if (delta <= tolerance)
    {
        printf("test_compute_pi_sum%d passed\n", id + 1);

        return 0;
    }
    else
    {
        printf("test_compute_pi_sum%d failed\n", id + 1);
        printf("\texpected:   %.30Lf.\n", expected);
        printf("\tactual:     %.30Lf.\n", actual);
        printf("\tdifference: %.30Lf.\n", delta);

        return 1;
    }
}

int test_compute_pi_sums(void)
{
    long double expected[] = 
        { 0.1810395338014360, 0.776065549807807, 0.3624585640705741, 
          0.38613867395201484};
    long double tolerance[] = 
        { 0.0000000000000001, 0.000000000000001, 0.0000000000000001, 
          0.00000000000000001 };
    long double (*fps[4])(int); 
    fps[0] = compute_pi_sum1;
    fps[1] = compute_pi_sum2;
    fps[2] = compute_pi_sum3;
    fps[3] = compute_pi_sum4;
    int result = 0;
    for (int i = 0; i < 4; i++) 
    {
        int r = test_compute_pi_sum(i, fps[i], expected[i], tolerance[i]);
        if (result > 0)
        {
            printf("test_compute_pi_sum%d failed\n", i + 1);
        }
        result += r;
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
            printf("test_log_2_binary passed.\n");
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

int test_pi_hex(void)
{
    char* expecteds[] = 
        { "243F6A88", "43F6A888", "3F6A8885", "26C65E52CB459", "17AF5863EFED", "ECB840E2192", /* "85895585A0428B" */ };
    long ns[] =  { 1, 2, 3, 1000000,       10000000,     100000000,      /* 1000000000 */ };
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
        printf("test_pi_hex_n_places(%ld, %d) passed.\n", n, places);
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


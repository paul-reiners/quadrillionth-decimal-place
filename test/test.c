#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include <check.h>

#include "../include/aux.h"
#include "../include/bbp.h"
#include "../include/pi.h"
#include "../include/log2.h"

#define RUN_EXTENDED_TEST_CASE 0

void
setup (void)
{
}

void
teardown (void)
{
}

START_TEST (test_modular_pow_gmp)
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

static const char* expected[] = { "101100010111", "01100010111", "1100010111" };
static const int n[] = { 1, 2, 3 };

START_TEST (test_log_2_binary)
{
    // log(2) base 2 = 0.101100010111...
    int places = strlen(expected[_i]);
    char* actual = log_2_binary(n[_i], places);

    char err_msg[100];
    sprintf(err_msg, "\texpected: \"%s\"; actual: \"%s\".\n", expected[_i], actual);
    fail_unless(strcmp(expected[_i], actual) == 0, err_msg);

    free(actual);
}
END_TEST

static const long double compute_pi_sums_expected[] = 
    { 0.181039533801436067853489346252, 0.776065549807807461372297594382, 
      0.362458564070574142068334335591, 0.386138673952014848001215186544 };
static const long double tolerance[] = 
    { 0.0000000000000001, 0.000000000000001, 0.0000000000000001, 
      0.00000000000000001 };
static long double (*fps[4])(long long int) = { compute_pi_sum1, compute_pi_sum2, compute_pi_sum3, compute_pi_sum4 }; 

START_TEST (test_compute_pi_sums)
{
    long double actual = (*fps[_i])(1000000 + 1);
    long double delta = fabs(actual - compute_pi_sums_expected[_i]);
    char err_msg[200];
    sprintf(
        err_msg, 
        "\n\texpected:   %.30Lf.\n\tactual:     %.30Lf.\n\tdifference: %.30Lf.\n", 
        compute_pi_sums_expected[_i], actual, delta);
    fail_unless(delta <= tolerance[_i], err_msg);
}
END_TEST

START_TEST (test_pi)
{
    long double actual = pi(1000000 + 1);
    long double expected  = 0.423429797567540358599812674109;
    long double tolerance = 0.0000000000000001;
    long double delta = fabs(actual - expected);
    char err_msg[200];
    sprintf(
        err_msg, 
        "\n\texpected:   %.30Lf.\n\tactual:     %.30Lf.\n\tdifference: %.30Lf.\n", 
        expected, actual, delta);
    fail_unless(delta <= tolerance, err_msg);
}
END_TEST

START_TEST (test_pi_extended)
{
    long double actual = pi(1000000 + 1);
    long double expected  = 0.423429797567540358599812674109;
    long double tolerance = 0.000000000000000000000000000001;
    long double delta = fabs(actual - expected);
    char err_msg[200];
    sprintf(
        err_msg, 
        "\n\texpected:   %.30Lf.\n\tactual:     %.30Lf.\n\tdifference: %.30Lf.\n", 
        expected, actual, delta);
    fail_unless(delta <= tolerance, err_msg);
}
END_TEST

START_TEST (test_compute_pi_sums_extended)
{
    long double actual = (*fps[_i])(1000000 + 1);
    long double delta = fabs(actual - compute_pi_sums_expected[_i]);
    long double tolerance = 0.000000000000000000000000000001;
    char err_msg[200];
    sprintf(
        err_msg, 
        "\n\texpected:   %.30Lf.\n\tactual:     %.30Lf.\n\tdifference: %.30Lf.\n", 
        compute_pi_sums_expected[_i], actual, delta);
    fail_unless(delta <= tolerance, err_msg);
}
END_TEST

static const char* expecteds[] =         
    { "243F6A88", "43F6A888", "3F6A8885", "26C65E52CB4593", "17AF5863EFED8D", 
      "ECB840E21926EC", "85895585A0428B" };
static const int pi_hex_precision[] = { 8, 8, 8, 12, 12, 11};
static const long ns[] =  { 1, 2, 3, 1000000, 10000000, 100000000, 1000000000 };

START_TEST (test_pi_hex)
{
    const char* expected = expecteds[_i];
    int places = pi_hex_precision[_i];
    long n = ns[_i];

    char* actual = pi_hex(n, places);

    char err_msg[200];
    sprintf(err_msg, "\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
    for (int i = 0; i < places; i++) {
        fail_unless(expected[i] == actual[i], err_msg);
    }

    free(actual);
}
END_TEST

START_TEST (test_pi_hex_extended)
{
    const char* expected = expecteds[_i];
    int places = strlen(expected);
    long n = ns[_i];

    char* actual = pi_hex(n, places);

    char err_msg[200];
    sprintf(err_msg, "\texpected: \"%s\"; actual: \"%s\".\n", expected, actual);
    for (int i = 0; i < places; i++) {
        fail_unless(expected[i] == actual[i], err_msg);
    }

    free(actual);
}
END_TEST

Suite *
my_suite (void)
{
  Suite *s = suite_create ("BBP Suite");

  /* Core test case */
  /* All the Core test cases should pass. */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);

  tcase_add_test (tc_core, test_modular_pow_gmp);
  tcase_add_test (tc_core, test_convert_floating_decimal_to_hex);
  tcase_add_test (tc_core, test_convert_log_of_2_to_binary);
  tcase_add_loop_test (tc_core, test_log_2_binary, 0, 3);
  tcase_add_loop_test (tc_core, test_compute_pi_sums, 0, 4);
  tcase_add_test (tc_core, test_pi);
  tcase_add_loop_test (tc_core, test_pi_hex, 0, 6);
  tcase_add_loop_test (tc_core, test_compute_pi_sums_extended, 2, 4);
  tcase_add_test (tc_core, test_pi_extended);

  tcase_set_timeout (tc_core, 0);
  suite_add_tcase (s, tc_core);

  if (RUN_EXTENDED_TEST_CASE) {
      /* Extended test case */
      /* All the Extended test cases should pass *after* I get the required precision. */
      TCase *tc_extended = tcase_create ("Extended");
      tcase_add_checked_fixture (tc_extended, setup, teardown);

      tcase_set_timeout (tc_extended, 0);
      suite_add_tcase (s, tc_extended);
      tcase_add_loop_test (tc_extended, test_compute_pi_sums_extended, 0, 2);
      tcase_add_loop_test (tc_extended, test_pi_hex_extended, 3, 7);
  }

  return s;
}

int main(void)
{
    mpf_set_default_prec(128);
    mp_bitcnt_t default_float_prec = mpf_get_default_prec();
    printf("Default float precision is %lu bits.\n", default_float_prec);

    int number_failed;
    Suite *s = my_suite ();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


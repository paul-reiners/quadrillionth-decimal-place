#ifndef CORE_H
#define CORE_H

#include <stdbool.h>

long double decimal_reciprocal(int n, int pos);
long double compute_3_4_first_sum(int n, int base, int c, int (*p)(int), bool start_at_0);
long double compute_3_4_second_sum(int n, int base, int c, int (*p)(int));
long double mod_one(long double x);
char* convert_floating_decimal_to_hex(long double x, int places);
char* convert_floating_decimal_to_base(long double x, int places, int base);
long double compute_3_4(int n, int base, int c, int (*p)(int), bool start_at_0);
char* compute_3_4_to_base(int n, int base, int c, int (*p)(int), int places, bool start_at_0);
long double calculate_machine_epsilon(void);
long double compute_s_first_sum(int d, int j);
long double compute_s_second_sum(int d, int j);
long double compute_s(int d, int j);

#endif // CORE_H


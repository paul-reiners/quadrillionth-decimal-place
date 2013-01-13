#ifndef CORE_H
#define CORE_H

#include <stdbool.h>

double decimal_reciprocal(int n, int pos);
double compute_3_4_first_sum(int n, int base, int c, int (*p)(int), bool start_at_0);
double compute_3_4_second_sum(int n, int base, int c, int (*p)(int));
double mod_one(double x);
char* convert_floating_decimal_to_hex(double x, int places);
char* convert_floating_decimal_to_base(double x, int places, int base);
double compute_3_4(int n, int base, int c, int (*p)(int), bool start_at_0);
char* compute_3_4_to_base(int n, int base, int c, int (*p)(int), int places, bool start_at_0);

#endif // CORE_H


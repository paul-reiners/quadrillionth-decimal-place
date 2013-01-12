#ifndef CORE_H
#define CORE_H

double decimal_reciprocal(int n, int pos);
double compute_3_4_first_sum(int n, int base, int c, int (*p)(int));
double compute_3_4_second_sum(int n, int base, int c, int (*p)(int));
double mod_one(double x);
char* convert_floating_decimal_to_hex(double x, int places);
char* convert_floating_decimal_to_base(double x, int places, int base);

#endif // CORE_H


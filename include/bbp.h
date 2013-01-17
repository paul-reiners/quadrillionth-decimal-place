#ifndef CORE_H
#define CORE_H

#include <stdbool.h>

long double compute_3_4_first_sum(int n, int base, int c, int (*p)(int), bool start_at_0);
long double compute_3_4_second_sum(int n, int base, int c, int (*p)(int));
long double compute_3_4(int n, int base, int c, int (*p)(int), bool start_at_0);
char* compute_3_4_to_base(int n, int base, int c, int (*p)(int), int places, bool start_at_0);

#endif // CORE_H


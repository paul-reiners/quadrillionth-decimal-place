#ifndef AUX_H
#define AUX_H

unsigned long int modular_pow(unsigned long int b, unsigned long int exponent, unsigned long int modulus);
long double mod_one(long double x);
char* convert_floating_decimal_to_hex(long double x, int places);
char* convert_floating_decimal_to_base(long double x, int places, int base);
long double calculate_machine_epsilon(void);

#endif // AUX_H


#define _XOPEN_SOURCE
#define PLACES 8

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "../test/test.h"
#include "../include/pi.h"
#include "../include/log2.h"

/** 
 * getopt code adapted from
 *      http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
 */
int main(int argc, char* argv[]) {
    // t = display calculation time (flag)
    // u = unit test (flag)
    // n = number to calculate digits of
    // d = starting digit
    
    int tflag = 0;
    int uflag = 0;
    char *nvalue = NULL;
    char *dvalue = NULL;
    int index;
    int c;

    while ((c = getopt (argc, argv, "tun:d:")) != -1)
     switch (c)
       {
       case 't':
         tflag = 1;
         break;
       case 'u':
         uflag = 1;
         break;
       case 'n':
         nvalue = optarg;
         break;
       case 'd':
         dvalue = optarg;
         break;
       case '?':
         if (optopt == 'n' || optopt == 'd')
           fprintf(stderr, "Option -%c requires an argument.\n", optopt);
         else if (isprint (optopt))
           fprintf (stderr, "Unknown option `-%c'.\n", optopt);
         else
           fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
         return 1;
       default:
         abort ();
       }

    printf ("tflag = %d, uflag = %d, nvalue = %s, dvalue = %s\n",
           tflag, uflag, nvalue, dvalue);

    for (index = optind; index < argc; index++)
     printf ("Non-option argument %s\n", argv[index]);

    time_t t1,t2;
    if (tflag) {
        (void) time(&t1);
    }
	char* result = NULL;
    if (uflag) {
        int result = test();
        if (result == 0) {
            printf("Tests succeeded.\n");
        } else {
            printf("Tests failed.\n");
        }
    } else if (nvalue == NULL || strcmp(nvalue, "pi") == 0) {
        if (dvalue == NULL) {
           fprintf(stderr, "You must specify a -d value.\n");
        } else {
            int d = atoi(dvalue);
        	result = pi_hex(d, PLACES);
        	fprintf(stderr, "Hex digits of pi beginning at position %d: ", d);
        	printf("%s\n", result);
        }
    } else if (strcmp(nvalue, "log2") == 0) {
        if (dvalue == NULL) {
           fprintf(stderr, "You must specify a -d value.\n");
        } else {
            int d = atoi(dvalue);
        	result = log_2_binary(d, PLACES);
        	fprintf(stderr, "Binary digits of log(2) beginning at position %d: ", d);
        	printf("%s\n", result);
        }
    } else {
        fprintf(stderr, "%s is an invalid argument for -n.\n", nvalue);
        fprintf(stderr, "\t\"pi\" and \"log2\" are valid arguments.\n");
    }
    if (tflag) {
        (void) time(&t2);
        
        // TODO Factor out common code below and in test.c
        int left = (int) (t2-t1);
        int hours = left / (60 * 60);
        left -= (60 * 60) * hours;
        int minutes = left / 60;
        left = left -= minutes * 60;
        int seconds = left;
		fprintf(stderr, "\tTime to compute = %02d:%02d:%02d.\n", hours, minutes, seconds);
    }
    
    if (result != NULL) {
        free(result);
    }

    return 0;
}


/****************************************************************************
 * project.c
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * Final Project
 *
 * An implementation of the Bailey–Borwein–Plouffe (BBP) formula in C.
 ***************************************************************************/

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
#include "../include/aux.h"

int main(int argc, char* argv[])
{
    char* usage = "Usage: project [-t] [-n number_code] first_digit";
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-h") == 0))
    {
        printf("%s\n", usage);

        return 0;
    }

    int tflag = 0;
    int uflag = 0;
    char* nvalue = NULL;
    int c;

    while ((c = getopt(argc, argv, "tun:")) != -1)
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
            case '?':
                if (optopt == 'n' || optopt == 'd')
                {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                }
                else if (isprint(optopt))
                {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                }
                else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return 1;
            default:
                abort();
        }

    if (uflag)
    {
        int result = test();
        if (result == 0)
        {
            printf("Tests succeeded.\n");

            return 0;
        }
        else
        {
            printf("Tests failed.\n");

            return 1;
        }
    }

    int d;
    if (optind >= argc)
    {
        fprintf(stderr, "You must specify a d value.\n");

        return 1;
    }
    else
    {
        char* dvalue = argv[optind];
        char* upper_limit_str = "100000000";
        char too_large_err_msg[120];
        sprintf(
            too_large_err_msg,
            "Cannot handle d larger than %s.  Please specify a smaller value.\n",
            upper_limit_str);
        if (strlen(dvalue) > strlen(upper_limit_str))
        {
            fprintf(stderr, "%s", too_large_err_msg);

            return 1;
        }
        else if (!is_integer(dvalue))
        {
            fprintf(
                stderr,
                "%s is an invalid value for d.  Please enter an integer (with no commas in it).  For example: 1000000.\n",
                dvalue);

            return 1;
        }
        d = atoi(dvalue);
        if (d > 100000000)
        {
            fprintf(stderr, "%s", too_large_err_msg);

            return 1;
        }
    }

    time_t t1, t2;
    if (tflag)
    {
        (void) time(&t1);
    }
    char* result = NULL;
    if (nvalue == NULL || strcmp(nvalue, "pi") == 0)
    {
        result = pi_hex(d, PLACES);
        fprintf(stderr, "Hex digits of pi beginning at position %d: ", d);
    }
    else if (strcmp(nvalue, "log2") == 0)
    {
        result = log_2_binary(d, PLACES);
        fprintf(stderr, "Binary digits of log(2) beginning at position %d: ", d);
    }
    else
    {
        fprintf(stderr, "%s is an invalid argument for -n.\n", nvalue);
        fprintf(stderr, "\t\"pi\" and \"log2\" are valid arguments.\n");

        return 1;
    }
    printf("%s\n", result);

    if (tflag)
    {
        (void) time(&t2);

        int seconds = (int)(t2 - t1);
        char* formatted_time = format_elapsed_time(seconds);
        fprintf(stderr, "\tTime to compute = %s.\n", formatted_time);
        free(formatted_time);
    }

    if (result != NULL)
    {
        free(result);
    }

    return 0;
}


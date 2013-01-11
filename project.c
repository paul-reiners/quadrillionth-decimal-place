#define _XOPEN_SOURCE

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int c = getopt(argc, argv, "abc:");
    printf("%d\n", c);
    
    return 0;
}


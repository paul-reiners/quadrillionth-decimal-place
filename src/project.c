#include <stdio.h>

#include "../test/test.h"

int main(int argc, char* argv[]) {
    int result = test();
    if (result == 0) {
        printf("Tests succeeded.\n");
    } else {
        printf("Tests failed.\n");
    }
}


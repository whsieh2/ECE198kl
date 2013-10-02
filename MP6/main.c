#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lorenz.h"

int main(int argc, const char *argv[])
{
    if (argc == 4) {
        if (!strcmp(argv[1], "euler")) {
            return do_lorenz_euler(argv[2], argv[3]);
        } else if (!strcmp(argv[1], "rk4")) {
            return do_lorenz_rk4(argv[2], argv[3]);
        }
    }

    fprintf(stderr, "Usage: %s <euler|rk4> <input> <output>\n", argv[0]);
    return EXIT_FAILURE;
}

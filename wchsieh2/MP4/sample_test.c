#include <stdio.h>

/* Include your code as part of this file. */
#include "jni/prog4.c"

int
main ()
{
    int32_t failed = 0;
    double diff;

    /* When called with BUTTON_PLUS, your code should add the two arguments. */
    diff = (execute_operator (BUTTON_PLUS, 7.5, 8.9) - (7.5 + 8.9));
    if (1E-9 < fabs (diff)) {
        printf ("test failed: 7.5 + 8.9 off by %e\n", diff);
	failed |= 1;
    }
    if (!failed) {
        printf ("all tests passed\n");
    }
    return 0;
}


#include "../include/gen1/gen1_math.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    int a = 02;
    int b = 10;
    int c = 33;

    int d;

    d = __int_concat(a, b);
    d = __int_concat(d, c);

    printf("%d\n", d);

    return 0;
}

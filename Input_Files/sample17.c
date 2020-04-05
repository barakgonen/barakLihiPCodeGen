#include <stdio.h>

void main()
{
    float a;
    int b;
    b = 1;
    a = 5;
    for (a = 0; a < 5; a++)
    {
        printf("%d\n", b);
        printf("%f\n", a);
        b -= b; //b=0. print 111
    }

    for (a = 1; a < 3; a++)
    {
        if (!b)
            printf("%d\n", 111);
        b -= b; //b=0. print 111
    }

    return;
}
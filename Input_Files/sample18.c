#include <stdio.h>

void main()
{
    int a;
    int i;
    double j = 213.2131;
    double k;
    int b = 45435;
    int c = 2334;
    double d = 1378;
    int x = 1;
    double e = 4444;
    float y = 24875.2313;
    double z = 769876.213123;
    float f;
    f = 2323.278645;

    i = 3;
    while (i-- > -100)
    {
        i--;
        printf("%d\n ", i);
    }

    i = 2;
    do
    {
        while (x < 19 && d > 50)
        {

            for (e = 2; e < 30; e /= 0.5)
            {
                printf("%f\n", e);
                f--;
                printf("%f\n", f);
                f++;
                printf("%f\n", f);
                ++f;
                printf("%f\n", f);
                --f;
                printf("%f\n", f);
            }

            x *= 2;
            d *= 0.75;
            printf("%d\n", x);
            printf("%f\n", d);
        }

        // statement of outer do-while loop
    } while (--i >= 0);

    x = 10;
    do
    {
        printf("%d\n", x * 2);
        x -= 1;
        do
        {
            printf("%d\n", x * 10);
            // statement of inside loop
            x -= 1;
        } while (x > 0);
        printf("%d\n", x * 5);
        // statement of outer loop
    } while (x > 2);

    for (i = 0; i < 50; i += 2)
    {
        for (k = 1; k < 20; ++k)
        {
            printf("%d\n", i);
            printf("%f\n", k);
        }
    }
    e = 4444;

    while (e > 12)
    {

        while (e > 100)
        {

            printf("%f\n", e);
            e *= 0.5;
        }

        e /= 4;
    }
    return;
}
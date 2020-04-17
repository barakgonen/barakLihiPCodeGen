#include <stdio.h>

void main()
{
    int b = 1;
    float a;
    a = 5;

    do
    {
        printf("%.2f\n", --a); //print 3,2,1,0
        if (a && b)
        {
            printf("%d\n", 555); //print 555,555,555
        }
    } while (a || 0);
    return;
}
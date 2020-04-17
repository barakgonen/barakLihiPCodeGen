#include <stdio.h>
void main()
{
    int *pc;
    int *c;
    int k = 10;
    c = 22;
    printf("%d\n", c); // value of c which is 22
    pc = 156;
    printf("%d\n", pc); // value of pc which is 156
    printf("%d\n", *pc); // address of pc which is 5

    pc = 20;
    printf("%d\n", pc); // value of pc which is 20
    printf("%d\n", *pc); // address of pc which is 5

    c = &k;
    k = (*c) + 2;
    printf("%d\n", k); // value of k which is 12
    printf("%d\n", c); // address of c, which is the address of k which is 7
    printf("%d\n", *c); // address of c which is 6  BUG!

    // printf("%d\n", 999998);
    // k = (*c)++;
    // printf("%d\n", k);
    // printf("%d\n", *c);
    // printf("%d\n", 999999);

    // k = 5 * (*(c)++);
    // printf("%d\n", k);
    // printf("%d\n", c);
    ++(*c);
    printf("%d\n", c);

    return;
} 
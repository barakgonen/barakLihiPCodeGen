#include <stdio.h>
struct BaseObject
{
    int AAA;
    int BBB;
    int CCC;
};

void main()
{
    int *pc;                // 5
    int *c;                 // 6
    int* k = 10;            // 7
    int a = 1;              // 8
    int b = 2;              // 9
    int c = 3;              // 10
    int d = 4;              // 11
    double* e = 13;         // 12
    float s = 2.2;          // 13
    int** second = 7;       // 14
    int *** third = 14;     // 15
    int**** forth = 15;     // 16
    double* cd[30];
    struct BaseObject* bla;
    int i;
    c = 22;
    printf("%d\n", c); // value of c which is 22
    pc = 7;
    printf("%d\n", pc); // value of pc which is 7
    printf("%d\n", *pc); // address of pc which is 5

    printf("%d\n", e); // value of e which is 13
    printf("%d\n", *e); // address of e which is 2.2

    printf("%d\n", forth);      // the address which forth is pointing at, which is 15
    printf("%d\n", *forth);     // the value in the address of third which should be 14
    printf("%d\n", **forth);    // the value in the address of second which should be 7
    printf("%d\n", ***forth);  // the value int the address of k which should be 10

    for (i = 0; i < 30; i++){
        cd[i] = i;
    }
    for (i = 0; i < 30; i++){
        printf("%f\n", *cd[i]);
    }
//
//    c = *k;
//    k = (*c) + 2;
//    printf("%d\n", k); // value of k which is 12
//    printf("%d\n", c); // address of c, which is the address of k which is 7
//    printf("%d\n", *c); // address of c which is 6  BUG!
//
//     printf("%d\n", 999998);
//     k = (*c)++;
//     printf("%d\n", k);
//     printf("%d\n", *c);
//     printf("%d\n", 999999);
//
//     k = 5 * (*(c)++);
//     printf("%d\n", k);
//     printf("%d\n", c);
//    printf("%d\n", c);
//    ++(*c);
//    printf("%d\n", c);
//
//    printf("%d\n", c);
//    (*c)++;
//    printf("%d\n", c);
//
//     a=(*c)+2;
//     a = 5 * (**d);
//
//    printf("%d\n", c);
//    *c++;
//    printf("%d\n", c);
//
//    printf("%d\n", c);
//    ++*c;
//    printf("%d\n", c);

    return;
} 
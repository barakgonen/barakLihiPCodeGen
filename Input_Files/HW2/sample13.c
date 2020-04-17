#include <stdio.h>
#include <stdlib.h>

struct BaseObject
{
    int AAA;
    int BBB; 
    int CCC; 
};

struct bakBAK
{
    int aa;
    struct BaseObject base; 
    int bb; 
    int cc;
};

struct blaTYpe
{
    int a;
    int b; 
    int c;
    struct bakBAK aa;
};


void main()
{
    struct blaTYpe a;
    a.a = 1;
    a.b = 2;
    a.c = 3;
    a.aa.aa = 4;
    a.aa.bb = 5;
    a.aa.cc = 6;
    a.aa.base.AAA = 7;
    a.aa.base.BBB = 8;
    a.aa.base.CCC = 9;
    printf("%d\n", a.a);
    printf("%d\n", a.b);
    printf("%d\n", a.aa.aa);
    printf("%d\n", a.aa.bb);
    printf("%d\n", a.aa.cc);
    printf("%d\n", a.aa.base.AAA);
    printf("%d\n", a.aa.base.BBB);
    printf("%d\n", a.aa.base.CCC);
    return;
}
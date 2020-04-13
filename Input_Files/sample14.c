#include <stdio.h>

void main() {
    float a;
    int b;
    double e;
    int x;
    float f;
    f=0;
    x=1;
    b=1;
    a = 5;
    e = 7;
    // e = a--; //e=5. a=4 store to a and than decrement  
    printf("%.2f\n",e); //print 5.00
    printf("%d\n",b++); //print: 1. b=2.
    printf("%.2f\n",--a); //print 3.00 = a
    printf("%.2f\n",-e); //print -5.00
    a=1;
    if (a--) //true. a=0
        printf("%d\n",x++); //print 1. x=2
    else
        printf("%d\n",++x); // print 3
    if (--a) //true. a=-1
        printf("%d\n",++x); // print 4

    a=1;
    b=1;
    if(a==b)
        printf("%.2f\n",a); //print 1.00
    if(a==1)
        printf("%.2f\n",a+a); //print 2.00
    if(0==a) //false
        printf("%.2f\n",a);
    if(a!=b) //false
        printf("%.2f\n",a);
    if(a>=b)
        printf("%.2f\n",a*4); //print 4.00
    while (a<=2)
        printf("%.2f\n",++a); //print 2.00 , 3.00

    a=1;
    printf("%.2f\n",a); // print 1.00
	
	return;
}
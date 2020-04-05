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
    e = a--; //e=5. a=4
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
    x--;
    printf("%d\n",x);// print 3
    x = (x==5)?(11):(22); //x=22
    printf("%d\n",x);
    ++x;
    // // for(a=1;a>=1;x--){
    // //     for(a=1;a>0;--x) {
    // //         if (a-- > 0)
    // //             printf("%d\n", x); //print 23
    // //         if (x)
    // //             printf("%d\n",x); //print 23
    // //     }
    // // }
    printf("%d\n",x); //print 21
    a=35;
    b=550;
    a+=b;
    printf("%.2f\n",a); //print 585.00
    a-=b;
    printf("%.2f\n",a); //print 550.00
    a-=2;
    printf("%.2f\n",a); //print 548.00
    a+=3;
    printf("%.2f\n",a); //print 551.00
    a=10.23;
    b=20;
    a-=0.23;
    a*=b;
    printf("%.2f\n",a); //print 200.00
    a/=b;
    printf("%.2f\n",a); //print 10.00
    a=4;
    f=5;
    printf("%.2f\n",a+f); //print 9.00
    a = f-3;
    printf("%.2f\n",a); //print 2.00
    a = 3- f;
    printf("%.2f\n",a); //print -2.00
    a = f+f;
    printf("%.2f\n",a); //print 10.00
    a = 1+f;
    printf("%.2f\n",a); //print 6.00
    a = a*a;
    printf("%.2f\n",a); //print 36.00
    a = a/a;
    printf("%.2f\n",a); //print 1.00
    a = 6/a;
    printf("%.2f\n",a); //print 6.00
    a = a/12;
    printf("%.2f\n",a); //print 0.50
    a = 2*a;
    // printf("%.2f\n",a); //print 1.00
    // a = a*4;
    // printf("%.2f\n",a); //print 4.00
    // b = 1;
    // // do{
    // //     printf("%.2f\n",--a); //print 3,2,1,0
    // //     if(a&&b){
    // //         printf("%d\n",555); //print 555,555,555
    // //     }
    // // }while(a||0);

    // // for(a=1;a<3;a++) {
    // //     if (!b)
    // //         printf("%d\n", 111);
    // //     b -= b; //b=0. print 111
    // // }
    // a=1;
    // b=1;
    // if(a==b)
    //     printf("%.2f\n",a); //print 1.00
    // if(a==1)
    //     printf("%.2f\n",a+a); //print 2.00
    // if(0==a) //false
    //     printf("%.2f\n",a);
    // if(a!=b) //false
    //     printf("%.2f\n",a);
    // if(a>=b)
    //     printf("%.2f\n",a*4); //print 4.00
    // while (a<=2)
    //     printf("%.2f\n",++a); //print 2.00 , 3.00

    // a=1;
    // printf("%.2f\n",+a); // print 1.00

    return;
}

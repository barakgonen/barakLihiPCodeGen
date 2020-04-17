#include <stdio.h>

void main() {
    double x = 1;
    double a;
    float y = 7.7;
    // double z = 1.12345678;
    double b;
    // double c= -345.12;
    printf("%f\n", x);
    printf("%f\n", y);
    x = ++y;
    printf("%f\n", x);
    printf("%f\n", y);
    x = ++x;
    printf("%f\n", x);
    printf("%f\n", y);
    // x = y++;
    printf("%f\n", x);
    printf("%f\n", y);
    // x = x++;
    printf("%f\n", x);
    printf("%f\n", y);
    b = 1;
    a = 15 * b;
    printf("%f\n", a);
    a = b * 15;
    printf("%f\n", a);
    a = 1 * 15;
    printf("%f\n", a);
    b = 1.1 * 15.4;
    printf("%f\n", b);
    a = b * 5;
    printf("%f\n", a);
    printf("%f\n", b);
    b *= a;
    printf("%f\n", b);
    printf("%f\n", a);
    b = 5 * b;
    printf("%f\n", 222222.1111);
    printf("%d\n", 1233456);
    printf("%f\n", b);
    printf("%f\n", a);
    b = a * 5;
    printf("%f\n", b);
    b *= a;
    printf("%f\n", b);
    printf("%f\n", a);
    a *= b;
    printf("%f\n", b);
    printf("%f\n", a);
    if (a <= b)
        printf("%f\n", a * 4); //print 4.00
    if (a >= b)
        printf("%f\n", a * 4); //print 4.00
    printf("%f\n", b);
    printf("%f\n", a);
    if (a >= b)
        printf("%f\n", a * b); //print 4.00
    if (a >= b)
        printf("%f\n", b * a); //print 4.00
    if (a >= b)
        printf("%f\n", 4 * a); //print 4.00
    printf("%f\n", x);
    // x = y++;
    printf("%f\n", y);
    printf("%f\n", x);
    printf("%f\n", y);
    b=1;
    printf("%f\n",b++);
    printf("%f\n", b);
    printf("%f\n",++b);
    printf("%f\n",b);
    printf("%f\n",--a); 
    printf("%f\n", a);
    printf("%f\n",a--);
    printf("%f\n", a);
    // MUL by neg
    b = b * -1.1212;
    printf("%f\n", b);
    b = -23213.3243 * b;
    printf("%f\n", b);
    x *= (b*-213) + 16;
    printf("%f\n", b);
    b = (-b) * (-(-b));
    printf("%f\n", b);
    // DIV by neg
    b -= -b/(-234.43);
    printf("%f\n", b);
    x = 10;
    b = -2;
    x+=x/b+12;
    printf("%f\n", x);
    printf("%f\n", b);
    // b/=(-123/x)-1000;
    printf("%f\n",b);
    // b/=(b*-12)/(-11);
    printf("%f\n",b);
    printf("%f\n",x);
    // b/=x++;
    printf("%f\n",b);
    printf("%f\n",x);
    return;
}

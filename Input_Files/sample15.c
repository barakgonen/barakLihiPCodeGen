#include <stdio.h>

void main() {
	int x = 1;
    int a;
	float y = 7.7;
	// double z = 1.12345678;
    int b;
	x = x++;
    a = 5;
	printf("%d\n", x);
	x = y++;
	printf("%d\n", x);
    printf("%f\n", y);
    b=1;
    printf("%d\n",b++);
    printf("%d\n", b);
    printf("%d\n",++b);
    printf("%d\n",b);
    printf("%d\n",--a); 
    printf("%d\n", a);
    printf("%d\n",a--);
    printf("%d\n", a);
    return;
}
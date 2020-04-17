#include <stdio.h>

int a;
void main() {
	int b = 1111;
	int c = 2222;
	int d = 3333;
	int e = 4444;
	a = 5555;
	a -= b;
	c +=b;
	d *= a;
	e /= b;

	printf("%d\n", a);			// V
	printf("%d\n", c);			// V
	printf("%d\n", d);			// V
	printf("%d\n", e);			// V
	printf("%d\n", b);			// V
	return;
}
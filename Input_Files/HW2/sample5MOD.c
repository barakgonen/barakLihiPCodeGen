#include <stdio.h>

void main() {
	int a[1];
	int* b;
	int** c;
	int*** d;

	b = &a;
	c = &a;
	d = &a;

	a[0] = 8;
	printf("%d\n",(d)[0]);
	return;
}
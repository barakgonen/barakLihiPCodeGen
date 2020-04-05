#include <stdio.h>

void main() {
	int x = 1;
	float y = 1.1;
	double z = 1.12345678;

	x = x || y;
	printf("%d\n", x);
	y = x || (z || y);
	printf("%f\n", y);
	z = (x || y) || (z || x);
	printf("%f\n", z);
	x = x && y;
	printf("%d\n", x);
	y = y && x;
	// x = x == y;
	printf("%f\n", y);
	x = x == y;
	printf("%d\n", x);
	y = x != (z || y);
	printf("%f\n", y);
	z = !(x || y) == (z && x);
	printf("%f\n", z);
	z = !((x || y) == (z && x));
	printf("%f\n", z);
	//	N-EQU
	x = x != y;
	printf("%d\n", x);
	y = x != (z == y);
	printf("%f\n", y);
	z = (x != y) != (z != x);
	printf("%f\n", z);
	// //	GRT
	x = x > y;
	printf("%d\n", x);
	y = x < (z > y);
	printf("%f\n", y);
	z = (x != y) > (z != x);
	printf("%f\n", z);
	//	LESS
	x = x < y;
	printf("%d\n", x);
	y = x < (z < y);
	printf("%f\n", y);
	z = (x < y) > (z < x);
	printf("%f\n", z);
	x = x < y;
	printf("%d\n", x);
	//	GREQ
	printf("%f\n", x);
	y = x < (z <= y);
	printf("%f\n", y);
	z = (x <= y) > (z <= x);
	printf("%f\n", z);
	//	LESSEQ
	x = x <= y;
	printf("%d\n", x);
	y = x < (z <= y);
	printf("%f\n", y);
	z = (x <= y) >= (z < x);
	printf("%f\n", z);
	// INC
	printf("%d\n", x);
	x = x++;
	printf("%d\n", x);
	x = y++;
	printf("%f\n", x);
	x += 1;
	printf("%d\n", x);
	x++;
	printf("%d\n", x);
	++x;
	printf("%d\n", x);
	y = y++;
	printf("%f\n", y);
	y++;
	printf("%f\n", y);
	++y;
	printf("%f\n", y);
	z = z++;
	printf("%f\n", z);
	z++;
	printf("%f\n", z);
	++z;
	printf("%f\n", z);
	// DEC
	x = x--;
	printf("%d\n", x);
	x--;
	printf("%d\n", x);
	--x;
	x -= 2;
	printf("%d\n", x);
	printf("%d\n", x);
	y = y--;
	printf("%f\n", y);
	y--;
	printf("%f\n", y);
	--y;
	printf("%f\n", y);
	z = z--;
	printf("%f\n", z);
	z--;
	printf("%f\n", z);
	--z;
	printf("%f\n", z);
	return;
}
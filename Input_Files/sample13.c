#include <stdio.h>

void main() {
	int x = 1;
	float y = 1.1;
	double z = 1.12345678; 
	//	+=
	x += 1;
	printf("%d\n", x);
	y += 1.00005;
	printf("%f\n", y);
	printf("%f\n", z);

	//	-=
	x = 10;
	x -= x - 1;
	printf("%d\n", x);
	y -= - 1.00505 - y;
	printf("%f\n", y);
	z -= -2.343;
	printf("%f\n", z);
	//	*=
	x *= x * (-1);
	printf("%d\n", x);
	y *= 2.45;
	printf("%f\n", y);
	z *= -0.45;
	printf("%f\n", z);

	//	/=
	x /= x;
	printf("%d\n", x);
	y /= (1 + !y); 
	printf("%f\n", y);
	z /= ((!z + 5.2) * 4) / y;
	printf("%f\n", z);
	//	coomplex conditions
	x *= (y || 2);
	printf("%d\n", x);
	y += x || ((z || y) + 87);
	printf("%f\n", y);
	z /= (((x || y) + 4.2) && ((z || x) * (- 2)) + 1);
	printf("%f\n", z);
	
	return;
}
#include <stdio.h>

struct BaseObject
{
    int AAA;
    int BBB; 
    int CCC; 
};

void main() {
	int i;
	int b[10];
	double c[11];
	float d[12];
	struct BaseObject e[13];

	for (i = 0; i < 10; i++){
		b[i] = i*2;
	}
	for (i = 0; i < 10; i++){
		printf("%d\n", b[i]);
	}

	for (i = 0; i < 11; i++){
		c[i] = i + 2.02;
	}
	for (i = 0; i < 11; i++){
		printf("%f\n", c[i]);
	}
	for (i = 0; i < 12; i++){
		d[i] = i + 2.12;
	}
	for (i = 0; i < 12; i++){
		printf("%f\n", d[i]);
	}
	for (i = 0; i < 13; i++){
		e[i].AAA = i + 5;
		e[i].BBB = i + 6;
		e[i].CCC = i + 7;
	}
	for (i = 0; i < 13; i++){
		printf("%f\n", e[i].AAA);
		printf("%f\n", e[i].BBB);
		printf("%f\n", e[i].CCC);
	}
	// pointer/
	// int a[10][4];
	// int c[5][5][5];

	// a[9][2] = 12;
	// i = 9;
	// b[7] = 2;
	// a[5][2] = 3;
	// c[1][2][3] = 4;

	// printf("%d\n",a[5][2]);
	return;
}
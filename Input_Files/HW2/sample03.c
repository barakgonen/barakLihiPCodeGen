#include <stdio.h>

struct BaseOObject
{
    int qqqq;
    int wwww; 
    int eeee; 
};
struct BaseTObject
{
    int rrrr;
    int tttt; 
    int yyyy;
	struct BaseOObject uuuuu;
};
struct BaseTTObject
{
    int iiii;
    int oooo; 
    int pppp; 
	struct BaseTObject ssss;
};

struct BaseObject
{
    int dddd;
    int ffff; 
    int kkkk; 
	struct BaseTTObject G;
};

void main() {
	int i;   				// 5
	int b[10];  			// start: 6 --> end  16
	double c[11]; 			// start: 17 --> end 28
	float d[12]; 			// start: 29 --> end 41
	struct BaseObject e[31]; // start: 42 --> end 414
	// pointer/
	// int a[10][4];
	// int three[5][5][5];


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
	
	for (i = 0; i < 31; i++){
		e[i].dddd = 123 + i;
		e[i].ffff = 456 - i;
		e[i].kkkk = 789 * i;
		e[i].G.ssss.uuuuu.qqqq = 123 - (5 * i);
		e[i].G.ssss.uuuuu.wwww = 456 + (7 / 7);
		e[i].G.ssss.uuuuu.eeee = 789 - (i * -5);
	}
	for (i = 0; i < 31; i++){
		printf("%d\n", e[i].dddd);
		printf("%d\n", e[i].ffff);
		printf("%d\n", e[i].kkkk);
		printf("%d\n", e[i].G.ssss.uuuuu.qqqq);
		printf("%d\n", e[i].G.ssss.uuuuu.wwww);
		printf("%d\n", e[i].G.ssss.uuuuu.eeee);
	}

	// a[9][2] = 12;
	i = 9;
	for (i = 0; i < 10; i++){
		printf("%d\n", b[i]);
	}
	b[7] = 2;
	for (i = 0; i < 10; i++){
		printf("%d\n", b[i]);
	}
	// a[5][2] = 3;
	// c[1][2][3] = 4;

	// printf("%d\n",a[5][2]);
	return;
}
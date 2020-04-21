#include <stdio.h>

struct BaseOne
{
    double qqqq;
    double eeee; 
};

struct BaseTwo
{
    int rrrr;
    int tttt; 
    int yyyy;
	struct BaseOne uuuuu;
};
struct BaseThree
{
    int iiii;
    int oooo; 
    int pppp; 
	struct BaseTwo ssss;
};

struct BaseFour
{
    int dddd;
    int ffff; 
    int kkkk; 
	struct BaseThree G;
};

void main() {
	int i;   				// 5
	int b[2];  			// start: 6 --> end  16
	double c[2]; 			// start: 17 --> end 28
	float d[2]; 			// start: 29 --> end 41
	struct BaseFour e[2]; // start: 42 --> end 414
	// // pointer/
	// int a[2][2];
	// int three[3][3][3];
	// int* aa;
	// int** aa;
	// int*** aaa;
	// int**** aaaa;
	int aV = 4;
	double dV = 4.4;
	float cV = 5.5;
	struct BaseFour bS;
	i = 53;
	bS.dddd = 123 + i;
	bS.ffff = 456 - i;
	bS.kkkk = 789 * i;
	bS.G.iiii = i + 2 * i + 3 * i;
	bS.G.oooo = (i + 1) * 2; 
	bS.G.pppp = i * i;
	bS.G.ssss.rrrr = 123 - (5 * i);
	bS.G.ssss.tttt = 456 + (7 / 7);
	bS.G.ssss.yyyy = 789 - (i * -5);
	bS.G.ssss.uuuuu.eeee = 5.5;
	bS.G.ssss.uuuuu.qqqq = 2 * 3.05;


	printf("%d\n", aV);
	printf("%f\n", dV);
	printf("%f\n", cV);
	printf("%d\n", i);
	printf("%d\n", bS.dddd);
	printf("%d\n", bS.ffff);
	printf("%d\n", bS.kkkk);
	printf("%d\n", bS.G.iiii);
	printf("%d\n", bS.G.oooo);
	printf("%d\n", bS.G.pppp);
	printf("%d\n", bS.G.ssss.rrrr);
	printf("%d\n", bS.G.ssss.tttt);
	printf("%d\n", bS.G.ssss.yyyy);
	printf("%f\n", bS.G.ssss.uuuuu.eeee);
	printf("%f\n", bS.G.ssss.uuuuu.qqqq);
	// for (i = 0; i < 10; i++){
	// 	b[i] = i*2;
	// }
	// for (i = 0; i < 10; i++){
	// 	printf("%d\n", b[i]);
	// }

	// for (i = 0; i < 11; i++){
	// 	c[i] = i + 2.02;
	// }
	// for (i = 0; i < 11; i++){
	// 	printf("%f\n", c[i]);
	// }
	// for (i = 0; i < 12; i++){
	// 	d[i] = i + 2.12;
	// }
	// for (i = 0; i < 12; i++){
	// 	printf("%f\n", d[i]);
	// }
	// ..Key is: e_0!dddd!
	// e_0!ffff!
	// for (i = 0; i < 5; i++){
	// 	e[i].dddd = 123 + i;
		// e[i].ffff = 456 - i;
		// e[i].kkkk = 789 * i;
		// e[i].G.iiii = i + 2 * i + 3 * i;
		// e[i].G.oooo = (i + 1) * 2; 
		// e[i].G.pppp = i * i;
		// e[i].G.ssss.rrrr = 123 - (5 * i);
		// e[i].G.ssss.tttt = 456 + (7 / 7);
		// e[i].G.ssss.yyyy = 789 - (i * -5);
		// e[i].G.ssss.uuuuu.eeee = i * 5.5;
		// e[i].G.ssss.uuuuu.qqqq = i * 2 * 3.05;
	// }
	// e_0!dddd!
	//e0_!dddd!
	//e_0!dddd!
	// for (i = 0; i < 5; i++){
	// 	printf("%d\n", e[i].dddd);
	// 	printf("%d\n", e[i].ffff);
	// 	printf("%d\n", e[i].kkkk);
		// printf("%d\n", e[i].G.iiii);
	// 	printf("%d\n", e[i].G.oooo);
	// 	printf("%d\n", e[i].G.pppp);
	// 	printf("%d\n", e[i].G.ssss.rrrr);
	// 	printf("%d\n", e[i].G.ssss.tttt);
	// 	printf("%d\n", e[i].G.ssss.yyyy);
	// 	printf("%f\n", e[i].G.ssss.uuuuu.qqqq);
	// 	printf("%f\n", e[i].G.ssss.uuuuu.eeee);
	// }

	// // a[9][2] = 12;
	// i = 9;
	// for (i = 0; i < 10; i++){
	// 	printf("%d\n", b[i]);
	// }
	// b[7] = 2;
	// for (i = 0; i < 10; i++){
	// 	printf("%d\n", b[i]);
	// }
	// // a[5][2] = 3;
	// // c[1][2][3] = 4;

	// // printf("%d\n",a[5][2]);
	return;
}
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
	int b[10];  			// start: 6 --> end  16
	double c[10]; 			// start: 17 --> end 28
	float d[15]; 			// start: 29 --> end 41
	int j = 8;
	struct BaseFour e[31]; // start: 42 --> end 414
    struct BaseFour bS;

    int aV = 6;
    double dV = 4.4;
    float cV = 5.5;
	// pointer/
	// int a[4][6];
	// int three[4][5][6];
	// int fourD[6][7][8][9];
	// int fourD[3][4][5][6];
	// int fourD[5][4][13][4];

	// int four[1][1][1][1][1][1][1][1][1][1][2][2][2][2][2][2][2][2][2][2];
//	 int indexA;
//	 int indexB;
//	 int indexC;
//	 int indexD;


	// // int j;
	// // // int* aa;
	// // // int** aa;
	// // // int*** aaa;
	// // // int**** aaaa;


    b[7] = 99;
    printf("%d\n", b[7]);
    i = 7;
    b[i] = 98;
    printf("%d\n", b[i]);
    b[i + j] =  98;
    printf("%d\n", b[i + j]);
    b[4] = 12345;
    printf("%d\n", b[4]);
    b[7] = 15;
    b[8] = 7;
    printf("%d\n", b[7]);
    printf("%d\n", b[8]);
    printf("%d\n", b[b[8]]);

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
     printf("%d\n", aV);
    aV++;
    printf("%d\n", aV);
    ++aV;
    printf("%d\n", aV);
    aV = aV + 1;
    printf("%d\n", aV);
    aV = 1 + aV;
    printf("%d\n", aV);
    aV += 1;
    printf("%d\n", aV);

	for (i = 0; i < 10; i++){
		b[i] = i*2;
	}
	 for (i = 0; i < 10; i++){
	 	printf("%d\n", b[i]);
	 }

	 for (i = 0; i < 10; i++){
	 	c[i] = i + 2.02;
	 }
	 for (i = 0; i < 10; i++){
	 	printf("%f\n", c[i]);
	 }
	 for (i = 0; i < 15; i++){
	 	d[i] = i + 2.12;
	 }

	 for (i = 0; i < 15; i++){
	 	printf("%f\n", d[i]);
	 }
	b[2] = 4;
	b[3] = 8;
    printf("%d\n", b[2]);
    printf("%d\n", b[3]);

    b[3] = 2 + 15;
    printf("%d\n", b[3]);
    b[6] = 8;
    b[7] = 11;
    printf("%d\n", b[6]);
    printf("%d\n", b[7]);
    printf("%d\n", b[2]);
    b[4] = b[6] + b[7];
    printf("%d\n", b[4]);
    printf("%d\n", b[6]);
    printf("%d\n", b[7]);
    b[5] = 6;
    printf("%d\n", b[5]);
    ++b[5];
    printf("%d\n", b[5]);
    b[5]++;
    printf("%d\n", b[5]);
    b[4] = 2;
    printf("%d\n", b[4]);
    printf("%d\n", b[2]);
    b[b[4]]++;
    printf("%d\n", b[2]);
    printf("%d\n", b[5]);
    b[1] = 2;
    b[2] = 3;
    b[3] = 4;
    b[4] = 5;
    printf("%d\n", b[b[b[b[b[b[1]]]]]]);
    b[b[b[b[b[b[1]]]]]]++;
    printf("%d\n", b[b[b[b[b[b[1]]]]]]);
    ++b[b[b[b[b[b[1]]]]]];
    printf("%d\n", b[b[b[b[b[b[1]]]]]]);
    b[b[b[b[b[b[1]]]]]]--;
    printf("%d\n", b[b[b[b[b[b[1]]]]]]);
    --b[b[b[b[b[b[1]]]]]];
    printf("%d\n", b[b[b[b[b[b[1]]]]]]);
    b[b[b[b[1]]]]++;
    printf("%d\n", b[5]);
    b[4] = 3;
    printf("%d\n", b[4]);
    printf("%d\n", b[3]);
    b[7] = b[b[4]];
    printf("%d\n", b[7]);

	 for (i = 0; i < 31; i++){
	 	e[i].dddd = 123 + i;
	 	e[i].ffff = 456 - i;
	 	e[i].kkkk = 789 * i;
	 	e[i].G.iiii = i + 2 * i + 3 * i;
	 	e[i].G.oooo = (i + 1) * 2;
	 	e[i].G.pppp = i * i;
	 	e[i].G.ssss.rrrr = 123 - (5 * i);
	 	e[i].G.ssss.tttt = 456 + (7 / 7);
	 	e[i].G.ssss.yyyy = 789 - (i * -5);
	 	e[i].G.ssss.uuuuu.eeee = i * 5.5;
	 	e[i].G.ssss.uuuuu.qqqq = i * 2 * 3.05;
	 }

	 for (i = 0; i < 31; i++){
	 	printf("%d\n", e[i].dddd);
	 	printf("%d\n", e[i].ffff);
	 	printf("%d\n", e[i].kkkk);
	 	printf("%d\n", e[i].G.iiii);
	 	printf("%d\n", e[i].G.oooo);
	 	printf("%d\n", e[i].G.pppp);
	 	printf("%d\n", e[i].G.ssss.rrrr);
	 	printf("%d\n", e[i].G.ssss.tttt);
	 	printf("%d\n", e[i].G.ssss.yyyy);
	 	printf("%f\n", e[i].G.ssss.uuuuu.qqqq);
	 	printf("%f\n", e[i].G.ssss.uuuuu.eeee);
	 }

	// fourD[2][2][0][8] = 20;
	// printf("%d\n", fourD[2][2][0][8]);
	// fourD[1][3][4][5] = 999;	
	// printf("%d\n", fourD[1][3][4][5]);

	// indexA = 7;
	// indexB = 3;
	// indexC = 5;
	// indexD = 4;
	// fourD[4][5][6][7] = indexA + indexB + indexC + indexD;
	// printf("%d\n", fourD[4][5][6][7]);

	// indexA = 3;
	// indexB = 2;
	// indexC = 8;
	// indexD = 2;
	// fourD[indexA][indexB][indexC][indexD] = 2;
	// printf("%d\n", fourD[3][2][8][2]);
	// printf("%d\n", fourD[indexA][indexB][indexC][indexD]);
	// fourD[indexA][indexB][indexC][indexD] = indexA + indexB + indexC + indexD;

	// for (indexA = 0; indexA < 5; indexA++){
	// 	for(indexB = 0; indexB < 4; indexB++){
	// 		for(indexC = 0; indexC < 13; indexC++){
	// 			for(indexD = 0; indexD < 4; indexD++){
	// 				fourD[indexA][indexB][indexC][indexD] = (indexA + indexB + indexC + indexD);
	// 			}
	// 		}
	// 	}
	// }

	// for (indexA = 0; indexA < 5; indexA++){
	// 	for(indexB = 0; indexB < 4; indexB++){
	// 		for(indexC = 0; indexC < 13; indexC++){
	// 			for(indexD = 0; indexD < 4; indexD++){
	// 				printf("%d\n", fourD[indexA][indexB][indexC][indexD]);
	// 			}
	// 		}
	// 	}
	// }
	// a[3][2] = 12;
	// printf("%d\n", a[8][7]);
	
	// for (i = 0; i < 10; i++){
	// 	printf("%d\n", b[i]);
	// }
	// b[7] = 2;
	// for (i = 0; i < 10; i++){
	// 	printf("%d\n", b[i]);
	// }
	// a[8][7] = 9090;
	// printf("%d\n", a[8][7]);

	// for (i =0; i < 15; i++){
	// 	for (j = 0; j < 15; j++){
	// 		a[i][j]=i + j;
	// 	}
	// }

	// for (i =0; i < 15; i++){
	// 	for (j = 0; j < 15; j++){
	// 		printf("%d\n", a[i][j]);
	// 	}
	// }
	// // a[5][2] = 3;
	// // c[1][2][3] = 4;

	// // printf("%d\n",a[5][2]);
	return;
}
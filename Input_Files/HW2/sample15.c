#include <stdio.h>
// struct st1
// { //total_size = 1+1+20+10+12 = 44
//     int a;          // →inc 0, size = 1 
//     double * *b;    //→inc 1, size = 1 
//     float * c[20]; //   →inc 2, size = 20 * 1 = 20 
//     int * **c[10]; // →inc 22, size = 10 * 1 = 10 
//     double * d[2][3][2]; // →inc 32, size = 2 * 3 * 2 * 1 = 12
    
// };

void main()
{
    // struct st1 ****a;       // →address = 5, size = 1 
    // int * *b;               // →address = 6, size = 1 
    // double * c[30];         // →address = 7, size = 30 * 1 = 30 
    // float * *d[2][2][2];    // →address = 37, size = 2 * 2 * 2 * 1 = 8 
    // struct st1 arrS1[5];    // →address = 45, size = 5 * 44 = 220 
    // struct st1 arrS2[2][3]; // →address = 265, size = 2 * 3 * 44 = 264 
    // double arrD1[5];        // →address = 529, size = 5 * 1 = 5 
    // double arrD2[5][2];     // →address = 534, size = 5 * 2 * 1 = 10 
    // int arrI1[2];           // →address = 544, size = 2 * 1 = 2 
    // double * pD;            // →address = 546, size = 1 
    // struct st1 * pS;        // →address = 547, size = 1
    // pD = 529; (arrD1);
    // pD[2] = 18.2 + (pD[1]++) * pD[0];
    // pS = 45; (arrS1);
    // pS[1].a ++;
    return;
}
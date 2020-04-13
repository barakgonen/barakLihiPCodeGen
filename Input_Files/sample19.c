#include <stdio.h>

void main() {	
	int a;
	int b = 2;
	int c = 3;
	int d = 5;
	a = 1;
	while ((a || 0) && (2 < 5)){
        printf("%d\n",1);
        break;
       	printf("%d\n",2);
    }
	printf("%d\n",3);

	for (a = 2; a < d; ++a){
		break;
		for (c = 3; c < d; c++){
			printf("%d\n", 2);
		}
		break;
	}
	b=3;
	do{
		printf("%d\n",a+b);
		b-=1;
	}while(b);
	return;
}
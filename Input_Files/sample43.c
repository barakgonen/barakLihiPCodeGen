#include <stdio.h>

void main(){
    int i;
    int j;
    int k;

	i=0;
	for(i=0;i<5;i++){
		j = i+1;
		while(j<5){
			k = j+1;
			do{
				printf("%d\n",i);
				printf("%d\n",j);
				printf("%d\n",k);
				k++;
			}while(k < 5);
			j++;
		}
	}
    return;
}

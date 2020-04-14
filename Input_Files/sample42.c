#include <stdio.h>

void main(){

    if(2<5){
        printf("%d\n",1);
    }

    if(2<5){
        printf("%d\n",2);
    }

    if(7 != 7){
        printf("%d\n",3);
    }

    if(7 != 7){
        printf("%d\n",4);
    }

    if(6 < 5){
        printf("%d\n",5);
    }
    else{
        printf("%d\n",6);
    }

    if(2 < 5){
        printf("%d\n",7);
    }
    else{
        printf("%d\n",8);
    }


    if(2 < 5){
        printf("%d\n",9);
    }
    else {
		if(2 > 1){
	        printf("%d\n",10);
	    }
	    else{
	        printf("%d\n",11);
	    }
	}

    if(2 > 5){
        printf("%d\n",12);
    }
    else {
		if(2 > 1){
	        printf("%d\n",13);
	    }
	    else{
	        printf("%d\n",14);
	    }
	}

    if(0){
        printf("%d\n",15);
    }
    else{
		if(0){
	        printf("%d\n",16);
	    }
	    else{
	        printf("%d\n",17);
	    }
	}

    return;
}

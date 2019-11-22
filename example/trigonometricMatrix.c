#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14159265
int main(){
	int i=0;
	double rad;
	printf("%4s","");
	printf("%7s","sin");
	printf("%9s","cos");
	printf("%9s","tan");
	printf("%9s","cot");
	printf("%9s","sec");
	printf("%9s\n","csc");

	for(i=0; i<=45; i++){
		rad=i*PI/180;
		printf("%2d°  ",i);
		printf("%7.4lf  ",sin(rad));
		printf("%7.4lf  ",cos(rad));
		printf("%7.4lf  ",tan(rad));
		printf("%7.4lf  ",1/tan(rad));
		printf("%7.4lf  ",1/cos(rad));
		printf("%7.4lf  ",1/sin(rad));
		printf("\n");
	}
	return 0;
}
